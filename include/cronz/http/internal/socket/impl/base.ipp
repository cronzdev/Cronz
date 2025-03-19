/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_IMPL_BASE_IPP
#define CRONZ_HTTP_INTERNAL_SOCKET_IMPL_BASE_IPP 1

#include "cronz/http/internal/socket/base.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::_createSocket() noexcept {
        if (!_closeSocket())
            return false;

        _socket = CRONZ_CREATE_SOCKET(AddressFamily, Type, Protocol);
        return _isSocketOk();
    }

    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::_closeSocket() noexcept {
        if (!_isSocketOk())
            return true;

        if (0 != CRONZ_CLOSE_SOCKET(_socket))
            return false;

        _socket = CRONZ_INVALID_SOCKET;
        return true;
    }

    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::_isSocketOk() const noexcept {
        return CRONZ_INVALID_SOCKET != _socket;
    }

    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::setOption(const int level, const int name, const char *value,
                                                                     const int &length) const noexcept {
        return 0 == ::setsockopt(_socket, level, name, reinterpret_cast<const char *>(value), length);
    }

    template<int AddressFamily, int Type, int Protocol>
    template<typename T>
    inline bool SocketBase<AddressFamily, Type, Protocol>::setOption(const int level, const int name, const T *value,
                                                                     const int &length) const noexcept {
        return setOption(level, name, reinterpret_cast<const char *>(value), length);
    }

    template<int AddressFamily, int Type, int Protocol>
    template<typename T>
    inline bool SocketBase<AddressFamily, Type,
        Protocol>::setOption(const int level, const int name, const T &value) const noexcept {
        return setOption(level, name, reinterpret_cast<const char *>(value[0]), static_cast<int>(sizeof(value)));
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_INTERNAL_SOCKET_IMPL_BASE_IPP
