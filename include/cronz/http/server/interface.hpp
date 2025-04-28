/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_INTERFACE_HPP
#define CRONZ_HTTP_SERVER_INTERFACE_HPP 1

#include "cronz/http/server/callback.hpp"
#include "cronz/http/server/config.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    struct ServerInterface : public ServerCallbacks<Version, ConfigurationFlags>,
                             public ServerConfiguration {
    };

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_INTERFACE_HPP
