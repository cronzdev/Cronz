/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_REQUEST_IMPL_REQUEST_IPP
#define CRONZ_HTTP_REQUEST_IMPL_REQUEST_IPP 1

#include "cronz/http/request/request.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Instance-based utility functions.
    inline void Request::reset() noexcept {
        method.value.clear();
        headers.clear();
        uri.clear();
        body.clear();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_REQUEST_IMPL_REQUEST_IPP
