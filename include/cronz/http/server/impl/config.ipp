/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_IMPL_CONFIG_IPP
#define CRONZ_HTTP_SERVER_IMPL_CONFIG_IPP 1

#include "cronz/http/server/config.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    template<typename T, T Min, T Max>
    inline void ServerConfiguration::_assign(T &config, T value) noexcept {
        config = (value < Min) ? Min : (value > Max) ? Max : value;
    }

    inline ServerConfiguration::ServerConfigurationValueType ServerConfiguration::numWorkers() const noexcept {
        return _numWorkers;
    }

    inline void ServerConfiguration::numWorkers(const ServerConfigurationValueType value) noexcept {
        _assign<ServerConfigurationValueType,
            static_cast<ServerConfigurationValueType>(1),
            static_cast<ServerConfigurationValueType>(1000)>(_numWorkers, value);
    }

    inline ServerConfiguration::ServerConfigurationValueType
    ServerConfiguration::maxConnectionsPerWorker() const noexcept {
        return _maxConnectionsPerWorker;
    }

    inline void ServerConfiguration::maxConnectionsPerWorker(const ServerConfigurationValueType value) noexcept {
        _assign<ServerConfigurationValueType,
            static_cast<ServerConfigurationValueType>(1),
            static_cast<ServerConfigurationValueType>(100000)>(_maxConnectionsPerWorker, value);
    }

    inline bool ServerConfiguration::isConfigurationLocked() const noexcept {
        return _configurationLocked;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_IMPL_CONFIG_IPP
