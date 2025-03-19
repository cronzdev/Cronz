/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_CRLF_IPP
#define CRONZ_RFC_RULE_IMPL_CRLF_IPP 1

#include "cronz/rfc/rule/crlf.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsCR(const char c) noexcept {
        return static_cast<char>(0x0D) == c;
    }

    inline bool IsLF(const char c) noexcept {
        return static_cast<char>(0x0A) == c;
    }

    inline bool IsCRLF(const char *data) noexcept {
        return IsCR(data[0]) && IsLF(data[1]);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_CRLF_IPP
