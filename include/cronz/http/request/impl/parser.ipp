/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_REQUEST_IMPL_PARSER_IPP
#define CRONZ_HTTP_REQUEST_IMPL_PARSER_IPP 1

#include "cronz/http/request/parser.hpp"

#include "cronz/rfc/rule/crlf.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline constexpr const Request &RequestParser::request() const noexcept {
        return _request;
    }

    inline bool RequestParser::isComplete() const noexcept {
        return _state == State::COMPLETE;
    }

    inline bool RequestParser::isIndeterminate() const noexcept {
        return !isComplete() && !isInvalid();
    }

    inline bool RequestParser::isInvalid() const noexcept {
        return _state == State::BAD_METHOD ||
               _state == State::BAD_PATH ||
               _state == State::BAD_VERSION ||
               _state == State::BAD_CRLF ||
               _state == State::BAD_HEADER ||
               _state == State::BAD_BODY;
    }

    // Request parsing.
    template<>
    inline bool RequestParser::_feed<Version::HTTP_1_1>(const char *data, const std::size_t length) noexcept {
        if (State::HTTP_BODY == _state) {
            if (length > _bufferLength) {
                _state = State::BAD_BODY;
                return false;
            }

            _request.body.append(data, length);
            _bufferLength -= length;

            if (static_cast<std::size_t>(0) == _bufferLength)
                _state = State::COMPLETE;

            return true;
        }

        for (auto i = static_cast<std::size_t>(0); i < length; ++i) {
            const char c = data[i];

            switch (_state) {
                case State::HTTP_METHOD:
                    if (' ' == c) {
                        try {
                            _request.method.value.assign(_buffer.data(), _bufferLength);
                        } catch (...) {
                            _state = State::BAD_METHOD;
                            return false;
                        }

                        if (!_request.method.isValid()) {
                            _state = State::BAD_METHOD;
                            return false;
                        }

                        _state = State::HTTP_PATH;
                        _bufferLength = static_cast<std::size_t>(0);
                        break;
                    }

                    _buffer[_bufferLength++] = c;
                    break;
                case State::HTTP_PATH:
                    if (' ' == c) {
                        if (static_cast<std::size_t>(0) == _bufferLength) {
                            _state = State::BAD_PATH;
                            return false;
                        }

                        _state = State::HTTP_VERSION_H;
                        _bufferLength = static_cast<std::size_t>(0);
                        break;
                    }

                    _buffer[_bufferLength++] = c;
                    break;
                case State::HTTP_VERSION_H:
                    if ('H' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HT;
                    break;
                case State::HTTP_VERSION_HT:
                    if ('T' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTT;
                    break;
                case State::HTTP_VERSION_HTT:
                    if ('T' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTTP;
                    break;
                case State::HTTP_VERSION_HTTP:
                    if ('P' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTTP_;
                    break;
                case State::HTTP_VERSION_HTTP_:
                    if ('/' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTTP_1;
                    break;
                case State::HTTP_VERSION_HTTP_1:
                    if ('1' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTTP_1_;
                    break;
                case State::HTTP_VERSION_HTTP_1_:
                    if ('.' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_VERSION_HTTP_1_1;
                    break;
                case State::HTTP_VERSION_HTTP_1_1:
                    if ('1' != c) {
                        _state = State::BAD_VERSION;
                        return false;
                    }

                    _state = State::HTTP_HEADER_CR;
                    break;
                case State::HTTP_HEADER_CR:
                    if (!RFC::IsCR(c)) {
                        _state = State::BAD_CRLF;
                        return false;
                    }

                    _state = State::HTTP_HEADER_LF;
                    break;
                case State::HTTP_HEADER_LF:
                    if (!RFC::IsLF(c)) {
                        _state = State::BAD_CRLF;
                        return false;
                    }

                    _state = State::HTTP_HEADER_START;
                    _bufferLength = static_cast<std::size_t>(0);
                    break;
                case State::HTTP_HEADER_START:
                    if (RFC::IsCR(c)) {
                        _state = State::HTTP_BODY_LF;
                        break;
                    }

                    _state = State::HTTP_HEADER;
                    _buffer[_bufferLength++] = c;
                    break;
                case State::HTTP_HEADER:
                    if (RFC::IsCR(c)) {
                        if (HeaderField header;
                            !header.parse(std::string_view(_buffer.data(), _bufferLength)) ||
                            nullptr == _request.headers.add(header)) {
                            _state = State::BAD_HEADER;
                            return false;
                        }

                        _state = State::HTTP_HEADER_LF;
                        break;
                    }

                    _buffer[_bufferLength++] = c;
                    break;
                case State::HTTP_BODY_LF:
                    if (!RFC::IsLF(c)) {
                        _state = State::BAD_CRLF;
                        return false;
                    }

                    if (const HeaderField *contentLength = _request.headers.get("Content-Length");
                        nullptr == contentLength) {
                        _bufferLength = static_cast<std::size_t>(0);
                    } else if (!contentLength->as(_bufferLength)) {
                        _state = State::BAD_BODY;
                        return false;
                    }

                    if (static_cast<std::size_t>(0) == _bufferLength) {
                        _state = State::COMPLETE;
                        break;
                    }

                    try {
                        _request.body.reserve(_bufferLength);
                    } catch (...) {
                        _state = State::BAD_BODY;
                        return false;
                    }

                    _state = State::HTTP_BODY;

                    try {
                        if (const std::size_t len = ((length - i) - static_cast<std::size_t>(1));
                            static_cast<std::size_t>(0) != len) {
                            _request.body.append(&data[i + static_cast<std::size_t>(1)], len);
                            _bufferLength -= len;
                        }

                        i = length;
                    } catch (...) {
                        _state = State::BAD_BODY;
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }

        return true;
    }

    inline bool RequestParser::feed(const char *data, const std::size_t length) noexcept {
        if (State::START == _state)
            _state = State::HTTP_METHOD;

        if (State::COMPLETE == _state) {
            _state = State::BAD_CRLF;
            return false;
        }

        return _feed<Version::HTTP_1_1>(data, length);
    }

    // Instance-based utility functions.
    inline void RequestParser::reset() noexcept {
        _state = State::START;
        _bufferLength = static_cast<std::size_t>(0);
        _request.reset();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_REQUEST_IMPL_PARSER_IPP
