/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_COOKIE_MANAGER_HPP
#define CRONZ_HTTP_COOKIE_MANAGER_HPP 1

#include "cronz/http/cookie/cookie.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class CookieManager final {
    public:
        using CookieType = ImmutableCookie;

        using CookieRefType = CookieType *;

        using CookieConstRefType = const CookieType *;

        using ArrayType = std::vector<CookieRefType>;

    private:
        // Properties.
        ArrayType _cookies{};

    public:
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/cookie/impl/manager.ipp"

#endif // CRONZ_HTTP_COOKIE_MANAGER_HPP
