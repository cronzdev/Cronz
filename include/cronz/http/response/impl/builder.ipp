/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_RESPONSE_IMPL_BUILDER_IPP
#define CRONZ_HTTP_RESPONSE_IMPL_BUILDER_IPP 1

#include "cronz/http/response/builder.hpp"
#include "cronz/http/cookie.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline bool ResponseBuilder::isComplete() const noexcept {
        return State::COMPLETE == _state;
    }

    // Response building.
    inline bool ResponseBuilder::prepare(const Version &version, Response &response) noexcept {
        const DateTime<> now = DateTime<>::Now();
        const std::string dateString = now.stringify();

        // HTTP version.
        if (Version::HTTP_1_1 != version)
            return false;

        _version = version;

        // Status code.
        if (StatusCode::Invalid == response.status)
            response.status = StatusCode::OK;
        else if (response.status.reason().empty())
            response.status.reason() = StatusCode::StatusCodeReasons.at(response.status.code());

        // Headers.
        if (dateString.empty() || !response.headers.set("Date", dateString) ||
            !response.headers.set("Server", "Cronz"))
            return false;

        if (!response.headers.contains("Content-Type") &&
            !response.headers.set("Content-Type", "application/octet-stream"))
            return false;

        if (response.contentCallback.has_value()) {
            if (!response.headers.set("Transfer-Encoding", "chunked"))
                return false;
        } else {
            if (!response.headers.set("Content-Length", std::to_string(response.body.length()))) {
                return false;
            }
        }

        // State.
        _state = State::PREPARED;

        _size = static_cast<std::size_t>(0);
        _offset = static_cast<std::size_t>(0);

        return true;
    }

    inline bool ResponseBuilder::buildNextBlock(Response &response) noexcept {
        if (State::NONE == _state || isComplete())
            return false;

        if (static_cast<std::size_t>(0) != _size)
            return true;

        _block.clear();
        _offset = static_cast<std::size_t>(0);

        switch (_state) {
            case State::PREPARED:
                if (!_version.stringify(_block))
                    return false;

                try {
                    _block.push_back(' ');

                    _block.append(std::to_string(response.status.code()));
                    _block.push_back(' ');
                    _block.append(response.status.reason());

                    _block.push_back('\r');
                    _block.push_back('\n');

                    _size = _block.size();
                    _state = State::HEADERS;
                    return true;
                } catch (...) {
                    return false;
                }

            case State::HEADERS:
                if (!response.headers.stringify(_block))
                    return false;

                if (response.contentCallback.has_value()) {
                    _state = State::BODY_CHUNKED;
                } else {
                    try {
                        _block.push_back('\r');
                        _block.push_back('\n');
                    } catch (...) {
                        return false;
                    }

                    _state = State::BODY_CONTENT;
                }

                _size = _block.size();
                return true;

            case State::BODY_CHUNKED:
                response.body.clear();

                _hasMore = response.contentCallback.value()(response.body);
                if (response.body.empty()) {
                    if (!_hasMore)
                        _state = State::BODY_CHUNKED_COMPLETE;

                    _size = static_cast<std::size_t>(0);
                    return true;
                }

                try {
                    _block = std::format("\r\n{:X}\r\n", response.body.length());
                    _size = _block.size();
                } catch (...) {
                    return false;
                }

                _state = State::BODY_CHUNKED_PHASE1;
                return true;

            case State::BODY_CHUNKED_PHASE1:
                _block.swap(response.body);
                _size = _block.size();
                _state = State::BODY_CHUNKED_PHASE2;
                return true;

            case State::BODY_CHUNKED_PHASE2:
                if (_hasMore)
                    _state = State::BODY_CHUNKED;
                else
                    _state = State::BODY_CHUNKED_COMPLETE;

                return true;

            case State::BODY_CHUNKED_COMPLETE:
                try {
                    _block.assign("\r\n0\r\n\r\n");
                } catch (...) {
                    return false;
                }

                _size = _block.size();
                _state = State::BODY_FINISHED;
                return true;

            case State::BODY_CONTENT:
                _block.swap(response.body);
                _size = _block.size();

                if (static_cast<std::size_t>(0) == _size)
                    _state = State::COMPLETE;
                else
                    _state = State::BODY_FINISHED;

                return true;

            case State::BODY_FINISHED:
                _state = State::COMPLETE;
                return true;

            default:
                return false;
        }
    }

    inline std::string_view ResponseBuilder::getBlockData() const noexcept {
        if (static_cast<std::size_t>(0) == _size)
            return std::string_view{};

        return std::string_view{std::next(_block.cbegin(), _offset), _block.cend()};
    }

    inline void ResponseBuilder::advance(std::size_t bytes) noexcept {
        bytes = std::min(_size, bytes);

        _size -= bytes;
        _offset += bytes;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_RESPONSE_IMPL_BUILDER_IPP
