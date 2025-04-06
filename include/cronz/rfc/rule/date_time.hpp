/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_DATE_TIME_HPP
#define CRONZ_RFC_RULE_DATE_TIME_HPP 1

#include "cronz/rfc/types.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsTimeOfDay(std::string_view timeOfDay) noexcept;

    CRONZ_NODISCARD_L1 bool IsHour(std::string_view hour) noexcept;

    CRONZ_NODISCARD_L1 bool IsMinute(std::string_view minute) noexcept;

    CRONZ_NODISCARD_L1 bool IsSecond(std::string_view second) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/date_time.ipp"

#endif // CRONZ_RFC_RULE_DATE_TIME_HPP
