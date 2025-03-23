/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_IMPL_FLAGS_IPP
#define CRONZ_HTTP_SERVER_IMPL_FLAGS_IPP 1

#include "cronz/http/server/flags.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<ServerConfigurationFlags ConfigurationFlags>
    inline constexpr bool IsHTTPSEnabled() noexcept {
        return static_cast<bool>(ConfigurationFlags & ServerConfigurationFlagBits::SERVER_ENABLE_HTTPS);
    }

    template<ServerConfigurationFlags ConfigurationFlags>
    inline constexpr bool IsServerIPv4() noexcept {
        return static_cast<bool>(ConfigurationFlags & SERVER_USE_IPv4);
    }

    template<ServerConfigurationFlags ConfigurationFlags>
    inline constexpr bool IsServerIPv6() noexcept {
        return static_cast<bool>(ConfigurationFlags & SERVER_USE_IPv6);
    }

    template<ServerConfigurationFlags ConfigurationFlags>
    inline constexpr int GetServerAddressFamily() noexcept {
        if constexpr (IsServerIPv4<ConfigurationFlags>())
            return AF_INET;

        if constexpr (IsServerIPv6<ConfigurationFlags>())
            return AF_INET6;

        return AF_INET + AF_INET6 + 1;
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_SERVER_IMPL_FLAGS_IPP
