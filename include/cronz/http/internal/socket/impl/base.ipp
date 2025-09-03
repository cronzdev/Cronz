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

        if (0 != CRONZ_CLOSE_SOCKET(_socket)) {
#if CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN
            constexpr struct linger l = {
                .l_onoff = static_cast<u_short>(1),
                .l_linger = static_cast<u_short>(0)
            };

            if (!setOption(SOL_SOCKET, SO_LINGER, l))
                return false;

#elif CRONZ_OS_LINUX || CRONZ_OS_UNIX || CRONZ_OS_WINDOWS_CYGWIN
            constexpr struct linger l = {
                .l_onoff = 1,
                .l_linger = 0
            };

            if (!setOption(SOL_SOCKET, SO_LINGER, l))
                return false;

#else
#error "Unsupported platform."
#endif // CRONZ_OS_WINDOWS && !CRONZ_OS_CYGWIN

            if (0 != CRONZ_CLOSE_SOCKET(_socket))
                return false;
        }

        _socket = CRONZ_INVALID_SOCKET;
        return true;
    }

    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::_isSocketOk() const noexcept {
        return CRONZ_INVALID_SOCKET != _socket;
    }


    template<int AddressFamily, int Type, int Protocol>
    inline CRONZ_SOCKET SocketBase<AddressFamily, Type, Protocol>::handle() const noexcept {
        return _socket;
    }


    template<int AddressFamily, int Type, int Protocol>
    inline void SocketBase<AddressFamily, Type, Protocol>::handle(const CRONZ_SOCKET handle) noexcept {
        _socket = handle;
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
        return setOption(level, name, &value, static_cast<int>(sizeof(value)));
    }

    template<int AddressFamily, int Type, int Protocol>
    inline bool SocketBase<AddressFamily, Type, Protocol>::setNonBlocking(const bool enabled) const noexcept {
        u_long mode = enabled ? 1 : 0;
        return 0 == (ioctlsocket(_socket, FIONBIO, &mode));
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_INTERNAL_SOCKET_IMPL_BASE_IPP
