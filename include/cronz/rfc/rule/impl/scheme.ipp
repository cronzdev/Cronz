/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_SCHEME_IPP
#define CRONZ_RFC_RULE_IMPL_SCHEME_IPP 1

#include "cronz/rfc/rule/scheme.hpp"

#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/digit.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsScheme(const std::string_view scheme) noexcept {
        if (scheme.empty() || !IsAlpha(scheme[0]))
            return false;

        return std::ranges::all_of(scheme, [](const char c) -> bool {
            return IsAlpha(c) || IsDigit(c) || '+' == c || '-' == c || '.' == c;
        });
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_SCHEME_IPP
