/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_DOMAIN_HPP
#define CRONZ_RFC_RULE_DOMAIN_HPP 1

#include "cronz/rfc/types.hpp"

#include <string_view>

CRONZ_BEGIN_RFC_NAMESPACE
    inline constexpr std::size_t MAX_DOMAIN_LENGTH = static_cast<std::size_t>(255);

    CRONZ_NODISCARD_L1 bool IsDomain(std::string_view domain) noexcept;

    CRONZ_NODISCARD_L1 bool IsSubdomain(std::string_view subdomain) noexcept;

    CRONZ_NODISCARD_L1 bool IsLabel(std::string_view label) noexcept;

    CRONZ_NODISCARD_L1 bool IsLdhStr(std::string_view str) noexcept;

    CRONZ_NODISCARD_L1 bool IsLetDigHyp(char c) noexcept;

    CRONZ_NODISCARD_L1 bool IsLetDig(char c) noexcept;

    CRONZ_NODISCARD_L1 bool IsLetter(char c) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/domain.ipp"

#endif // CRONZ_RFC_RULE_DOMAIN_HPP
