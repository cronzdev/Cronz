/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_MANAGER_HPP
#define CRONZ_SESSION_MANAGER_HPP 1

#include "cronz/session/flags.hpp"
#include "cronz/session/session.hpp"

#include <shared_mutex>

CRONZ_BEGIN_SESSION_NAMESPACE
    CRONZ_NODISCARD_L1 SessionId DefaultSessionIdGenerator() noexcept;

CRONZ_END_SESSION_NAMESPACE

CRONZ_BEGIN_SESSION_INTERNAL_NAMESPACE
    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags, bool Enabled>
    struct SessionManagerCallbacks;

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    struct SessionManagerCallbacks<SessionDataType, ConfigurationFlags, true> {
        using CallbackSessionType = CRONZ_SESSION_NAMESPACE_INTERNAL::SessionManagerCallbackSessionParamType<
            SessionDataType, ConfigurationFlags>;

        std::function<void(CallbackSessionType)> onSessionCreated = [](CallbackSessionType) -> void {
        };
        std::function<void(CallbackSessionType)> onSessionDestroyed = [](CallbackSessionType) -> void {
        };
    };

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    struct SessionManagerCallbacks<SessionDataType, ConfigurationFlags, false> {
    };

    template<typename SessionDataType, SessionManagerConfigurationFlags ConfigurationFlags>
    struct SessionManagerCallbacksWrapper : public SessionManagerCallbacks<SessionDataType, ConfigurationFlags,
                CRONZ_SESSION_NAMESPACE_INTERNAL::IsSessionManagerUsingSessionCallbacks<ConfigurationFlags>()> {
    };

    template<bool Enabled>
    struct SessionManagerThreadSafety;

    template<>
    struct SessionManagerThreadSafety<true> {
        std::shared_mutex _mutex{};
        std::atomic<std::thread::id> _owner{};
    };

    template<>
    struct SessionManagerThreadSafety<false> {
    };

CRONZ_END_SESSION_INTERNAL_NAMESPACE

CRONZ_BEGIN_SESSION_NAMESPACE
    /**
     * @ingroup cronz_session
     * @brief Session manager class.
     * @tparam SessionDataType Type of the session data.
     * @tparam ConfigurationFlags Session manager configuration flags.
     */
    template<typename SessionDataType = void,
        SessionManagerConfigurationFlags ConfigurationFlags = DefaultSessionManagerConfigurationFlags>
    class SessionManager final :
            public CRONZ_SESSION_NAMESPACE_INTERNAL::SessionManagerCallbacksWrapper<SessionDataType,
                ConfigurationFlags>,
            private CRONZ_SESSION_NAMESPACE_INTERNAL::SessionManagerThreadSafety<
                CRONZ_SESSION_NAMESPACE_INTERNAL::IsSessionManagerMultithreaded<ConfigurationFlags>()> {
    public:
        /**
         * @name Static types and constants.
         */
        /** @{ */
        /**
         * @brief Session type.
         */
        using SessionType = CRONZ_SESSION_NAMESPACE_INTERNAL::SessionPtrType<SessionDataType, ConfigurationFlags>;

        /**
         * @brief Session type.
         */
        using RawSessionType = Session<SessionDataType>;

        /**
         * @brief Session const reference type.
         */
        using SessionConstRefType = CRONZ_SESSION_NAMESPACE_INTERNAL::SessionConstRefType<SessionDataType,
            ConfigurationFlags>;

        /**
         * @brief Session destroy predicate function type.
         */
        using SessionDestroyPredicateFunction = std::function<bool(SessionConstRefType session, bool &cancel)>;

        /**
         * @brief Session filter predicate function type.
         */
        using SessionFilterPredicateFunction = std::function<bool(SessionConstRefType session, bool &cancel)>;

        /**
         * @brief Maximum value for session expiration time.
         */
        inline static constexpr SessionTime ExpirationTimeMax = static_cast<SessionTime>(31'536'000'000'000);

        /**
         * @brief Minimum value for session expiration time.
         */
        inline static constexpr SessionTime ExpirationTimeMin = static_cast<SessionTime>(1'000);

        /**
         * @brief Default value for session expiration time.
         */
        inline static constexpr SessionTime ExpirationTimeDefault = static_cast<SessionTime>(86'400'000);

        /** @} */

    private:
        using SessionArrayType = std::vector<SessionType>;

        using SessionArraySizeType = typename SessionArrayType::size_type;

        inline static constexpr SessionArraySizeType ArraySize = static_cast<SessionArraySizeType>(1) +
                                                                 static_cast<SessionArraySizeType>(std::numeric_limits<
                                                                     std::uint8_t>::max());

        using SessionArrayTypeB2 = std::array<SessionArrayType, ArraySize>;
        using SessionArrayTypeB1 = std::array<SessionArrayTypeB2, ArraySize>;

        inline static constexpr typename SessionArrayType::size_type AllocatorStep = static_cast<typename
            SessionArrayType::size_type>(32);

        inline static constexpr typename SessionArrayType::difference_type IterationStep = static_cast<typename
            SessionArrayType::size_type>(512);

        // Properties.
        SessionArrayTypeB1 _sessions{};

        SessionTime _expirationTime = ExpirationTimeDefault;

        std::atomic<std::size_t> _count = static_cast<std::size_t>(0);

        std::atomic<bool> _busy = false;

        CRONZ_NODISCARD_L1 constexpr bool _isThreadSafe() const noexcept {
            return CRONZ_SESSION_NAMESPACE_INTERNAL::IsSessionManagerMultithreaded<ConfigurationFlags>();
        }

        CRONZ_NODISCARD_L1 constexpr bool _hasCallbacks() const noexcept {
            return CRONZ_SESSION_NAMESPACE_INTERNAL::IsSessionManagerUsingSessionCallbacks<ConfigurationFlags>();
        }

        CRONZ_NODISCARD_L1 constexpr bool _isUsingRawPointers() const noexcept {
            return CRONZ_SESSION_NAMESPACE_INTERNAL::IsSessionManagerUsingRawPointers<ConfigurationFlags>();
        }

        // Session management.
        CRONZ_NODISCARD_L1 SessionType _create() noexcept;

        CRONZ_NODISCARD_L1 SessionType _get(SessionId id) noexcept;

        CRONZ_NODISCARD_L1 SessionType _get(SessionId id, SessionTime startTime) noexcept;

        CRONZ_NODISCARD_L1 SessionType _get(SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept;

        CRONZ_NODISCARD_L2 bool _destroy(SessionId id) noexcept;

        CRONZ_NODISCARD_L2 bool _destroy(SessionId id, SessionTime startTime) noexcept;

        CRONZ_NODISCARD_L2 bool _destroy(SessionConstRefType session) noexcept;

        CRONZ_NODISCARD_L2 bool _destroy(SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept;

        CRONZ_NODISCARD_L2 typename SessionArrayType::iterator _destroyIt(
            SessionArrayType &arr, typename SessionArrayType::iterator it) noexcept;

        void _destroy(const SessionDestroyPredicateFunction &predicate) noexcept;

        void _destroyAll() noexcept;

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 SessionId _generateUniqueId() const noexcept;

        CRONZ_NODISCARD_L1 SessionArrayType &_getSessionArray(SessionId id) noexcept;

        CRONZ_NODISCARD_L1 const SessionArrayType &_getSessionArray(SessionId id) const noexcept;

        CRONZ_NODISCARD_L1 typename SessionArrayType::iterator _getSessionRangeStartIterator(
            const SessionArrayType &arr, SessionTime startTime) const noexcept;

        CRONZ_NODISCARD_L1 typename SessionArrayType::iterator _getSessionIterator(
            SessionArrayType &arr, SessionId id) noexcept;

        CRONZ_NODISCARD_L1 typename SessionArrayType::iterator _getSessionIterator(
            SessionArrayType &arr, SessionId id, SessionTime startTime) noexcept;

        void _shrink(SessionArrayType &arr) noexcept;

        void _purge(SessionArrayType &arr, SessionTime now) noexcept;

        CRONZ_NODISCARD_L1 bool _expired(SessionConstRefType session, SessionTime now) const noexcept;

        CRONZ_NODISCARD_L1 std::vector<SessionType> _filter(const SessionFilterPredicateFunction &predicate) noexcept;

        // Static utility functions.
        CRONZ_NODISCARD_L1 static SessionId _generateId() noexcept;

        CRONZ_NODISCARD_L1 static SessionTime _now() noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        SessionManager() noexcept = default;

        /**
         * @brief Deleted copy constructor.
         */
        SessionManager(const SessionManager &) = delete;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Tells the expiration time of sessions.
         * @return Expiration time of sessions.
         */
        CRONZ_NODISCARD_L1 SessionTime expirationTime() const noexcept;

        /**
         * @brief Sets the expiration time.
         * @param[in] milliseconds Expiration time of sessions.
         * @param[in] deleteExpired Whether to delete expired sessions based on the new expiration time.
         * @remark If `milliseconds` is invalid, this function does nothing.
         */
        void expirationTime(SessionTime milliseconds, bool deleteExpired = true) noexcept;

        /**
         * @brief Tells the number of sessions registered in the manager.
         * @return Number of sessions in the manager.
         */
        CRONZ_NODISCARD_L1 SessionCount count() const noexcept;

        /**
         * @brief Tells if the current container's registry is empty.
         * @return `true` if the current container does not hold and sessions, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Tells if the session manager is thread-safe.
         * @return `true` if the session manager is thread-safe.
         * @return `false` if the session manager is not thread-safe.
         */
        CRONZ_NODISCARD_L1 constexpr bool isThreadSafe() const noexcept;

        /** @} */

        /**
         * @name Session management.
         */
        /** @{ */
        /**
         * @brief Creates a session and returns the reference to it.
         * @return Reference to the session.
         * @return `nullptr` if the session could not be created.
         */
        CRONZ_NODISCARD_L1 SessionType create() noexcept;

        /**
         * @brief Gets the session with the given ID.
         * @param[in] id ID of the session to get.
         * @return Reference to the session.
         * @return `nullptr` if the session could not be found.
         */
        CRONZ_NODISCARD_L1 SessionType get(SessionId id) noexcept;

        /**
         * @brief Gets the session with the given ID and start time.
         * @param[in] id ID of the session to get.
         * @param[in] startTime Start time of the session to get.
         * @return Reference to the session.
         * @return `nullptr` if the session could not be found.
         */
        CRONZ_NODISCARD_L1 SessionType get(SessionId id, SessionTime startTime) noexcept;

        /**
         * @brief Destroys the session with the given ID.
         * @param[in] id ID of the session to destroy.
         * @return `true` if the session was destroyed successfully.
         * @return `false` if the session could not be destroyed.
         */
        CRONZ_NODISCARD_L2 bool destroy(SessionId id) noexcept;

        /**
         * @brief Destroys the session with the given ID and start time.
         * @param[in] id ID of the session to destroy.
         * @param[in] startTime Start time of the session to destroy.
         * @return `true` if the session was destroyed successfully.
         * @return `false` if the session could not be destroyed.
         */
        CRONZ_NODISCARD_L2 bool destroy(SessionId id, SessionTime startTime) noexcept;

        /**
         * @brief Destroys the session with the given reference.
         * @param[in] session Reference to the session to destroy.
         * @return `true` if the session was destroyed successfully.
         * @return `false` if the session could not be destroyed.
         */
        CRONZ_NODISCARD_L2 bool destroy(SessionConstRefType session) noexcept;

        /**
         * @brief Destroys the sessions that match the given predicate.
         * @param[in] predicate Predicate function to match the sessions to destroy.
         */
        void destroy(const SessionDestroyPredicateFunction &predicate) noexcept;

        /**
         * @brief Destroys all sessions in the session manager.
         */
        void destroyAll() noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 std::vector<SessionType> filter(const SessionFilterPredicateFunction &predicate) noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Deleted copy assignment operator.
         */
        SessionManager &operator=(const SessionManager &) = delete;

        /**
         * @brief Deleted move constructor.
         */
        SessionManager(SessionManager &&) = delete;

        /**
         * @brief Deleted move assignment operator.
         */
        SessionManager &operator=(SessionManager &&) = delete;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~SessionManager() noexcept = default;

        /** @} */
    };

CRONZ_END_SESSION_NAMESPACE

#include "cronz/session/impl/manager.ipp"

#endif // CRONZ_SESSION_MANAGER_HPP
