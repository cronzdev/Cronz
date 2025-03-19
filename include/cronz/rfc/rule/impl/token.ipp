/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_TOKEN_IPP
#define CRONZ_RFC_RULE_IMPL_TOKEN_IPP 1

#include "cronz/rfc/rule/token.hpp"

#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/digit.hpp"

#include <algorithm>

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsTokenChar(const char c) noexcept {
        return '!' == c || '#' == c || '$' == c || '%' == c || '&' == c || '\'' == c || '*' == c ||
               '+' == c || '-' == c || '.' == c || '^' == c || '_' == c || '`' == c || '|' == c || '~' == c
               || IsAlpha(c) || IsDigit(c);
    }

    inline bool IsToken(const std::string_view token) noexcept {
        return !token.empty() && std::ranges::all_of(token, IsTokenChar);
    }

    inline bool CompareTokens(const std::string_view token1, const std::string_view token2) noexcept {
        if (token1.length() != token2.length())
            return false;

        for (auto i = static_cast<std::size_t>(0); i < token1.length(); i++) {
            if (!CompareAlphaCaseInsensitive(token1[i], token2[i]))
                return false;
        }

        return true;
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_TOKEN_IPP
