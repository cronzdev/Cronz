/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_DELIMS_HPP
#define CRONZ_RFC_RULE_DELIMS_HPP 1

#include "cronz/rfc/types.hpp"

#include <array>

CRONZ_BEGIN_RFC_NAMESPACE
    extern const std::array<char, static_cast<std::size_t>(7)> GeneralDelimiters;

    CRONZ_NODISCARD_L1 bool IsGenDelim(char c) noexcept;

    extern const std::array<char, static_cast<std::size_t>(11)> SubcomponentDelimiters;

    CRONZ_NODISCARD_L1 bool IsSubDelim(char c) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/delims.ipp"

#endif // CRONZ_RFC_RULE_DELIMS_HPP
