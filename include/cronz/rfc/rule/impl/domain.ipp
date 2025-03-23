/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_DOMAIN_IPP
#define CRONZ_RFC_RULE_IMPL_DOMAIN_IPP 1

#include "cronz/rfc/rule/domain.hpp"

#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/digit.hpp"

#include <algorithm>

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsDomain(const std::string_view domain) noexcept {
        return static_cast<std::size_t>(255) >= domain.length() &&
               (IsSubdomain(domain) ||
                (static_cast<std::size_t>(1) == domain.length() && ' ' == domain.front()));
    }

    inline bool IsSubdomain(const std::string_view subdomain) noexcept {
        const char *const beg = subdomain.cbegin();
        const char *const end = subdomain.cend();

        const char *pos = beg;

        while (pos < end) {
            const char *const dot = std::ranges::find(pos, end, '.');

            if (const std::string_view label(pos, dot);
                !IsLabel(label))
                return false;

            pos = dot + static_cast<std::ptrdiff_t>(1);
        }

        return true;
    }

    inline bool IsLabel(const std::string_view label) noexcept {
        if (label.empty() || static_cast<std::size_t>(63) < label.length())
            return false;

        auto i = static_cast<std::size_t>(0);
        if (!IsLetter(label[i++]))
            return false;

        if (i == label.length())
            return true;

        return IsLdhStr(label) && IsLetDig(label.back());
    }

    inline bool IsLdhStr(std::string_view str) noexcept {
        return !str.empty() && std::ranges::all_of(str, [](const char c) -> bool {
            return IsLetDigHyp(c);
        });
    }

    inline bool IsLetDigHyp(const char c) noexcept {
        return IsLetDig(c) || '-' == c;
    }

    inline bool IsLetDig(const char c) noexcept {
        return IsLetter(c) || IsDigit(c);
    }

    inline bool IsLetter(const char c) noexcept {
        return IsAlpha(c);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_DOMAIN_IPP
