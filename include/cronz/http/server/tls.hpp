/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_TLS_HPP
#define CRONZ_HTTP_SERVER_TLS_HPP 1

#include "cronz/http/server/types.hpp"
#include "cronz/http/internal/socket/stcp.hpp"

#if CRONZ_ENABLE_OPENSSL

CRONZ_BEGIN_HTTP_NAMESPACE
CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_ENABLE_OPENSSL

#include "cronz/http/server/impl/tls.ipp"

#endif // CRONZ_HTTP_SERVER_TLS_HPP
