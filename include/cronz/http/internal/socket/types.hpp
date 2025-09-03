/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_TYPES_HPP
#define CRONZ_HTTP_INTERNAL_SOCKET_TYPES_HPP 1

#include "cronz/http/types.hpp"

#if CRONZ_OS_WINDOWS && !CRONZ_OS_WINDOWS_CYGWIN

#include <ws2tcpip.h>

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    using CRONZ_SOCKET = SOCKET;

    inline static constexpr auto CRONZ_INVALID_SOCKET = INVALID_SOCKET;
    inline static constexpr auto CRONZ_SOCKET_ERROR = SOCKET_ERROR;
    inline static constexpr auto CRONZ_SOCKET_GET_ERROR = WSAGetLastError;
    inline static constexpr auto CRONZ_CREATE_SOCKET = ::socket;
    inline static constexpr auto CRONZ_CLOSE_SOCKET = ::closesocket;
    inline static constexpr auto CRONZ_BIND_SOCKET = ::bind;
    inline static constexpr auto CRONZ_LISTEN_SOCKET = ::listen;
    inline static constexpr auto CRONZ_READ_SOCKET = ::recv;
    inline static constexpr auto CRONZ_WRITE_SOCKET = ::send;
    inline static constexpr auto CRONZ_ACCEPT_SOCKET = ::accept;
    inline static constexpr auto CRONZ_SHUTDOWN_SOCKET = ::shutdown;

    inline static constexpr auto CRONZ_POLL = WSAPoll;
    inline static constexpr auto CRONZ_POLL_M = 1;
    inline static constexpr auto CRONZ_POLL_IN = POLLIN;
    inline static constexpr auto CRONZ_POLL_OUT = POLLOUT;
    inline static constexpr auto CRONZ_POLL_HUP = POLLHUP;
    inline static constexpr auto CRONZ_POLL_ERR = POLLERR;

    using CRONZ_POLL_STRUCT = WSAPOLLFD;

CRONZ_END_HTTP_INTERNAL_NAMESPACE
#endif // CRONZ_OS_WINDOWS && !CRONZ_OS_WINDOWS_CYGWIN

#if CRONZ_OS_LINUX || CRONZ_OS_UNIX || CRONZ_OS_WINDOWS_CYGWIN

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    using CRONZ_SOCKET = int;

    inline static constexpr auto CRONZ_INVALID_SOCKET = -1;
    inline static constexpr auto CRONZ_SOCKET_ERROR = -1;
    inline static constexpr auto CRONZ_SOCKET_GET_ERROR = errno;
    inline static constexpr auto CRONZ_CREATE_SOCKET = ::socket;
    inline static constexpr auto CRONZ_CLOSE_SOCKET = ::close;
    inline static constexpr auto CRONZ_BIND_SOCKET = ::bind;
    inline static constexpr auto CRONZ_LISTEN_SOCKET = ::listen;
    inline static constexpr auto CRONZ_READ_SOCKET = ::recv;
    inline static constexpr auto CRONZ_WRITE_SOCKET = ::send;
    inline static constexpr auto CRONZ_ACCEPT_SOCKET = ::accept;
    inline static constexpr auto CRONZ_SHUTDOWN_SOCKET = ::shutdown;

    inline static constexpr auto CRONZ_POLL = poll;
    inline static constexpr auto CRONZ_POLL_M = 1;
    inline static constexpr auto CRONZ_POLL_IN = POLLIN;
    inline static constexpr auto CRONZ_POLL_OUT = POLLOUT;
    inline static constexpr auto CRONZ_POLL_HUP = POLLHUP;
    inline static constexpr auto CRONZ_POLL_ERR = POLLERR;

    using CRONZ_POLL_STRUCT = struct pollfd;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_OS_LINUX || CRONZ_OS_UNIX || CRONZ_OS_WINDOWS_CYGWIN

#endif // CRONZ_HTTP_INTERNAL_SOCKET_TYPES_HPP
