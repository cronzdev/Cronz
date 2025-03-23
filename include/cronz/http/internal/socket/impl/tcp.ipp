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
    template<typename T>
    inline bool BasicSocketTCPBase<AddressFamily>::_getAddr(CRONZ_SOCKET &handle,
                                                            ConnectionAddress &address) const noexcept {
        static thread_local std::array<char, BasicSocketTCPBase<AddressFamily>::AddressLength> str{};

        T addr{};
        socklen_t len = sizeof(T);

        handle = CRONZ_ACCEPT_SOCKET(this->_socket, reinterpret_cast<sockaddr *>(&addr), &len);
        if (CRONZ_INVALID_SOCKET == handle)
            return false;

        if constexpr (AF_INET == AddressFamily) {
            if (nullptr == inet_ntop(AddressFamily, &addr.sin_addr, str.data(), str.size()))
                goto invalidate_socket;

            address.port = ntohs(addr.sin_port);
        }

        if constexpr (AF_INET6 == AddressFamily) {
            if (nullptr == inet_ntop(AddressFamily, &addr.sin6_addr, str.data(), str.size()))
                goto invalidate_socket;

            address.port = ntohs(addr.sin6_port);
        }

        try {
            address.address.assign(str.data());
        } catch (...) {
            goto invalidate_socket;
        }

        return true;

    invalidate_socket:
        CRONZ_CLOSE_SOCKET(handle);
        handle = CRONZ_INVALID_SOCKET;

        return false;
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::create() noexcept {
        return this->_createSocket();
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::close() noexcept {
        [[maybe_unused]] const bool _ = this->_closeSocket();
        return true;
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::ok() const noexcept {
        return this->_isSocketOk();
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::accept(CRONZ_SOCKET &handle,
                                                          ConnectionAddress &address) const noexcept {
        if constexpr (AF_INET == AddressFamily)
            return _getAddr<sockaddr_in>(handle, address);

        if constexpr (AF_INET6 == AddressFamily)
            return _getAddr<sockaddr_in6>(handle, address);

        return false;
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::bind(const Port port, const bool strict) noexcept {
        return bind(std::string_view(), port, strict);
    }

    template<int AddressFamily>
    inline bool BasicSocketTCPBase<AddressFamily>::bind(const std::string_view ip, const Port port,
                                                        bool strict) noexcept {
        if (!this->_isSocketOk())
            return false;

        if (!this->setOption(SOL_SOCKET, SO_REUSEADDR, static_cast<int>(1)))
            return false;

        if constexpr (AF_INET == AddressFamily) {
            sockaddr_in address{};
            address.sin_family = AddressFamily;
            address.sin_port = htons(port);

            if (!ip.empty()) {
                if (1 != inet_pton(AF_INET, ip.data(), &address.sin_addr))
                    return false;
            } else {
                address.sin_addr.s_addr = INADDR_ANY;
            }

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

            if (!ip.empty()) {
                if (1 != inet_pton(AF_INET6, ip.data(), &address.sin6_addr))
                    return false;
            } else {
                address.sin6_addr = in6addr_any;
            }

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
    inline bool BasicSocketTCPBase<AddressFamily>::write(const void *buffer, std::size_t &length) const noexcept {
        const int res = CRONZ_WRITE_SOCKET(this->_socket, static_cast<const char *>(buffer), static_cast<int>(length),
                                           0);
        if (CRONZ_SOCKET_ERROR == res)
            return false;

        length = static_cast<std::size_t>(res);
        return true;
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_INTERNAL_SOCKET_IMPL_TCP_IPP
