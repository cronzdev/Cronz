/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_DATE_TIME_IPP
#define CRONZ_HTTP_DATE_IMPL_DATE_TIME_IPP 1

#include "cronz/http/date/date_time.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline DateTime<
        ConfigurationFlags>::DateTime(const Date &date, const TimeType &time) noexcept : Date(date),
        DateTime<ConfigurationFlags>::TimeType(time) {
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline DateTime<ConfigurationFlags>::DateTime(const std::string_view dateTime) noexcept {
        [[maybe_unused]] const bool _ = _parseDateTime(dateTime);
    }

    // Properties.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<bool IncludeMilliseconds, Date::YearType FirstYear>
    typename DateTime<ConfigurationFlags>::TimestampType DateTime<ConfigurationFlags>::_timestamp() const noexcept {
        constexpr auto precision = static_cast<TimestampType>(IncludeMilliseconds ? 1000 : 1);

        auto ts = static_cast<TimestampType>(0);

        Date::YearType y = FirstYear;
        while (y != this->year()) {
            ts += static_cast<Date::YearType>(Date::_isLeapYear(y) ? 366 : 365);
            ++y;
        }

        for (auto m = static_cast<MonthType>(Month::January); m < Date::getMonthValue(); ++m)
            ts += Date::_getDaysInMonth(y, m);

        ts += static_cast<TimestampType>(getDay()) - static_cast<TimestampType>(1);

        ts *= (static_cast<TimestampType>(86400) * precision);

        ts += static_cast<TimestampType>(this->getHours()) * static_cast<TimestampType>(3600 * precision);
        ts += static_cast<TimestampType>(this->getMinutes()) * static_cast<TimestampType>(60 * precision);
        ts += static_cast<TimestampType>(this->getSeconds()) * precision;

        if constexpr (IncludeMilliseconds &&
                      CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<ConfigurationFlags>())
            ts += static_cast<TimestampType>(this->getMilliseconds());

        return ts;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::DateType DateTime<ConfigurationFlags>::date() const noexcept {
        return getDate();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::DateType DateTime<ConfigurationFlags>::getDate() const noexcept {
        return *this;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimeType DateTime<ConfigurationFlags>::time() const noexcept {
        return getTime();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimeType DateTime<ConfigurationFlags>::getTime() const noexcept {
        return *this;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimestampType
    DateTime<ConfigurationFlags>::timestamp() const noexcept {
        return getTimestamp();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimestampType
    DateTime<ConfigurationFlags>::getTimestamp() const noexcept {
        return _timestamp<CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<ConfigurationFlags>(), Date::YearMin>();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimestampType
    DateTime<ConfigurationFlags>::getTimestampInSeconds() const noexcept {
        return _timestamp<false, Date::YearMin>();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::TimestampType
    DateTime<ConfigurationFlags>::getTimestampInMilliseconds() const noexcept {
        return _timestamp<true, Date::YearMin>();
    }

    // Parsing.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::_parseDateTime(std::string_view dateTime) noexcept {
        if (const auto pos = dateTime.find_first_not_of(' ');
            std::string_view::npos != pos)
            dateTime.remove_prefix(pos);

        if (const auto pos = dateTime.find_last_not_of(' ');
            std::string_view::npos != pos)
            dateTime.remove_suffix(dateTime.length() - pos - static_cast<std::size_t>(1));

        if (static_cast<std::size_t>(17) > dateTime.length())
            return false;

        const auto dateLength = (std::string_view::npos != dateTime.find(','))
                                    ? static_cast<std::size_t>(16)
                                    : static_cast<std::size_t>(11);

        if (!DateType::_parseDate(dateTime.substr(static_cast<std::size_t>(0), dateLength)) ||
            ' ' != dateTime[dateLength] ||
            !TimeType::_parseTime(dateTime.substr(dateLength + static_cast<std::size_t>(1))))
            goto parse_bad;

        return true;

    parse_bad:
        _resetDateTime();
        return false;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline void DateTime<ConfigurationFlags>::_resetDateTime() noexcept {
        DateType::_resetDate();
        TimeType::_resetTime();
    }

    // Stringification.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::_stringify(const DateTime<ConfigurationFlags> &dt, std::string &str,
                                                         std::size_t &offset) const noexcept {
        constexpr auto l = static_cast<std::size_t>(29);

        if (const std::size_t len = (l + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (const std::bad_alloc &) {
                return false;
            }
        }

        const std::string_view dayOfWeek = DateType::DayOfWeekNameAbbreviations.at(dt.getDayOfWeek());
        const std::string_view month = DateType::MonthNameAbbreviations.at(dt.getMonth());

        const auto res = std::format_to_n(&str[offset], l, "{:3s}, {:02d} {:3s} {:04d} {:02d}:{:02d}:{:02d} GMT",
                                          dayOfWeek, dt.getDay(), month, dt.getYear(), dt.getHours(), dt.getMinutes(),
                                          dt.getSeconds());
        if (res.size != l)
            return false;

        offset = static_cast<std::size_t>(l);
        return true;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline std::string DateTime<ConfigurationFlags>::stringify() const noexcept {
        std::string str;
        [[maybe_unused]] const bool _ = stringify(str);
        return str;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (static_cast<typename TimeType::ZoneType::ZoneOffsetType>(0) == this->getTimezoneOffsetInMinutes())
            return _stringify(*this, str, offset);

        DateTimeType dt = *this;
        dt.adjustZone(TimeType::ZoneType::GMT);
        return _stringify(dt, str, offset);
    }

    // Operators.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags, typename CompareOp>
    inline bool DateTime<ConfigurationFlags>::_c(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        constexpr bool ms = (CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<ConfigurationFlags>() &&
                             CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<IConfigurationFlags>());
        constexpr Date::YearType fy = Date::YearMin;

        return CompareOp{}(_timestamp<ms, fy>(), dateTime.template _timestamp<ms, fy>());
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator==(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::equal_to<> >(dateTime);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator!=(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::not_equal_to<> >(dateTime);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator<(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::less<> >(dateTime);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator<=(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::less_equal<> >(dateTime);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator>(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::greater<> >(dateTime);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool DateTime<ConfigurationFlags>::operator>=(const DateTime<IConfigurationFlags> &dateTime) const noexcept {
        return _c<IConfigurationFlags, std::greater_equal<> >(dateTime);
    }

    // Static utility functions.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename DateTime<ConfigurationFlags>::DateTimeType DateTime<ConfigurationFlags>::Now() noexcept {
        return DateTime<ConfigurationFlags>(Date::Today(), TimeType::CurrentTime());
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_DATE_TIME_IPP
