/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_PCHAR_HPP
#define CRONZ_RFC_RULE_PCHAR_HPP 1

#include "cronz/rfc/types.hpp"

#include <string_view>

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsPChar(char c) noexcept;

    CRONZ_NODISCARD_L1 bool IsPChar(std::string_view str) noexcept;

    CRONZ_NODISCARD_L1 bool IsPctEncoded(std::string_view str, std::size_t offset) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/pchar.ipp"

#endif // CRONZ_RFC_RULE_PCHAR_HPP
