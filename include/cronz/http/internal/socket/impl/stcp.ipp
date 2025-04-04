/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_IMPL_STCP_IPP
#define CRONZ_HTTP_INTERNAL_SOCKET_IMPL_STCP_IPP 1

#include "cronz/http/internal/socket/stcp.hpp"

#if CRONZ_ENABLE_OPENSSL

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily>
    inline SSL *BasicSocketSTCPBase<AddressFamily>::ssl() const noexcept {
        return _ssl;
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::create() noexcept {
        return false;
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::close() noexcept {
        if (nullptr != _ssl) {
            SSL_free(_ssl);
            _ssl = nullptr;
        }

        [[maybe_unused]] const bool _ = this->_closeSocket();
        return true;
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::ok() const noexcept {
        return nullptr != _ssl && this->_isSocketOk();
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::handshake(SSL_CTX *context) noexcept {
        _ssl = SSL_new(context);
        if (nullptr == _ssl)
            return false;

        if (1 != SSL_set_fd(_ssl, this->_socket) ||
            1 != SSL_accept(_ssl))
            goto handshake_bad;

        return true;

    handshake_bad:
        SSL_free(_ssl);
        _ssl = nullptr;

        return false;
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::read(void *buffer, std::size_t &limit) const noexcept {
        const int res = SSL_read(this->_socket, static_cast<char *>(buffer), static_cast<int>(limit), 0);
        if (1 > res)
            return false;

        limit = static_cast<std::size_t>(res);
        return true;
    }

    template<int AddressFamily>
    inline bool BasicSocketSTCPBase<AddressFamily>::write(const void *buffer, std::size_t &length) const noexcept {
        const int res = SSL_write(this->_socket, static_cast<const char *>(buffer), static_cast<int>(length));
        if (1 > res)
            return false;

        length = static_cast<std::size_t>(res);
        return true;
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_ENABLE_OPENSSL

#endif // CRONZ_HTTP_INTERNAL_SOCKET_IMPL_STCP_IPP
