/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP
#define CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP 1

#include "cronz/http/server/extension/router.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructor.
    inline ServerRouterExtension::ServerRouterExtension(std::shared_mutex &mutex) noexcept : ServerExtension(mutex) {
    }

    // Destructor.
    inline ServerRouterExtension::~ServerRouterExtension() noexcept {
    }
CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP
