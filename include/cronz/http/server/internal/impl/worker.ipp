/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_INTERNAL_IMPL_WORKER_IPP
#define CRONZ_HTTP_SERVER_INTERNAL_IMPL_WORKER_IPP 1

#include "cronz/http/server/internal/worker.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    // Constructors.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline ServerWorker<Version, ConfigurationFlags>::ServerWorker(ServerType *server) noexcept : _server(server) {
    }

    // Instance management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerWorker<Version, ConfigurationFlags>::_allocate() noexcept {
        _free();

        try {
            _fds.resize(_server->maxConnectionsPerWorker(), CRONZ_POLL_STRUCT{
                            CRONZ_INVALID_SOCKET, static_cast<short>(0), static_cast<short>(0)
                        });

            _connections.resize(_server->maxConnectionsPerWorker(), nullptr);

            auto index = static_cast<std::size_t>(0);
            for (ServerConnectionRefType &connection: _connections) {
                connection.reset(new(std::nothrow) ServerConnectionType(index, this, _fds[index]));

                if (!connection)
                    goto allocation_failure;

                ++index;
            }
        } catch (...) {
            goto allocation_failure;
        }

        return true;

    allocation_failure:
        _free();
        return false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerWorker<Version, ConfigurationFlags>::_free() noexcept {
        for (ServerConnectionRefType &connection: _connections) {
            if (!connection)
                continue;

            connection->_terminate();
            connection.reset();
        }

        _fds.clear();
        _connections.clear();
    }

    // Connection management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerWorker<Version, ConfigurationFlags>::_add(
        const CRONZ_SOCKET handle, ConnectionAddress &address) noexcept {
        std::lock_guard _(_lock);

        if (_numConnections >= _connections.size())
            return false;

        for (ServerConnectionRefType &connection: _connections) {
            if (connection->_socket.ok())
                continue;

            if (!connection->_init(handle, address))
                return false;

            auto &[fd, ev, rv] = connection->_fd;
            fd = handle;
            ev = POLLIN;
            rv = static_cast<short>(0);

            ++_numConnections;
            return true;
        }

        return false;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerWorker<Version, ConfigurationFlags>::_remove(std::size_t index) noexcept {
        ServerConnectionRefType connection = _connections[index];

        connection->_metrics.timeClosed = std::chrono::system_clock::now();

        connection->_terminate();

        --_numConnections;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerWorker<Version, ConfigurationFlags>::_run() noexcept {
        if (_running)
            return;

        _running = true;

        std::thread(&_loop, this).detach();
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerWorker<Version, ConfigurationFlags>::_loop() noexcept {
        while (_running) {
            std::shared_lock _(_lock);

            if (static_cast<std::size_t>(0) == _numConnections) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                continue;
            }

            const auto res = CRONZ_POLL(_fds.data(), _fds.size(), 100);
            if (0 == res) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                continue;
            }

            if (CRONZ_SOCKET_ERROR == res) {
                std::abort();
            }

            for (ServerConnectionRefType &connection: _connections)
                connection->_tick();
        }
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_SERVER_INTERNAL_IMPL_WORKER_IPP
