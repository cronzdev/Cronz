/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_HEXDIG_IPP
#define CRONZ_RFC_RULE_IMPL_HEXDIG_IPP 1

#include "cronz/rfc/rule/hexdig.hpp"

#include "cronz/rfc/rule/digit.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsHexDig(const char c) noexcept {
        return IsDigit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_HEXDIG_IPP
