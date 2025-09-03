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
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline Server<Version, ConfigurationFlags, Extensions...>::Server() noexcept : Extensions(this)... {
        this->port(DefaultPort());
    }

    // Properties.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::_initialized() const noexcept {
        return STATE_INITIALIZED <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::_running() const noexcept {
        return STATE_RUNNING <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::_stopping() const noexcept {
        return STATE_STOPPING <= _state;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::isInitialized() const noexcept {
        std::shared_lock _(_lock);
        return _initialized();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::isRunning() const noexcept {
        std::shared_lock _(_lock);
        return _running();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::isStopping() const noexcept {
        std::shared_lock _(_lock);
        return _stopping();
    }

    // Server management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::_initialize() noexcept {
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
            _workers.resize(this->numWorkers(), nullptr);

            for (ServerWorkerRefType &worker: _workers) {
                worker = new(std::nothrow) ServerWorkerType(this);
                if (nullptr == worker || !worker->_allocate())
                    goto init_bad;
            }
        } catch (...) {
            goto init_bad;
        }

        if (!_socket.create() ||
            !_socket.bind(this->port(), !(_ipv4 && _ipv6)))
            goto init_bad;

        if (!_installExtensions())
            goto init_bad;

        _state = STATE_INITIALIZED;
        this->_configurationLocked = true;
        return true;

    init_bad:
        _terminate();
        return false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::_terminate() noexcept {
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

#if CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN
        if (_wsa) {
            WSACleanup();
            _wsa = false;
        }
#endif // CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN

        _uninstallExtensions();

        _state = STATE_NONE;
        this->_configurationLocked = false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::_serve() noexcept {
        ConnectionAddress address{};
        CRONZ_NAMESPACE_INTERNAL::CRONZ_SOCKET handle = CRONZ_NAMESPACE_INTERNAL::CRONZ_INVALID_SOCKET;

        for (ServerWorkerRefType worker: _workers)
            worker->_run();

        while (_running()) {
            if (!_socket.accept(handle, address)) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            if (!this->onAccept(address)) {
                [[maybe_unused]] const bool _ = CRONZ_NAMESPACE_INTERNAL::CRONZ_CLOSE_SOCKET(handle);
                continue;
            }

            _addConnection(handle, address);
        }
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::initialize() noexcept {
        std::lock_guard _(_lock);

        if (_running() || _stopping())
            return false;

        if (_initialized())
            terminate();

        return _initialize();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::serve(const bool async) noexcept {
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

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::stop(bool abort) noexcept {
        std::lock_guard _(_lock);

        if (!_running())
            return;

        _state = STATE_STOPPING;

        _state = STATE_INITIALIZED;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::terminate() noexcept {
        std::lock_guard _(_lock);

        if (!_initialized() || _running() || _stopping())
            return;

        _terminate();
    }

    // Connection management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::_addConnection(
        CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET handle,
        ConnectionAddress &address) noexcept {
        ServerWorkerRefType candidate = nullptr;
        std::size_t candidateLoad = std::numeric_limits<std::size_t>::max();
        for (const ServerWorkerRefType worker: _workers) {
            if (const std::size_t workerLoad = worker->_numConnections;
                workerLoad < candidateLoad && workerLoad < this->maxConnectionsPerWorker()) {
                candidate = worker;
                candidateLoad = workerLoad;
            }
        }

        if (nullptr == candidate || !candidate->_add(handle, address))
            [[maybe_unused]] const bool _ = CRONZ_NAMESPACE_INTERNAL::CRONZ_CLOSE_SOCKET(handle);
    }

    // Extensions.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline bool Server<Version, ConfigurationFlags, Extensions...>::_installExtensions() noexcept {
        return (Extensions::install() && ...);
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline void Server<Version, ConfigurationFlags, Extensions...>::_uninstallExtensions() noexcept {
        (Extensions::uninstall(), ...);
    }

 /*   template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    template<ServerExtensionType<Version, ConfigurationFlags> Extension>
    inline constexpr bool Server<Version, ConfigurationFlags, Extensions...>::hasExtension() const noexcept {
        if constexpr (!std::derived_from<Extension, ServerExtension<Version, ConfigurationFlags>>)
            return false;

        return (... || std::is_same_v<Extension, Extensions>);
    }*/

    // Static properties.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, ServerExtensionType<Version, ConfigurationFlags>... Extensions>
    inline constexpr Port Server<Version, ConfigurationFlags, Extensions...>::DefaultPort() noexcept {
        if constexpr (CRONZ_HTTP_NAMESPACE_INTERNAL::IsHTTPSEnabled<ConfigurationFlags>())
            return static_cast<Port>(443);
        else
            return static_cast<Port>(80);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_IMPL_SERVER_IPP
