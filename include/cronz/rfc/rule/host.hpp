/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_HOST_HPP
#define CRONZ_RFC_RULE_HOST_HPP 1

#include "cronz/rfc/types.hpp"

#include <string_view>

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsIPLiteral(std::string_view literal) noexcept;

    CRONZ_NODISCARD_L1 bool IsIPvFuture(std::string_view future) noexcept;

    CRONZ_NODISCARD_L1 bool IsRegName(std::string_view name) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/host.ipp"

#endif // CRONZ_RFC_RULE_HOST_HPP
