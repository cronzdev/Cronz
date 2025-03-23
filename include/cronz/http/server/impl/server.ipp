/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_IMPL_SERVER_IPP
#define CRONZ_HTTP_SERVER_IMPL_SERVER_IPP 1

#include "cronz/http/server/server.hpp"

#include <thread>

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline Server<Version, ConfigurationFlags>::Server() noexcept {
        port(DefaultPort());
    }

    // Properties.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::_initialized() const noexcept {
        return STATE_INITIALIZED <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::_running() const noexcept {
        return STATE_RUNNING <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::_stopping() const noexcept {
        return STATE_STOPPING <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::isInitialized() const noexcept {
        std::shared_lock _(_lock);
        return _initialized();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::isRunning() const noexcept {
        std::shared_lock _(_lock);
        return _running();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::isStopping() const noexcept {
        std::shared_lock _(_lock);
        return _stopping();
    }

    // Server management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::_initialize() noexcept {
        constexpr bool _ipv4 = CRONZ_HTTP_NAMESPACE_INTERNAL::IsServerIPv4<ConfigurationFlags>();
        constexpr bool _ipv6 = CRONZ_HTTP_NAMESPACE_INTERNAL::IsServerIPv6<ConfigurationFlags>();

#if CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN
        if (!_wsa) {
            WSADATA wsaData;
            if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
                goto init_bad;
        }
#endif // CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN

        try {
            _workers.resize(numWorkers(), nullptr);

            for (ServerWorkerRefType &worker: _workers) {
                worker = new(std::nothrow) ServerWorkerType(this);
                if (nullptr == worker || !worker->_allocate())
                    goto init_bad;
            }
        } catch (...) {
            goto init_bad;
        }

        if (!_socket.create() ||
            !_socket.bind(port(), !(_ipv4 && _ipv6)))
            goto init_bad;

        _state = STATE_INITIALIZED;
        _configurationLocked = true;
        return true;

    init_bad:
        _terminate();
        return false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void Server<Version, ConfigurationFlags>::_terminate() noexcept {
        if (!_workers.empty()) {
            for (ServerWorkerRefType worker: _workers) {
                if (worker) {
                    worker->_free();
                    delete worker;
                }
            }

            _workers.clear();
        }

        if (_socket.ok()) {
            [[maybe_unused]] const bool _ = _socket.close();
        }

        if (_wsa) {
            WSACleanup();
            _wsa = false;
        }

        _state = STATE_NONE;
        _configurationLocked = false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void Server<Version, ConfigurationFlags>::_serve() noexcept {
        ConnectionAddress address{};
        CRONZ_NAMESPACE_INTERNAL::CRONZ_SOCKET handle = CRONZ_NAMESPACE_INTERNAL::CRONZ_INVALID_SOCKET;

        for (ServerWorkerRefType worker: _workers)
            worker->_run();

        while (_running()) {
            if (!_socket.accept(handle, address)) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            if (!onAccept(address)) {
                [[maybe_unused]] const bool _ = CRONZ_NAMESPACE_INTERNAL::CRONZ_CLOSE_SOCKET(handle);
                continue;
            }

            _addConnection(handle, address);
        }
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::initialize() noexcept {
        std::lock_guard _(_lock);

        if (_running() || _stopping())
            return false;

        if (_initialized())
            terminate();

        return _initialize();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool Server<Version, ConfigurationFlags>::serve(const bool async) noexcept {
        std::lock_guard _(_lock);

        if (_running() || _stopping())
            return false;

        if (!_initialized() && !_initialize())
            return false;

        if (!_socket.listen())
            return false;

        _state = STATE_RUNNING;

        if (async)
            std::thread(&_serve, this).detach();
        else
            _serve();

        return true;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void Server<Version, ConfigurationFlags>::stop(bool abort) noexcept {
        std::lock_guard _(_lock);

        if (!_running())
            return;

        _state = STATE_STOPPING;

        _state = STATE_INITIALIZED;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void Server<Version, ConfigurationFlags>::terminate() noexcept {
        std::lock_guard _(_lock);

        if (!_initialized() || _running() || _stopping())
            return;

        _terminate();
    }

    // Connection management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void Server<Version, ConfigurationFlags>::_addConnection(CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET handle,
                                                                    ConnectionAddress &address) noexcept {
        ServerWorkerRefType candidate = nullptr;
        std::size_t candidateLoad = std::numeric_limits<std::size_t>::max();
        for (const ServerWorkerRefType worker: _workers) {
            if (const std::size_t workerLoad = worker->_numConnections;
                workerLoad < candidateLoad && workerLoad < maxConnectionsPerWorker()) {
                candidate = worker;
                candidateLoad = workerLoad;
            }
        }

        if (nullptr == candidate || !candidate->_add(handle, address))
            [[maybe_unused]] const bool _ = CRONZ_NAMESPACE_INTERNAL::CRONZ_CLOSE_SOCKET(handle);
    }

    // Static properties.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline constexpr Port Server<Version, ConfigurationFlags>::DefaultPort() noexcept {
        if constexpr (CRONZ_HTTP_NAMESPACE_INTERNAL::IsHTTPSEnabled<ConfigurationFlags>())
            return static_cast<Port>(443);
        else
            return static_cast<Port>(80);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_IMPL_SERVER_IPP
