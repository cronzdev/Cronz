/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_CONNECTION_IMPL_CONNECTION_IPP
#define CRONZ_HTTP_SERVER_CONNECTION_IMPL_CONNECTION_IPP 1

#include "cronz/http/server/connection/connection.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline ServerConnection<Version, ConfigurationFlags>::ServerConnection(
        const std::size_t index, const ServerWorkerRefType worker,
        CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_POLL_STRUCT &fd) noexcept : _fd(fd), _worker(worker), _index(index) {
    }

    // Connection management.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerConnection<Version, ConfigurationFlags>::_init(
        const CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET handle, ConnectionAddress &address) noexcept {
        if (_socket.ok())
            return false;

        _socket.handle(handle);

        _address.address.swap(address.address);
        _address.port = address.port;

        return _socket.setNonBlocking(true);
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerConnection<Version, ConfigurationFlags>::_terminate() noexcept {
        [[maybe_unused]] const bool _ = _socket.close();
        _address.address.clear();

        _fd.fd = CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_INVALID_SOCKET;

        _requests.clear();
    }

    // Events.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerConnection<Version, ConfigurationFlags>::_tick() noexcept {
        if (!_socket.ok() || static_cast<short>(0) == _fd.revents)
            return;

        if ((_fd.revents & POLLIN) && _in())
            return;

        if ((_fd.revents & POLLOUT) && _out())
            return;

        _worker->_remove(_index);
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerConnection<Version, ConfigurationFlags>::_in() noexcept {
        _bufferLength = _buffer.size();
        if (!_socket.read(_buffer.data(), _bufferLength)) {
            if (const int err = CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET_GET_ERROR();
                err == EWOULDBLOCK || err == WSAEWOULDBLOCK)
                return true;

            return false;
        }

        _metrics.totalBytesIn += _bufferLength;

        if (_requests.empty()) {
            try {
                _requests.push_back({});
            } catch (...) {
                return false;
            }
        }

        auto &rr = _requests[0];
        if (!rr.requestParser.feed(_buffer.data(), _bufferLength) ||
            rr.requestParser.isInvalid()) {
            return false;
        }

        if (rr.requestParser.isComplete()) {
            auto self = _worker->_connections[_index];
            _worker->_server->onRequest(self, rr.requestParser.request(), rr.response);

            if (!rr.responseBuilder.prepare(Version::HTTP_1_1, rr.response))
                return false;

            _fd.events = POLLOUT;
        }

        return true;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerConnection<Version, ConfigurationFlags>::_out() noexcept {
        auto &rr = _requests[0];

        if (rr.responseBuilder.isComplete()) {
            _fd.events = POLLHUP;
            return false;
        }

        if (!rr.responseBuilder.buildNextBlock(rr.response))
            return false;

        const std::string_view block = rr.responseBuilder.getBlockData();
        if (block.empty())
            return false;

        std::size_t len = block.length();
        if (!_socket.write(block.data(), len)) {
            if (const int err = CRONZ_HTTP_NAMESPACE_INTERNAL::CRONZ_SOCKET_GET_ERROR();
                err == EWOULDBLOCK || err == WSAEWOULDBLOCK)
                return true;

            return false;
        }

        rr.responseBuilder.advance(len);

        _metrics.totalBytesOut += len;

        return true;
    }

    // Properties.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline const ConnectionAddress &ServerConnection<Version, ConfigurationFlags>::address() const noexcept {
        return _address;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline const ConnectionMetrics &ServerConnection<Version, ConfigurationFlags>::metrics() const noexcept {
        return _metrics;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline constexpr bool ServerConnection<Version, ConfigurationFlags>::isSecure() const noexcept {
        return CRONZ_HTTP_NAMESPACE_INTERNAL::IsHTTPSEnabled<ConfigurationFlags>();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_CONNECTION_IMPL_CONNECTION_IPP
