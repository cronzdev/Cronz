/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_HOST_IPP
#define CRONZ_RFC_RULE_IMPL_HOST_IPP 1

#include "cronz/rfc/rule/host.hpp"

#include "cronz/rfc/rule/delims.hpp"
#include "cronz/rfc/rule/hexdig.hpp"
#include "cronz/rfc/rule/unreserved.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsRegName(const std::string_view name) noexcept {
        auto i = static_cast<std::size_t>(0);
        while (i < name.length()) {
            const char c = name[i++];
            if (IsUnreserved(c) || IsSubDelim(c))
                continue;

            if ('%' == c) {
                if (!IsHexDig(name[i]) ||
                    !IsHexDig(name[i + static_cast<std::size_t>(1)]))
                    return false;

                i += static_cast<std::size_t>(2);
            }

            return false;
        }

        return name.length() == i;
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_HOST_IPP
