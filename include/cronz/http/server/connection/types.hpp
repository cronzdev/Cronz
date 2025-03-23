/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_CONNECTION_TYPES_HPP
#define CRONZ_HTTP_SERVER_CONNECTION_TYPES_HPP 1

#include "cronz/http/version.hpp"
#include "cronz/http/server/flags.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class Server;

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class ServerWorker;

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    using ServerWorkerRef = ServerWorker<Version, ConfigurationFlags> *;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_SERVER_CONNECTION_TYPES_HPP
