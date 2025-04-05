/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_IMPL_MANAGER_IPP
#define CRONZ_SESSION_IMPL_MANAGER_IPP 1

#include "cronz/session/manager.hpp"

#include <random>

CRONZ_BEGIN_SESSION_NAMESPACE
    inline SessionId DefaultSessionIdGenerator() noexcept {
        thread_local static std::random_device rd;
        thread_local static std::mt19937_64 mt(rd());
        thread_local static std::uniform_int_distribution<SessionId> ud{
            std::numeric_limits<SessionId>::min() + static_cast<SessionId>(1),
            std::numeric_limits<SessionId>::max()
        };

        return ud(mt);
    }

CRONZ_END_SESSION_NAMESPACE

CRONZ_BEGIN_SESSION_NAMESPACE
    // Properties.
    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline SessionTime SessionManager<SessionDataType, ConfigurationFlags>::expirationTime() const noexcept {
        return _expirationTime;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::expirationTime(
        const SessionTime milliseconds, bool deleteExpired) noexcept {
        if (ExpirationTimeMin > milliseconds || milliseconds > ExpirationTimeMax)
            return;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline SessionCount SessionManager<SessionDataType, ConfigurationFlags>::count() const noexcept {
        return _count;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::empty() const noexcept {
        return static_cast<SessionCount>(0) == _count;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline constexpr bool SessionManager<SessionDataType, ConfigurationFlags>::isThreadSafe() const noexcept {
        return _isThreadSafe();
    }

    // Session management.
    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::_create() noexcept {
        const SessionId id = _generateUniqueId();
        if (static_cast<SessionId>(0) == id)
            return nullptr;

        auto *ptr = new(std::nothrow) RawSessionType(id, _now());
        if (nullptr == ptr)
            return nullptr;

        SessionType session(ptr);

        SessionArrayType &arr = _getSessionArray(id);
        try {
            if (arr.size() == arr.capacity())
                arr.reserve(arr.capacity() + AllocatorStep);

            arr.emplace_back(session);
        } catch (...) {
            delete ptr;
            return nullptr;
        }

        if constexpr (_hasCallbacks())
            this->onSessionCreated(session);

        ++_count;
        return session;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::_get(const SessionId id) noexcept {
        SessionArrayType &arr = _getSessionArray(id);
        return _get(arr, _getSessionIterator(arr, id));
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::_get(const SessionId id, const SessionTime startTime) noexcept {
        SessionArrayType &arr = _getSessionArray(id);
        return _get(arr, _getSessionIterator(arr, id, startTime));
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::_get(SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept {
        if (arr.end() == it)
            return nullptr;

        SessionConstRefType session = (*it);

        const SessionTime now = _now();
        if (_expired(session, now)) {
            [[maybe_unused]] const bool _ = _destroy(arr, it);
            return nullptr;
        }

        session->_lastAccessTime = now;
        return session;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::_destroy(const SessionId id) noexcept {
        SessionArrayType &arr = _getSessionArray(id);
        return _destroy(arr, _getSessionIterator(arr, id));
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::_destroy(
        const SessionId id, const SessionTime startTime) noexcept {
        SessionArrayType &arr = _getSessionArray(id);
        return _destroy(arr, _getSessionIterator(arr, id, startTime));
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::_destroy(SessionConstRefType session) noexcept {
        SessionArrayType &arr = _getSessionArray(session->_sessionId);

        auto it = _getSessionIterator(arr, session->_sessionId, session->_startTime);
        if (it == arr.end() || (*it) != session)
            return false;

        return _destroy(arr, it);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::_destroy(
        SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept {
        if (it == arr.end())
            return false;

        [[maybe_unused]] const auto _ = _destroyIt(arr, it);

        _shrink(arr);
        return true;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionArrayType::iterator
    SessionManager<SessionDataType, ConfigurationFlags>::_destroyIt(
        SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept {
        SessionConstRefType session = (*it);
        session->_destroyed = true;

        if constexpr (_hasCallbacks())
            this->onSessionDestroyed(session);

        if constexpr (_isUsingRawPointers())
            delete session;
        else
            session.reset();

        --_count;
        return arr.erase(it);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    void SessionManager<SessionDataType, ConfigurationFlags>::_destroy(
        const SessionDestroyPredicateFunction &predicate) noexcept {
        const SessionTime now = _now();
        for (SessionArrayTypeB2 &b2: _sessions) {
            for (SessionArrayType &arr: b2) {
                bool cancel = false;
                for (auto it = arr.begin(); it != arr.end();) {
                    if (SessionConstRefType session = (*it);
                        _expired(session, now) || predicate(session, cancel)) {
                        it = _destroyIt(arr, it);
                    } else {
                        ++it;
                    }

                    if (cancel)
                        break;
                }

                _shrink(arr);

                if (cancel)
                    return;
            }
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::_destroyAll() noexcept {
        for (SessionArrayTypeB2 &b2: _sessions) {
            for (SessionArrayType &arr: b2) {
                if constexpr (_isUsingRawPointers()) {
                    for (SessionType session: arr) {
                        session->_destroyed = true;

                        if constexpr (_hasCallbacks())
                            this->onSessionDestroyed(session);

                        delete session;
                    }
                } else {
                    for (SessionType session: arr) {
                        session->_destroyed = true;

                        if constexpr (_hasCallbacks())
                            this->onSessionDestroyed(session);

                        session.reset();
                    }
                }

                arr.clear();
                arr.shrink_to_fit();
            }
        }

        _count = static_cast<SessionCount>(0);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::create() noexcept {
        if (_busy)
            return nullptr;

        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _create();
        } else {
            return _create();
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::get(const SessionId id) noexcept {
        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _get(id);
        } else {
            return _get(id);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType SessionManager<SessionDataType,
        ConfigurationFlags>::get(const SessionId id, const SessionTime startTime) noexcept {
        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _get(id, startTime);
        } else {
            return _get(id, startTime);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::destroy(const SessionId id) noexcept {
        if (static_cast<SessionId>(0) == id || _busy)
            return false;

        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _destroy(id);
        } else {
            return _destroy(id);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::destroy(
        const SessionId id, const SessionTime startTime) noexcept {
        if (static_cast<SessionId>(0) == id || static_cast<SessionTime>(0) >= startTime || _busy)
            return false;

        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _destroy(id, startTime);
        } else {
            return _destroy(id, startTime);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::destroy(SessionConstRefType session) noexcept {
        if (nullptr == session || session->_destroyed || _busy)
            return false;

        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _destroy(session);
        } else {
            return _destroy(session);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::destroy(
        const SessionDestroyPredicateFunction &predicate) noexcept {
        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            _destroy(predicate);
        } else {
            _destroy(predicate);
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::destroyAll() noexcept {
        if (_busy)
            return;

        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            _destroyAll();
        } else {
            _destroyAll();
        }
    }

    // Instance-based utility functions.
    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline SessionId SessionManager<SessionDataType, ConfigurationFlags>::_generateUniqueId() const noexcept {
        for (auto i = static_cast<std::uint8_t>(0); i < std::numeric_limits<std::uint8_t>::max(); ++i) {
            const SessionId id = _generateId();

            if (const SessionArrayType &arr = _getSessionArray(id);
                std::ranges::none_of(arr, [id](SessionConstRefType session) noexcept -> bool {
                    return session->_sessionId == id;
                })) {
                return id;
            }
        }

        return static_cast<SessionId>(0);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename SessionManager<SessionDataType, ConfigurationFlags>::SessionArrayType &SessionManager<
        SessionDataType, ConfigurationFlags>::_getSessionArray(const SessionId id) noexcept {
        SessionArrayTypeB2 &b2 = _sessions[static_cast<typename SessionArrayTypeB1::size_type>((id >> 8) & 0xFF)];
        SessionArrayType &arr = b2[static_cast<typename SessionArrayTypeB2::size_type>(id & 0xFF)];
        return arr;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline const typename SessionManager<SessionDataType, ConfigurationFlags>::SessionArrayType &SessionManager<
        SessionDataType, ConfigurationFlags>::_getSessionArray(const SessionId id) const noexcept {
        const SessionArrayTypeB2 &b2 = _sessions[static_cast<typename SessionArrayTypeB1::size_type>((id >> 8) & 0xFF)];
        const SessionArrayType &arr = b2[static_cast<typename SessionArrayTypeB2::size_type>(id & 0xFF)];
        return arr;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename std::vector<typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType>::iterator
    SessionManager<SessionDataType, ConfigurationFlags>::_getSessionRangeStartIterator(
        const SessionArrayType &arr, const SessionTime startTime) const noexcept {
        if (arr.empty())
            return arr.end();

        auto index = static_cast<typename SessionArrayType::size_type>(0);
        while (index < static_cast<typename SessionArrayType::size_type>(arr.size())) {
            const auto next = std::min((index + IterationStep), arr.size());
            if (arr[next - static_cast<typename SessionArrayType::size_type>(1)]->_startTime > startTime)
                break;

            index = next;
        }

        if (index == arr.size())
            return arr.end();

        return std::next(arr.begin(), index);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename std::vector<typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType>::iterator
    SessionManager<SessionDataType, ConfigurationFlags>::_getSessionIterator(
        SessionArrayType &arr, const SessionId id) noexcept {
        return std::ranges::find_if(arr, [id](SessionConstRefType session) noexcept -> bool {
            return session->_sessionId == id;
        });
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline typename std::vector<typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType>::iterator
    SessionManager<SessionDataType, ConfigurationFlags>::_getSessionIterator(
        SessionArrayType &arr, const SessionId id, const SessionTime startTime) noexcept {
        auto it = _getSessionRangeStartIterator(arr, startTime);
        while (it != arr.end()) {
            if (it->_sessionId == id)
                return it;

            if (it->_startTime > startTime)
                break;
        }

        return arr.end();
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::_shrink(SessionArrayType &arr) noexcept {
        if (AllocatorStep < (arr.capacity() - arr.size())) {
            const SessionCount capacity = (arr.capacity() - AllocatorStep);
            if (static_cast<SessionCount>(0) == (capacity % AllocatorStep))
                arr.shrink_to_fit();
        }
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline void SessionManager<SessionDataType, ConfigurationFlags>::_purge(
        SessionArrayType &arr, const SessionTime now) noexcept {
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline bool SessionManager<SessionDataType, ConfigurationFlags>::_expired(
        SessionConstRefType session, const SessionTime now) const noexcept {
        const SessionTime idle = (now - session->_lastAccessTime);
        return (idle >= _expirationTime);
    }

    // Static utility functions.
    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline SessionId SessionManager<SessionDataType, ConfigurationFlags>::_generateId() noexcept {
        thread_local static std::random_device rd;
        thread_local static std::mt19937_64 mt(rd());
        thread_local static std::uniform_int_distribution<SessionId> ud{
            std::numeric_limits<SessionId>::min() + static_cast<SessionId>(1),
            std::numeric_limits<SessionId>::max()
        };

        return ud(mt);
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline SessionTime SessionManager<SessionDataType, ConfigurationFlags>::_now() noexcept {
        return static_cast<SessionTime>(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline std::vector<typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType>
    SessionManager<SessionDataType, ConfigurationFlags>::_filter(
        const SessionFilterPredicateFunction &predicate) noexcept {
        std::vector<SessionType> sessions;

        const SessionTime now = _now();
        for (SessionArrayTypeB2 &b2: _sessions) {
            for (SessionArrayType &arr: b2) {
                bool cancel = false;
                for (auto it = arr.begin(); it != arr.end();) {
                    if (SessionConstRefType session = (*it);
                        _expired(session, now)) {
                        it = _destroyIt(arr, it);
                    } else {
                        if (predicate(session, cancel)) {
                            try {
                                sessions.emplace_back(session);
                            } catch (...) {
                            }
                        }

                        ++it;
                    }

                    if (cancel)
                        break;
                }

                _shrink(arr);

                if (cancel)
                    return sessions;
            }
        }

        return sessions;
    }

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    inline std::vector<typename SessionManager<SessionDataType, ConfigurationFlags>::SessionType>
    SessionManager<SessionDataType, ConfigurationFlags>::filter(
        const SessionFilterPredicateFunction &predicate) noexcept {
        if constexpr (_isThreadSafe()) {
            std::lock_guard _(this->_mutex);
            return _filter(predicate);
        } else {
            return _filter(predicate);
        }
    }

CRONZ_END_SESSION_NAMESPACE

#undef CRONZ_SESSION_MANAGER_DH

#endif // CRONZ_SESSION_IMPL_MANAGER_IPP
