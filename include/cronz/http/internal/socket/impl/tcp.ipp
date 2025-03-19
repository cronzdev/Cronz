/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_IMPL_TCP_IPP
#define CRONZ_HTTP_INTERNAL_SOCKET_IMPL_TCP_IPP 1

#include "cronz/http/internal/socket/tcp.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::create() noexcept {
        return this->_createSocket();
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::close() noexcept {
        return this->_closeSocket();
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::ok() const noexcept {
        return this->_isSocketOk();
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::bind(const u_short port, bool strict) noexcept {
        if (!this->_isSocketOk())
            return false;

        if (!this->setOption(SOL_SOCKET, SO_REUSEADDR, static_cast<int>(1)))
            return false;

        if constexpr (AF_INET == AddressFamily) {
            sockaddr_in address{};
            address.sin_family = AddressFamily;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(port);

            if (0 != CRONZ_BIND_SOCKET(this->_socket, reinterpret_cast<const sockaddr *>(&address), sizeof(address)))
                return false;
        } else if constexpr (AF_INET6 == AddressFamily) {
            if (strict && !this->setOption(IPPROTO_IPV6, IPV6_V6ONLY, static_cast<int>(1)))
                return false;

            sockaddr_in6 address{};
            address.sin6_family = AddressFamily;
            address.sin6_addr = in6addr_any;
            address.sin6_port = htons(port);
            address.sin6_flowinfo = 0;
            address.sin6_scope_id = 0;

            if (0 != CRONZ_BIND_SOCKET(this->_socket, reinterpret_cast<const sockaddr *>(&address), sizeof(address)))
                return false;
        }

        _port = port;
        return true;
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::listen() const noexcept {
        if (!this->_isSocketOk())
            return false;

        return 0 == CRONZ_LISTEN_SOCKET(this->_socket, 128);
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::read(void *buffer, std::size_t &limit) const noexcept {
        const int res = CRONZ_READ_SOCKET(this->_socket, static_cast<char *>(buffer), static_cast<int>(limit), 0);
        if (CRONZ_SOCKET_ERROR == res)
            return false;

        limit = static_cast<std::size_t>(res);
        return true;
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::write(void *buffer, std::size_t &length) const noexcept {
        const int res = CRONZ_WRITE_SOCKET(this->_socket, static_cast<char *>(buffer), static_cast<int>(length), 0);
        if (CRONZ_SOCKET_ERROR == res)
            return false;

        length = static_cast<std::size_t>(res);
        return true;
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_INTERNAL_SOCKET_IMPL_TCP_IPP
