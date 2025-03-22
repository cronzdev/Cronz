/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_DELIMS_IPP
#define CRONZ_RFC_RULE_IMPL_DELIMS_IPP 1

#include "cronz/rfc/rule/delims.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline const std::array<char, static_cast<std::size_t>(7)> GeneralDelimiters = {
        ':', '/', '?', '#', '[', ']', '@'
    };

    inline bool IsGenDelim(const char c) noexcept {
        return std::ranges::any_of(GeneralDelimiters, [c](const char delimiter) -> bool {
            return delimiter == c;
        });
    }

    inline const std::array<char, static_cast<std::size_t>(11)> SubcomponentDelimiters = {
        '!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '='
    };

    inline bool IsSubDelim(const char c) noexcept {
        return std::ranges::any_of(SubcomponentDelimiters, [c](const char delimiter) -> bool {
            return delimiter == c;
        });
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_DELIMS_IPP
