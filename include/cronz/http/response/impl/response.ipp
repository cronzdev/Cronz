/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_RESPONSE_IMPL_RESPONSE_IPP
#define CRONZ_HTTP_RESPONSE_IMPL_RESPONSE_IPP 1

#include "cronz/http/response/response.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    inline void Response::reset() noexcept {
        status = StatusCode::OK;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_RESPONSE_IMPL_RESPONSE_IPP
