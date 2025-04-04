/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_STCP_HPP
#define CRONZ_HTTP_INTERNAL_SOCKET_STCP_HPP 1

#include "cronz/http/internal/socket/base.hpp"

#if CRONZ_ENABLE_OPENSSL

#include <openssl/ssl.h>

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily>
    class BasicSocketSTCPBase final : public SocketBase<AddressFamily, SOCK_STREAM, IPPROTO_TCP> {
        static_assert(AF_INET == AddressFamily || AF_INET6 == AddressFamily, "Invalid address family.");

        SSL *_ssl = nullptr;

    public:
        BasicSocketSTCPBase() noexcept = default;

        CRONZ_NODISCARD_L1 SSL *ssl() const noexcept;

        CRONZ_NODISCARD_L1 bool create() noexcept override;

        CRONZ_NODISCARD_L1 bool close() noexcept override;

        CRONZ_NODISCARD_L1 bool ok() const noexcept override;

        CRONZ_NODISCARD_L1 bool handshake(SSL_CTX *context) noexcept;

        CRONZ_NODISCARD_L1 bool read(void *buffer, std::size_t &limit) const noexcept;

        CRONZ_NODISCARD_L1 bool write(const void *buffer, std::size_t &length) const noexcept;

        ~BasicSocketSTCPBase() override = default;
    };

    using BasicSocketSTCP4 = BasicSocketSTCPBase<AF_INET>;
    using BasicSocketSTCP6 = BasicSocketSTCPBase<AF_INET6>;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_ENABLE_OPENSSL

#include "cronz/http/internal/socket/impl/stcp.ipp"

#endif // CRONZ_HTTP_INTERNAL_SOCKET_STCP_HPP
