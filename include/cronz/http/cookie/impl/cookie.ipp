/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_COOKIE_IMPL_COOKIE_IPP
#define CRONZ_HTTP_COOKIE_IMPL_COOKIE_IPP 1

#include "cronz/http/cookie/cookie.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Attributes.
    template<bool Renamable>
    inline const std::string &Cookie<Renamable>::name() const noexcept {
        return getName();
    }

    template<bool Renamable>
    inline const std::string &Cookie<Renamable>::getName() const noexcept {
        return _name;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_COOKIE_IMPL_COOKIE_IPP
