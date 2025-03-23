/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_CONNECTION_IMPL_ADDRESS_IPP
#define CRONZ_HTTP_CONNECTION_IMPL_ADDRESS_IPP 1

#include "cronz/http/connection/address.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Instance-based utility functions.
    inline void ConnectionAddress::reset() noexcept {
        address.clear();
        port = InvalidPort;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_CONNECTION_IMPL_ADDRESS_IPP
