/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_FLAGS_HPP
#define CRONZ_HTTP_SERVER_FLAGS_HPP 1

#include "cronz/http/server/types.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Server configuration flags.
     * @enum ServerConfigurationFlagBits
     */
    enum ServerConfigurationFlagBits : std::uint64_t {
        /**
         * @brief Enables HTTPS for the server.
         * @remark If not used, the server will serve using HTTP.
         */
        SERVER_ENABLE_HTTPS = 0x0000000000000001,

        /**
         * @brief Enables multiple SSL certificates for the server.
         * @remark If not used, the server will use a single SSL certificate.
         * @remark This flag is only valid if `SERVER_ENABLE_HTTPS` is set.
         */
        SERVER_ENABLE_MULTI_SSL = 0x0000000000000002,

        /**
         * @brief Tells the server to allow IPv4 connections.
         * @remark Can be used together with `SERVER_USE_IPv6` to allow both protocols.
         */
        SERVER_USE_IPv4 = 0x0000000000000004,

        /**
         * @brief Tells the server to allow IPv6 connections.
         * @remark Can be used together with `SERVER_USE_IPv4` to allow both protocols.
         */
        SERVER_USE_IPv6 = 0x0000000000000008,
    };

    /**
     * @ingroup cronz_http
     * @brief Server configuration flag type.
     * @typedef std::uint64_t ServerConfigurationFlags
     */
    typedef std::uint64_t ServerConfigurationFlags;

    /**
     * @ingroup cronz_http
     * @brief Default server configuration flags.
     * @var ServerConfigurationFlags DefaultServerConfigurationFlags
     */
    inline static constexpr ServerConfigurationFlags DefaultServerConfigurationFlags = SERVER_USE_IPv4;

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<ServerConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr bool IsHTTPSEnabled() noexcept;

    template<ServerConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr bool IsMultiSSLContextEnabled() noexcept;

    template<ServerConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr bool IsServerIPv4() noexcept;

    template<ServerConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr bool IsServerIPv6() noexcept;

    template<ServerConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr int GetServerAddressFamily() noexcept;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#include "cronz/http/server/impl/flags.ipp"

#endif // CRONZ_HTTP_SERVER_FLAGS_HPP
