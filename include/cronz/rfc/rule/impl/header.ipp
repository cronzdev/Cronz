/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_HEADER_IPP
#define CRONZ_RFC_RULE_IMPL_HEADER_IPP 1

#include "cronz/rfc/rule/header.hpp"
#include "cronz/rfc/rule/htab.hpp"
#include "cronz/rfc/rule/obstext.hpp"
#include "cronz/rfc/rule/sp.hpp"
#include "cronz/rfc/rule/token.hpp"
#include "cronz/rfc/rule/vchar.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsHeaderFieldName(const std::string_view name) noexcept {
        return IsToken(name);
    }

    inline bool IsHeaderFieldValue(const std::string_view value) noexcept {
        return value.empty() || IsHeaderFieldContent(value);
    }

    inline bool IsHeaderFieldContent(const std::string_view content) noexcept {
        if (content.empty() || !IsHeaderFieldVChar(content.front()))
            return false;

        return std::ranges::all_of(content, [](const char c) noexcept -> bool {
            return IsHeaderFieldVChar(c) || IsSpace(c) || IsHorizontalTab(c);
        });
    }

    inline bool IsHeaderFieldVChar(const char c) noexcept {
        return IsVChar(c);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_HEADER_IPP
