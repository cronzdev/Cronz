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
    template<typename T>
    inline void ServerConfiguration::_assign(T &config, T value) noexcept {
        if (_configurationLocked)
            return;

        config = value;
    }

    template<typename T, T Min, T Max>
    inline void ServerConfiguration::_assign(T &config, T value) noexcept {
        _assign<T>(config, (value < Min) ? Min : (value > Max) ? Max : value);
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

    inline Port ServerConfiguration::port() const noexcept {
        return _port;
    }

    inline void ServerConfiguration::port(const Port port) noexcept {
        _assign<Port>(_port, port);
    }

    inline bool ServerConfiguration::isIPv4Enabled() const noexcept {
        return _ipv4;
    }

    inline void ServerConfiguration::enableIPv4() noexcept {
        _assign<bool>(_ipv4, true);
    }

    inline void ServerConfiguration::disableIPv4() noexcept {
        _assign<bool>(_ipv4, false);
    }

    inline bool ServerConfiguration::isIPv6Enabled() const noexcept {
        return _ipv6;
    }

    inline void ServerConfiguration::enableIPv6() noexcept {
        _assign<bool>(_ipv6, true);
    }

    inline void ServerConfiguration::disableIPv6() noexcept {
        _assign<bool>(_ipv6, false);
    }

    inline bool ServerConfiguration::isConfigurationLocked() const noexcept {
        return _configurationLocked;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_IMPL_CONFIG_IPP
