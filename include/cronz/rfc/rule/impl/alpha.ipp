/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_ALPHA_IPP
#define CRONZ_RFC_RULE_IMPL_ALPHA_IPP 1

#include "cronz/rfc/rule/alpha.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsAlpha(const char c) noexcept {
        return IsAlphaLower(c) || IsAlphaUpper(c);
    }

    inline bool IsAlphaLower(const char c) noexcept {
        return 'a' <= c && c <= 'z';
    }

    inline bool IsAlphaUpper(const char c) noexcept {
        return 'A' <= c && c <= 'Z';
    }

    inline char ToAlphaLower(const char c) noexcept {
        return IsAlphaUpper(c) ? c + 32 : c;
    }

    inline char ToAlphaUpper(const char c) noexcept {
        return IsAlphaLower(c) ? c - 32 : c;
    }

    inline bool CompareAlphaCaseInsensitive(const std::string_view s1, const std::string_view s2) noexcept {
        return (s1.length() == s2.length()) &&
               std::ranges::equal(s1, s2, [](const char c1, const char c2) noexcept -> bool {
                   return CompareAlphaCaseInsensitive(c1, c2);
               });
    }

    inline bool CompareAlphaCaseInsensitive(const char c1, const char c2) noexcept {
        return ToAlphaLower(c1) == ToAlphaLower(c2);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_ALPHA_IPP
