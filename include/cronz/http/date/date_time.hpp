/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_DATE_TIME_HPP
#define CRONZ_HTTP_DATE_DATE_TIME_HPP 1

#include "cronz/http/date/date.hpp"
#include "cronz/http/date/time.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<DateTimeConfigurationFlags ConfigurationFlags>
    class DateTime final : public Date, public Time<ConfigurationFlags> {
        void _addDays(const MathType days) noexcept override {
            addDays(days);
        }
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/date_time.ipp"

#endif // CRONZ_HTTP_DATE_DATE_TIME_HPP
