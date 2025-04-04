/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_RESPONSE_RESPONSE_HPP
#define CRONZ_HTTP_RESPONSE_RESPONSE_HPP 1

#include "cronz/http/status_code.hpp"
#include "cronz/http/header.hpp"

#include <optional>

CRONZ_BEGIN_HTTP_NAMESPACE
    class Response {
    public:
        StatusCode status;

        HeaderManager headers;

        std::string body;

        void reset() noexcept;
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/response/impl/response.ipp"

#endif // CRONZ_HTTP_RESPONSE_RESPONSE_HPP
