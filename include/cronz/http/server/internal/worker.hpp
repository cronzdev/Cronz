/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_INTERNAL_WORKER_HPP
#define CRONZ_HTTP_SERVER_INTERNAL_WORKER_HPP 1

#include "cronz/http/server/connection/connection.hpp"

#include <atomic>
#include <shared_mutex>
#include <thread>
#include <vector>

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class ServerWorker final {
        // Type definitions.
        using ServerType = Server<Version, ConfigurationFlags>;
        using ServerConnectionType = ServerConnection<Version, ConfigurationFlags>;
        using ServerConnectionRefType = ServerConnectionRef<Version, ConfigurationFlags>;

        // Properties.
        std::vector<ServerConnectionRefType> _connections{};
        std::vector<CRONZ_POLL_STRUCT> _fds{};

        std::shared_mutex _lock{};
        std::thread _thread{};

        ServerType *_server = nullptr;

        std::atomic<std::size_t> _numConnections = static_cast<std::size_t>(0);

        std::atomic_bool _running = false;

        // Friends.
        friend class Server<Version, ConfigurationFlags>;
        friend class ServerConnection<Version, ConfigurationFlags>;

        // Constructors.
        explicit ServerWorker(ServerType *server) noexcept;

        // Instance management.
        CRONZ_NODISCARD_L1 bool _allocate() noexcept;

        void _free() noexcept;

        // Connection management.
        CRONZ_NODISCARD_L1 bool _add(CRONZ_SOCKET handle, ConnectionAddress &address) noexcept;

        void _remove(std::size_t index) noexcept;

        void _run() noexcept;

        void _loop() noexcept;

        // Destructor.
        ~ServerWorker() noexcept = default;

    public:
        // Constructors.
        ServerWorker() = delete;
    };

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#include "cronz/http/server/internal/impl/worker.ipp"

#endif // CRONZ_HTTP_SERVER_INTERNAL_WORKER_HPP
