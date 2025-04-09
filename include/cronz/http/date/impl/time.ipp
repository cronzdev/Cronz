/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_TIME_IPP
#define CRONZ_HTTP_DATE_IMPL_TIME_IPP 1

#include "cronz/http/date/time.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline Time<ConfigurationFlags>::Time(const TimeOfDayType &timeOfDay, const ZoneType &zone) noexcept
        : TimeOfDay<ConfigurationFlags>(timeOfDay), Zone(zone) {
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline Time<ConfigurationFlags>::Time(const std::string_view time) noexcept {
        [[maybe_unused]] const bool _ = this->_parseTime(time);
    }

    // Properties.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::TimeOfDayType Time<ConfigurationFlags>::timeOfDay() const noexcept {
        return getTimeOfDay();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::TimeOfDayType Time<ConfigurationFlags>::getTimeOfDay() const noexcept {
        return *this;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::ZoneType Time<ConfigurationFlags>::zone() const noexcept {
        return getZone();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::ZoneType Time<ConfigurationFlags>::getZone() const noexcept {
        return *this;
    }

    // Parsing.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool Time<ConfigurationFlags>::_parseTime(std::string_view time) noexcept {
        this->_resetTime();

        while (!time.empty() && ' ' == time.front())
            time.remove_prefix(static_cast<std::string_view::size_type>(1));

        while (!time.empty() && ' ' == time.back())
            time.remove_suffix(static_cast<std::string_view::size_type>(1));

        const char *const space = std::ranges::find(time, ' ');
        const std::string_view t(time.cbegin(), space);
        if (!this->_parseTimeOfDay(t))
            goto parse_bad;

        if (time.cend() == space)
            return true;

        time.remove_prefix(t.length());
        while (!time.empty() && ' ' == time.front())
            time.remove_prefix(static_cast<std::string_view::size_type>(1));

        if (!this->_parseTimezone(time))
            goto parse_bad;

        return true;

    parse_bad:
        this->_resetTime();
        return false;
    }

    // Instance-based utility functions.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline void Time<ConfigurationFlags>::_resetTime() noexcept {
        this->_resetTimeOfDay();
        this->_resetZone();
    }

    // Static utility functions.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::TimeType Time<ConfigurationFlags>::CurrentTime() noexcept {
        return TimeType(Time::CurrentTimeOfDay(), Zone::CurrentZone());
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_TIME_IPP
