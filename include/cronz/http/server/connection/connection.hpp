/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_CONNECTION_CONNECTION_HPP
#define CRONZ_HTTP_SERVER_CONNECTION_CONNECTION_HPP 1

#include "cronz/http/server/connection/types.hpp"
#include "cronz/http/server/internal/request.hpp"
#include "cronz/http/connection/address.hpp"
#include "cronz/http/version.hpp"

#include <memory>

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum IVersion, ServerConfigurationFlags ConfigurationFlags>
    class ServerConnection final : public std::enable_shared_from_this<ServerConnection<IVersion, ConfigurationFlags> > {
    protected:
        // Type definitions.
        using ServerConnectionSocketType = CRONZ_HTTP_NAMESPACE_INTERNAL::BasicSocketTCP4;
        using ServerWorkerRefType = CRONZ_HTTP_NAMESPACE_INTERNAL::ServerWorkerRef<IVersion, ConfigurationFlags>;

        // Properties.
        std::array<char, static_cast<std::size_t>(1024)> _buffer{};
        std::size_t _bufferLength = static_cast<std::size_t>(0);

        ConnectionMetrics _metrics{};
        ConnectionAddress _address{};

        Version _version = Version::Invalid;

        CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_POLL_STRUCT &_fd;

        ServerConnectionSocketType _socket{};

        ServerWorkerRefType _worker = nullptr;

        std::vector<CRONZ_HTTP_NAMESPACE_INTERNAL::ServerRequestResponsePair> _requests{};

        const std::size_t _index = std::numeric_limits<std::size_t>::max();

        // Constructors.
        ServerConnection(std::size_t index, ServerWorkerRefType worker,
                         CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_POLL_STRUCT &fd) noexcept;

        // Connection management.
        CRONZ_NODISCARD_L1 bool _init(CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET handle,
                                      ConnectionAddress &address) noexcept;

        void _terminate() noexcept;

        // Events.
        void _tick() noexcept;

        CRONZ_NODISCARD_L1 bool _in() noexcept;

        CRONZ_NODISCARD_L1 bool _out() noexcept;

        // Friends.
        friend class Server<IVersion, ConfigurationFlags>;
        friend class CRONZ_HTTP_NAMESPACE_INTERNAL::ServerWorker<IVersion, ConfigurationFlags>;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        ServerConnection() noexcept = delete;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the remote address of the connection.
         * @return Remote address of the connection.
         */
        CRONZ_NODISCARD_L1 const ConnectionAddress &address() const noexcept;

        /**
         * @brief Returns the metrics of the connection.
         * @return Metrics of the connection.
         */
        CRONZ_NODISCARD_L1 const ConnectionMetrics &metrics() const noexcept;

        /**
         * @brief Tells whether the connection is secure.
         * @return `true` if the connection is secure.
         * @return `false` if the connection is not secure.
         * @remark The connection is secure if the server is configured to use HTTPS.
         */
        CRONZ_NODISCARD_L1 constexpr bool isSecure() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~ServerConnection() noexcept = default;

        /** @} */
    };

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    using ServerConnectionRef = std::shared_ptr<ServerConnection<Version, ConfigurationFlags> >;

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/connection/impl/connection.ipp"

#endif // CRONZ_HTTP_SERVER_CONNECTION_CONNECTION_HPP
