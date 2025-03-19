/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_SP_IPP
#define CRONZ_RFC_RULE_IMPL_SP_IPP 1

#include "cronz/rfc/rule/sp.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsSpace(const char c) noexcept {
        return static_cast<char>(0x20) == c;
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_SP_IPP
