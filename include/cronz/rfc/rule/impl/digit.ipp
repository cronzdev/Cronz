/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_DIGIT_IPP
#define CRONZ_RFC_RULE_IMPL_DIGIT_IPP 1

#include "cronz/rfc/rule/digit.hpp"

#include <algorithm>

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsDigit(const char c) noexcept {
        return '0' <= c && c <= '9';
    }

    inline bool IsDigit(const std::string_view str) noexcept {
        return std::ranges::all_of(str, [](const char c) noexcept-> bool {
            return IsDigit(c);
        });
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_DIGIT_IPP
