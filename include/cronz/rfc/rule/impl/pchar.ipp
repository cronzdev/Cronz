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
    inline bool IsPChar(const char c) noexcept {
        return IsUnreserved(c) || '%' == c || IsHexDig(c) || IsSubDelim(c) || ':' == c || '@' == c;
    }

    inline bool IsPChar(const std::string_view str) noexcept {
        for (auto i = static_cast<std::size_t>(0); i < str.size(); ++i) {
            if (const char c = str[i];
                IsUnreserved(c) || IsHexDig(c) || IsSubDelim(c) || ':' == c || '@' == c)
                continue;

            if (IsPctEncoded(str, i)) {
                i += static_cast<std::size_t>(2);
                continue;
            }

            return false;
        }

        return true;
    }

    inline bool IsPctEncoded(const std::string_view str, const std::size_t offset) noexcept {
        if ((static_cast<std::size_t>(2) + offset) >= str.size())
            return false;

        return '%' == str[offset] &&
               IsHexDig(str[offset + static_cast<std::size_t>(1)]) &&
               IsHexDig(str[offset + static_cast<std::size_t>(2)]);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_PCHAR_IPP
