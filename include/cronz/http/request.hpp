/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_REQUEST_HPP
#define CRONZ_HTTP_REQUEST_HPP 1

#include "cronz/http/method/method.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class Request {
    public:
        Method method;
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/impl/request.ipp"

#endif // CRONZ_HTTP_REQUEST_HPP
