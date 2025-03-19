/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_OBSTEXT_IPP
#define CRONZ_RFC_RULE_IMPL_OBSTEXT_IPP 1

#include "cronz/rfc/rule/obstext.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    template<typename CharType>
        requires std::same_as<CharType, char> || std::same_as<CharType, unsigned char>
    inline bool IsObsoleteText(CharType c) noexcept {
        if constexpr (std::is_same_v<char, CharType>)
            return IsObsoleteText(static_cast<unsigned char>(c));

        return static_cast<unsigned char>(0x80) <= c && c <= static_cast<unsigned char>(0xFF);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_OBSTEXT_IPP
