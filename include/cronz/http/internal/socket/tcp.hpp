/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_TCP_HPP
#define CRONZ_HTTP_INTERNAL_SOCKET_TCP_HPP 1

#include "cronz/http/internal/socket/base.hpp"

#include "cronz/http/connection/address.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily>
    class BasicSocketTCPBase final : public SocketBase<AddressFamily, SOCK_STREAM, IPPROTO_TCP> {
        static_assert(AF_INET == AddressFamily || AF_INET6 == AddressFamily, "Invalid address family.");

        Port _port = InvalidPort;

        template<typename T>
        CRONZ_NODISCARD_L1 bool _getAddr(CRONZ_SOCKET &handle, ConnectionAddress &address) const noexcept;

    public:
        BasicSocketTCPBase() noexcept = default;

        CRONZ_NODISCARD_L1 bool create() noexcept override;

        CRONZ_NODISCARD_L1 bool close() noexcept override;

        CRONZ_NODISCARD_L1 bool ok() const noexcept override;

        CRONZ_NODISCARD_L1 bool accept(CRONZ_SOCKET &handle, ConnectionAddress &address) const noexcept;

        CRONZ_NODISCARD_L1 bool bind(Port port, bool strict) noexcept;

        CRONZ_NODISCARD_L1 bool bind(std::string_view ip, Port port, bool strict) noexcept;

        CRONZ_NODISCARD_L1 bool listen() const noexcept;

        CRONZ_NODISCARD_L1 bool read(void *buffer, std::size_t &limit) const noexcept;

        CRONZ_NODISCARD_L1 bool write(const void *buffer, std::size_t &length) const noexcept;

        ~BasicSocketTCPBase() override = default;
    };

    using BasicSocketTCP4 = BasicSocketTCPBase<AF_INET>;
    using BasicSocketTCP6 = BasicSocketTCPBase<AF_INET6>;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#include "cronz/http/internal/socket/impl/tcp.ipp"

#endif // CRONZ_HTTP_INTERNAL_SOCKET_TCP_HPP
