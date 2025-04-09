/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_SERVER_HPP
#define CRONZ_HTTP_SERVER_SERVER_HPP 1

#include "cronz/http/server/config.hpp"
#include "cronz/http/server/extension.hpp"
#include "cronz/http/server/flags.hpp"
#include "cronz/http/server/tls.hpp"
#include "cronz/http/version.hpp"

#include "cronz/http/server/internal/worker.hpp"

#include <shared_mutex>
#include <tuple>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief HTTP server.
     * @tparam Version HTTP version.
     * @tparam ConfigurationFlags Server configuration flags.
     * @class Server
     */
    template<Version::Enum Version = Version::HighestSupportedVersion,
        ServerConfigurationFlags ConfigurationFlags = DefaultServerConfigurationFlags, typename... Extensions>
    class Server : public ServerConfiguration,
                   public Extensions... {
    public:
        /**
         * @name Type definitions.
         */
        /** @{ */
        /**
         * @brief Server connection type.
         */
        using ServerConnectionRefType = ServerConnectionRef<Version, ConfigurationFlags, Extensions...>;

        /** @} */
    private:
        // Static assertions.
        static_assert(Version::HTTP_0_9 != Version, "HTTP/0.9 is deprecated.");
        static_assert(Version::HTTP_1_0 != Version, "HTTP/1.0 is deprecated.");
        static_assert(Version::HTTP_2 != Version, "HTTP/2 is not supported.");
        static_assert(Version::HTTP_3 != Version, "HTTP/3 is not supported.");
        static_assert(Version::Invalid != Version, "Invalid HTTP version.");

        static_assert(CRONZ_HTTP_NAMESPACE_INTERNAL::IsServerIPv4<ConfigurationFlags>() ||
                      CRONZ_HTTP_NAMESPACE_INTERNAL::IsServerIPv6<ConfigurationFlags>(),
                      "Invalid server configuration. At least one of IPv4 or IPv6 must be enabled.");

        static_assert((std::is_base_of_v<ServerExtension, Extensions> && ...));

        // Type definitions.
        using ServerType = Server<Version, ConfigurationFlags, Extensions...>;

        using ServerWorkerType = CRONZ_HTTP_NAMESPACE_INTERNAL::ServerWorker<Version, ConfigurationFlags, Extensions...>
        ;
        using ServerWorkerRefType = CRONZ_HTTP_NAMESPACE_INTERNAL::ServerWorkerRef<Version, ConfigurationFlags,
            Extensions...>;

        using ServerSocketType = std::conditional_t<CRONZ_HTTP_NAMESPACE_INTERNAL::IsServerIPv4<ConfigurationFlags>(),
            CRONZ_HTTP_NAMESPACE_INTERNAL::BasicSocketTCP4,
            CRONZ_HTTP_NAMESPACE_INTERNAL::BasicSocketTCP6>;

        // Constants.
        inline static constexpr std::int_fast8_t STATE_NONE = static_cast<std::int_fast8_t>(0);
        inline static constexpr std::int_fast8_t STATE_INITIALIZED = static_cast<std::int_fast8_t>(1);
        inline static constexpr std::int_fast8_t STATE_RUNNING = static_cast<std::int_fast8_t>(2);
        inline static constexpr std::int_fast8_t STATE_STOPPING = static_cast<std::int_fast8_t>(3);

        // Properties.
        std::vector<ServerWorkerRefType> _workers{};

        ServerSocketType _socket{};

        std::shared_mutex _lock{};

        // std::tuple<Extensions...> _extensions{Extensions{_lock}...};

        std::int_fast8_t _state = STATE_NONE;

#if CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN
        bool _wsa = false;
#endif // CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN

        CRONZ_NODISCARD_L1 bool _initialized() const noexcept;

        CRONZ_NODISCARD_L1 bool _running() const noexcept;

        CRONZ_NODISCARD_L1 bool _stopping() const noexcept;

        // Server management.
        CRONZ_NODISCARD_L1 bool _initialize() noexcept;

        void _terminate() noexcept;

        void _serve() noexcept;

        // Connection management.
        void _addConnection(CRONZ_NAMESPACE_INTERNAL::CRONZ_SOCKET handle, ConnectionAddress &address) noexcept;

        // Extensions.
        CRONZ_NODISCARD_L1 bool _installExtensions() noexcept;

        void _uninstallExtensions() noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Server() noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Tells whether the server is initialized.
         * @return `true` if the server is initialized.
         * @return `false` if the server is not initialized.
         */
        CRONZ_NODISCARD_L1 bool isInitialized() const noexcept;

        /**
         * @brief Tells whether the server is running.
         * @return `true` if the server is running.
         * @return `false` if the server is not running.
         */
        CRONZ_NODISCARD_L1 bool isRunning() const noexcept;

        /**
         * @brief Tells whether the server is stopping.
         * @return `true` if the server is stopping.
         * @return `false` if the server is not stopping.
         */
        CRONZ_NODISCARD_L1 bool isStopping() const noexcept;

        /** @} */

        /**
         * @name Server management.
         */
        /** @{ */
        /**
         * @brief Initialize the server.
         * @return `true` if the server is successfully initialized.
         * @return `false` if the server is not successfully initialized.
         * @remark If the server is already initialized, but not running, it will be re-initialized.
         * @remark If the server is running or stopping, returns `false`.
         * @remark Upon the initialization, configuration options are locked.
         */
        CRONZ_NODISCARD_L1 bool initialize() noexcept;

        /**
         * @brief Start the server.
         * @param[in] async Whether to start the server asynchronously.
         * @return `true` if the server is successfully started.
         * @return `false` if the server is not successfully started.
         * @remark If the server is not initialized, then it will be initialized.
         * @remark If the server is running or stopping, returns `false`.
         * @remark If async is `true`, the function will return immediately after starting the server. However,
         * initialization or stopping will be synchronous.
         */
        CRONZ_NODISCARD_L1 bool serve(bool async = false) noexcept;

        /**
         * @brief Stop the server.
         * @param[in] abort Whether to abort the existing connections.
         * @remark This is a blocking operation.
         * @remark If `abort` is `true`, the server will stop immediately, and all existing connections will be
         * terminated. Active transactions will be aborted as well.
         * @remark If `abort` is `false`, the server will stop gracefully. Existing connections will be allowed to
         * complete their transactions.
         */
        void stop(bool abort = false) noexcept;

        /**
         * @brief Terminates and frees server resources.
         * @remark If the server is not initialized or is running, nothing happens. This function will not block and
         * will return immediately.
         */
        void terminate() noexcept;

        /** @} */

        /**
         * @name Callbacks.
         */
        /** @{ */
        /**
         * @brief Called when a new connection is accepted.
         * @param[in] address Address of the connection.
         * @return `true` to accept the connection.
         * @return `false` to reject the connection.
         * @remark This function is called on the server thread. Thus, until this function returns, the server will not
         * be able to accept new connections.
         * @TODO Make this function asynchronous.
         */
        virtual bool onAccept(const ConnectionAddress &address) noexcept = 0;

        /**
         * @brief Called when a request is received.
         * @param[in] connection Connection reference.
         * @param[in] request Request object.
         * @param[out] response Response object.
         * @remark This function is called on the worker thread. Thus, until this function returns, the worker will not
         * be able to process other requests.
         */
        virtual void onRequest(const ServerConnectionRefType &connection, const Request &request,
                               Response &response) noexcept = 0;

        /**
         * @brief Called when a connection is closed.
         * @param[in] connection Connection reference.
         * @remark This function is called on the worker thread. Thus, until this function returns, the worker will not
         * be able to process other requests.
         */
        virtual void onConnectionClosed(const ServerConnectionRefType &connection) noexcept = 0;

        /** @} */

        /**
         * @name Extensions.
         */
        /** @{ */
        /**
         * @brief Tells whether the server has the specified extension.
         * @tparam Extension Type of the extension.
         * @return `true` if the server has the extension.
         * @return `false` if the server does not have the extension.
         */
        template<typename Extension>
        CRONZ_NODISCARD_L1 constexpr bool hasExtension() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        virtual ~Server() noexcept = default;

        /** @} */

        /**
         * @name Static properties.
         */
        /** @{ */
        /**
         * @brief Default port for the server.
         * @return Default port for the server.
         * @remark The default port is 80 for HTTP and 443 for HTTPS.
         */
        CRONZ_NODISCARD_L1 static constexpr Port DefaultPort() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/impl/server.ipp"

#endif // CRONZ_HTTP_SERVER_SERVER_HPP
