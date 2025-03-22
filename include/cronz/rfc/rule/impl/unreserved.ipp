/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_UNRESERVED_IPP
#define CRONZ_RFC_RULE_IMPL_UNRESERVED_IPP 1

#include "cronz/rfc/rule/unreserved.hpp"
#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/digit.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsUnreserved(const char c) noexcept {
        return IsAlpha(c) || IsDigit(c) || '-' == c || '.' == c || '_' == c || '~' == c;
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_UNRESERVED_IPP
