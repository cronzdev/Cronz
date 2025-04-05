/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_IMPL_SESSION_IPP
#define CRONZ_SESSION_IMPL_SESSION_IPP 1

#include "cronz/session/session.hpp"

CRONZ_BEGIN_SESSION_NAMESPACE
    // Constructors.
    template<typename SessionDataType>
    inline Session<SessionDataType>::Session(const SessionId _sessionId, const SessionTime _startTime) noexcept
        : _sessionId(_sessionId), _startTime(_startTime), _lastAccessTime(_startTime) {
    }

    // Properties.
    template<typename SessionDataType>
    inline SessionId Session<SessionDataType>::id() const noexcept {
        return _sessionId;
    }

    template<typename SessionDataType>
    inline SessionTime Session<SessionDataType>::startTime() const noexcept {
        return _startTime;
    }

    template<typename SessionDataType>
    inline SessionTime Session<SessionDataType>::lastAccessTime() const noexcept {
        return _lastAccessTime;
    }

    template<typename SessionDataType>
    inline bool Session<SessionDataType>::isDeleted() const noexcept {
        return _deleted;
    }

    // Instance-based utility functions.
    template<typename SessionDataType>
    inline void Session<SessionDataType>::updateLastAccessTime() noexcept {
        _lastAccessTime = static_cast<SessionTime>(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
    }

CRONZ_END_SESSION_NAMESPACE

#endif // CRONZ_SESSION_IMPL_SESSION_IPP
