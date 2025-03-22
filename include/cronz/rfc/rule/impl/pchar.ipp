/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_PCHAR_IPP
#define CRONZ_RFC_RULE_IMPL_PCHAR_IPP 1

#include "cronz/rfc/rule/pchar.hpp"
#include "cronz/rfc/rule/delims.hpp"
#include "cronz/rfc/rule/hexdig.hpp"
#include "cronz/rfc/rule/unreserved.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsPChar(const char c) noexcept {
        return IsUnreserved(c) || '%' == c || IsHexDig(c) || IsSubDelim(c) || ':' == c || '@' == c;
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_PCHAR_IPP
