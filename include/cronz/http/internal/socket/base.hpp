/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_INTERNAL_SOCKET_BASE_HPP
#define CRONZ_HTTP_INTERNAL_SOCKET_BASE_HPP 1

#include "cronz/http/internal/socket/types.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<int AddressFamily, int Type, int Protocol>
    class SocketBase {
        inline static constexpr std::size_t AddressLength = static_cast<std::size_t>(AF_INET == AddressFamily
                ? INET_ADDRSTRLEN
                : INET6_ADDRSTRLEN);

    protected:
        CRONZ_SOCKET _socket = CRONZ_INVALID_SOCKET;

        CRONZ_NODISCARD_L1 bool _createSocket() noexcept;

        CRONZ_NODISCARD_L1 bool _closeSocket() noexcept;

        CRONZ_NODISCARD_L1 bool _isSocketOk() const noexcept;

    public:
        SocketBase() noexcept = default;

        CRONZ_NODISCARD_L1 virtual bool create() noexcept = 0;

        CRONZ_NODISCARD_L1 virtual bool close() noexcept = 0;

        CRONZ_NODISCARD_L1 virtual bool ok() const noexcept = 0;

        CRONZ_NODISCARD_L1 bool setOption(int level, int name, const char *value, const int &length) const noexcept;

        template<typename T>
        CRONZ_NODISCARD_L1 bool setOption(int level, int name, const T *value, const int &length) const noexcept;

        template<typename T>
        CRONZ_NODISCARD_L1 bool setOption(int level, int name, const T &value) const noexcept;

        virtual ~SocketBase() = default;
    };

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#include "cronz/http/internal/socket/impl/base.ipp"

#endif // CRONZ_HTTP_INTERNAL_SOCKET_BASE_HPP
