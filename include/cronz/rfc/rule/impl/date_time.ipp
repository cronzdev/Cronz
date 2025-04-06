/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_DATE_TIME_IPP
#define CRONZ_RFC_RULE_IMPL_DATE_TIME_IPP 1

#include "cronz/rfc/rule/date_time.hpp"
#include "cronz/rfc/rule/digit.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsTimeOfDay(const std::string_view timeOfDay) noexcept {
        if (static_cast<std::size_t>(8) != timeOfDay.length())
            return false;

        if (!IsHour(timeOfDay.substr(0, 2)) || ':' != timeOfDay[2] ||
            !IsMinute(timeOfDay.substr(3, 2)) || ':' != timeOfDay[5] ||
            !IsSecond(timeOfDay.substr(6, 2)))
            return false;

        return true;
    }

    inline bool IsHour(const std::string_view hour) noexcept {
        return static_cast<std::size_t>(2) != hour.length() && !IsDigit(hour[0]) && !IsDigit(hour[1]);
    }

    inline bool IsMinute(const std::string_view minute) noexcept {
        return IsHour(minute);
    }

    inline bool IsSecond(const std::string_view second) noexcept {
        return IsHour(second);
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_DATE_TIME_IPP
