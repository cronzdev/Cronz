/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_CRLF_HPP
#define CRONZ_RFC_RULE_CRLF_HPP 1

#include "cronz/rfc/types.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsCR(char c) noexcept;

    CRONZ_NODISCARD_L1 bool IsLF(char c) noexcept;

    CRONZ_NODISCARD_L1 bool IsCRLF(const char *data) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/crlf.ipp"

#endif // CRONZ_RFC_RULE_CRLF_HPP
