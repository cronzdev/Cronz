/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_SERVER_HPP
#define CRONZ_HTTP_SERVER_SERVER_HPP 1

#include "cronz/http/server/config.hpp"
#include "cronz/http/server/flags.hpp"
#include "cronz/http/version.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<HTTPVersion::Enum Version>
    class Server {
        static_assert((Version == HTTPVersion::HTTP_1_0) || (Version == HTTPVersion::HTTP_1_1),
                      "Only HTTP/1.x is supported.");
    };

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_SERVER_HPP
