/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_CONFIG_HPP
#define CRONZ_HTTP_SERVER_CONFIG_HPP 1

#include "cronz/http/server/types.hpp"

#include "cronz/uri/authority/port.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Server configuration.
     * @class ServerConfiguration
     */
    class ServerConfiguration {
    public:
        /**
         * @name Static type definitions.
         */
        /** @{ */
        /**
         * @brief Server configuration value type.
         */
        using ServerConfigurationValueType = std::uint_fast32_t;

        /** @} */
    private:
        // Properties.
        ServerConfigurationValueType _numWorkers = static_cast<ServerConfigurationValueType>(1);
        ServerConfigurationValueType _maxConnectionsPerWorker = static_cast<ServerConfigurationValueType>(32);

        Port _port = InvalidPort;

        bool _ipv4 = true;
        bool _ipv6 = false;

        template<typename T>
        void _assign(T &config, T value) noexcept;

        template<typename T, T Min, T Max>
        void _assign(T &config, T value) noexcept;

    protected:
        bool _configurationLocked = false;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @remark Initializes the server configuration with default values: 1 worker and 32 connections per worker.
         */
        ServerConfiguration() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Gets the number of workers.
         * @return The number of workers.
         */
        CRONZ_NODISCARD_L1 ServerConfigurationValueType numWorkers() const noexcept;

        /**
         * @brief Sets the number of workers.
         * @param[in] value The number of workers. Must be greater than 0. Capped at 1000.
         */
        void numWorkers(ServerConfigurationValueType value) noexcept;

        /**
         * @brief Gets the maximum number of connections per worker.
         * @return The maximum number of connections per worker.
         */
        CRONZ_NODISCARD_L1 ServerConfigurationValueType maxConnectionsPerWorker() const noexcept;

        /**
         * @brief Sets the maximum number of connections per worker.
         * @param[in] value The maximum number of connections per worker. Must be greater than 0. Capped at 100000.
         */
        void maxConnectionsPerWorker(ServerConfigurationValueType value) noexcept;

        /**
         * @brief Gets the port.
         * @return The port.
         */
        CRONZ_NODISCARD_L1 Port port() const noexcept;

        /**
         * @brief Sets the port.
         * @param[in] port The port.
         */
        void port(Port port) noexcept;

        /**
         * @brief Tells if IPv4 is enabled.
         * @return `true` if IPv4 is enabled.
         * @return `false` if IPv4 is not enabled.
         */
        CRONZ_NODISCARD_L1 bool isIPv4Enabled() const noexcept;

        /**
         * @brief Enables IPv4.
         */
        void enableIPv4() noexcept;

        /**
         * @brief Disables IPv4.
         */
        void disableIPv4() noexcept;

        /**
         * @brief Tells if IPv6 is enabled.
         * @return `true` if IPv6 is enabled.
         * @return `false` if IPv6 is not enabled.
         */
        CRONZ_NODISCARD_L1 bool isIPv6Enabled() const noexcept;

        /**
         * @brief Enables IPv6.
         */
        void enableIPv6() noexcept;

        /**
         * @brief Disables IPv6.
         */
        void disableIPv6() noexcept;

        /**
         * @brief Tells if the server configuration is locked.
         * @return `true` if the server configuration is locked.
         * @return `false` if the server configuration is not locked.
         * @remark The server configuration is locked after the server is initialized.
         */
        CRONZ_NODISCARD_L1 bool isConfigurationLocked() const noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/impl/config.ipp"

#endif // CRONZ_HTTP_SERVER_CONFIG_HPP
