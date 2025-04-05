/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_SESSION_HPP
#define CRONZ_SESSION_SESSION_HPP 1

#include "cronz/session/types.hpp"

#include <atomic>
#include <memory>
#include <type_traits>

CRONZ_BEGIN_SESSION_INTERNAL_NAMESPACE
    template<typename SessionDataType>
    struct SessionDataWrapperT {
        SessionDataType data;
    };

    template<typename SessionDataType>
    struct SessionDataWrapperS : public SessionDataType {
    };

    template<typename SessionDataType>
    struct SessionDataWrapper : public std::conditional_t<std::is_class_v<SessionDataType>,
                SessionDataWrapperS<SessionDataType>, SessionDataWrapperT<SessionDataType> > {
    };

    template<>
    struct SessionDataWrapper<void> {
    };

CRONZ_END_SESSION_INTERNAL_NAMESPACE

CRONZ_BEGIN_SESSION_NAMESPACE
    /**
     * @ingroup cronz_session
     * @brief Session class.
     * @tparam SessionDataType Type of the session data.
     */
    template<typename SessionDataType>
    class Session final : public CRONZ_SESSION_NAMESPACE_INTERNAL::SessionDataWrapper<SessionDataType> {
        // Properties.
        SessionId _sessionId = static_cast<SessionId>(0);

        SessionTime _startTime = static_cast<SessionTime>(0);
        SessionTime _lastAccessTime = static_cast<SessionTime>(0);

        std::atomic_bool _deleted = false;

        // Constructors.
        Session(SessionId _sessionId, SessionTime _startTime) noexcept;

        // Friends.
        template<typename ISessionDataType, SessionManagerConfigurationFlags ConfigurationFlags,
            SessionIdGeneratorFunctionType SessionIdGeneratorCallback,
            SessionOnCreateFunctionType<SessionDataType> SessionOnCreateCallback,
            SessionOnDestroyFunctionType<SessionDataType> SessionOnDestroyCallback>
        friend class SessionManager;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @remark This constructor is deleted. Use `SessionManager` instead.
         */
        Session() noexcept = delete;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the session id.
         * @return The session id.
         */
        CRONZ_NODISCARD_L1 SessionId id() const noexcept;

        /**
         * @brief Tells when the session was started.
         * @return Start time of the session in milliseconds.
         */
        CRONZ_NODISCARD_L1 SessionTime startTime() const noexcept;

        /**
         * @brief Tells the time the session was last accessed.
         * @return Last access time of the session in milliseconds.
         * @remark This value is automatically updated when the session is retrieved through a session manager.
         */
        CRONZ_NODISCARD_L1 SessionTime lastAccessTime() const noexcept;

        /**
         * @brief Returns whether the session is deleted.
         * @return `true` if the session is deleted.
         * @return `false` if the session is not deleted.
         * @remark The intended way to access a session is through a `std::shared_ptr`. Thus, the session may be
         * invalidated and removed from the manager's registry, but a copy of it may still be alive somewhere else,
         * possibly registered by the user.
         */
        CRONZ_NODISCARD_L1 bool isDeleted() const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Updates the last access time of the session.
         * @remark This function is automatically called when the session is retrieved through a session manager.
         */
        void updateLastAccessTime() noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~Session() noexcept = default;

        /** @} */
    };

CRONZ_END_SESSION_NAMESPACE

#include "cronz/session/impl/session.ipp"

#endif // CRONZ_SESSION_SESSION_HPP
