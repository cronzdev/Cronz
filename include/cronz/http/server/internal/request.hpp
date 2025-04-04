/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_INTERNAL_REQUEST_HPP
#define CRONZ_HTTP_SERVER_INTERNAL_REQUEST_HPP 1

#include "cronz/http/request.hpp"
#include "cronz/http/response.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    struct ServerRequestResponsePair {
        std::string id{};

        RequestParser requestParser{};

        Response response{};
        ResponseBuilder responseBuilder{};

        inline void reset() noexcept {
            id.clear();
            requestParser.reset();
        }
    };

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_SERVER_INTERNAL_REQUEST_HPP
