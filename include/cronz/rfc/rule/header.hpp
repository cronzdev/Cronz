/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_HEADER_HPP
#define CRONZ_RFC_RULE_HEADER_HPP 1

#include "cronz/rfc/types.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsHeaderFieldName(std::string_view name) noexcept;

    CRONZ_NODISCARD_L1 bool IsHeaderFieldValue(std::string_view value) noexcept;

    CRONZ_NODISCARD_L1 bool IsHeaderFieldContent(std::string_view content) noexcept;

    CRONZ_NODISCARD_L1 bool IsHeaderFieldVChar(char c) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/header.ipp"

#endif // CRONZ_RFC_RULE_HEADER_HPP
