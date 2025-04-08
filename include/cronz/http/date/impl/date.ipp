/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_DATE_IPP
#define CRONZ_HTTP_DATE_IMPL_DATE_IPP 1

#include "cronz/http/date/date.hpp"

#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/date_time.hpp"

#include <cstring>

CRONZ_BEGIN_HTTP_NAMESPACE
    // Static constants and types.
    inline const std::unordered_map<Date::DayOfWeek, std::string_view> Date::DayOfWeekNames = {
        {DayOfWeek::Sunday, Sunday}, {DayOfWeek::Monday, Monday}, {DayOfWeek::Tuesday, Tuesday},
        {DayOfWeek::Wednesday, Wednesday}, {DayOfWeek::Thursday, Thursday}, {DayOfWeek::Friday, Friday},
        {DayOfWeek::Saturday, Saturday}, {DayOfWeek::Invalid, ""}
    };

    inline const std::unordered_map<Date::DayOfWeek, std::string_view> Date::DayOfWeekNameAbbreviations = {
        {DayOfWeek::Sunday, Sun}, {DayOfWeek::Monday, Mon}, {DayOfWeek::Tuesday, Tue},
        {DayOfWeek::Wednesday, Wed}, {DayOfWeek::Thursday, Thu}, {DayOfWeek::Friday, Fri},
        {DayOfWeek::Saturday, Sat}, {DayOfWeek::Invalid, ""}
    };

    inline const std::array<Date::Month, static_cast<std::size_t>(12)> Date::Months = {
        Month::January, Month::February, Month::March, Month::April,
        Month::May, Month::June, Month::July, Month::August,
        Month::September, Month::October, Month::November, Month::December
    };

    inline const std::unordered_map<Date::Month, std::string_view> Date::MonthNames = {
        {Month::January, January}, {Month::February, February}, {Month::March, March},
        {Month::April, April}, {Month::May, May}, {Month::June, June},
        {Month::July, July}, {Month::August, August}, {Month::September, September},
        {Month::October, October}, {Month::November, November}, {Month::December, December},
        {Month::Invalid, ""}
    };

    inline const std::unordered_map<Date::Month, std::string_view> Date::MonthNameAbbreviations = {
        {Month::January, Jan}, {Month::February, Feb}, {Month::March, Mar},
        {Month::April, Apr}, {Month::May, May}, {Month::June, Jun},
        {Month::July, Jul}, {Month::August, Aug}, {Month::September, Sep},
        {Month::October, Oct}, {Month::November, Nov}, {Month::December, Dec},
        {Month::Invalid, ""}
    };

    // Constructors.
    inline Date::Date(const MathType day, const MathType month, const MathType year) noexcept {
        setDate(day, month, year);
    }

    inline Date::Date(const std::string_view date) noexcept {
        [[maybe_unused]] const bool _ = _parseDate(date);
    }

    // Properties.
    inline void Date::_setYear(const YearType year) noexcept {
        _year = static_cast<YearType>(year);

        if (static_cast<MonthType>(Month::February) == _month &&
            static_cast<DayType>(29) == _day && !isLeapYear())
            _day = static_cast<DayType>(28);
    }

    template<>
    inline void Date::_addMonths<false>(MathType months) noexcept {
        while (true) {
            if (static_cast<MathType>(_month) > months) {
                _month -= static_cast<MonthType>(months);
                return;
            }

            months -= static_cast<MathType>(_month);
            _month = static_cast<MonthType>(Month::December);

            if (static_cast<YearType>(YearMin) > --_year)
                _year = YearMax;
        }
    }

    template<>
    inline void Date::_addMonths<true>(MathType months) noexcept {
        months += static_cast<MathType>(_month);

        while (true) {
            if (months <= static_cast<MathType>(Month::December)) {
                _month = static_cast<MonthType>(months);
                break;
            }

            months -= static_cast<MathType>(Month::December);

            if (static_cast<YearType>(YearMax) < ++_year)
                _year = YearMin;
        }

        _day = std::min(_day, getDaysInMonth());
    }

    template<>
    inline void Date::_addDays<false>(MathType days) noexcept {
        while (true) {
            if (static_cast<MathType>(_day) > days) {
                _day -= static_cast<DayType>(days);
                return;
            }

            if (static_cast<MonthType>(Month::January) > --_month) {
                _month = static_cast<MonthType>(Month::December);
                if (YearMin > --_year)
                    _year = YearMax;
            }

            days -= static_cast<MathType>(_day);
            _day = getDaysInMonth();
        }
    }

    template<>
    inline void Date::_addDays<true>(MathType days) noexcept {
        days += static_cast<MathType>(_day);

        while (true) {
            const auto daysInMonth = static_cast<MathType>(getDaysInMonth());
            if (days <= daysInMonth) {
                _day = static_cast<DayType>(days);
                return;
            }

            days -= daysInMonth;

            if (static_cast<MonthType>(Month::December) < ++_month) {
                _month = static_cast<MonthType>(Month::January);
                if (YearMax < ++_year)
                    _year = YearMin;
            }
        }
    }

    inline Date::DayOfWeek Date::_getDayOfWeek() const noexcept {
        static constexpr std::array<DayType, static_cast<std::size_t>(12)> ToM = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

        const auto YY = static_cast<YearType>(_year - static_cast<YearType>(1));

        MonthType MM = ToM[_month - static_cast<MonthType>(1)];
        if (static_cast<MonthType>(Month::March) <= _month && isLeapYear())
            MM = static_cast<MonthType>((MM + static_cast<MonthType>(1)) % static_cast<MonthType>(7));

        const auto res = static_cast<DayType>(
            static_cast<MathType>(static_cast<MathType>(_day) + static_cast<MathType>(MM) + static_cast<MathType>(5) *
                                  static_cast<MathType>(YY % static_cast<YearType>(4)) + static_cast<MathType>(4) *
                                  static_cast<MathType>(YY % static_cast<YearType>(100)) + static_cast<MathType>(6) *
                                  static_cast<MathType>(YY % static_cast<YearType>(400))) % static_cast<MathType>(7));
        return static_cast<DayType>(DayOfWeek::Sunday) <= res && res <= static_cast<DayType>(DayOfWeek::Saturday)
                   ? static_cast<DayOfWeek>(res)
                   : DayOfWeek::Invalid;
    }

    inline Date::YearType Date::year() const noexcept {
        return getYear();
    }

    inline Date::YearType Date::getYear() const noexcept {
        return _year;
    }

    inline void Date::year(const MathType year) noexcept {
        setYear(year);
    }

    inline void Date::setYear(const MathType year) noexcept {
        _setYear((_year < YearMin) ? YearMin : (_year > YearMax) ? YearMax : static_cast<YearType>(year));
    }

    inline void Date::addYears(MathType years) noexcept {
        static constexpr YearType y = (YearMax - YearMin);

        while (years > static_cast<MathType>(YearMax))
            years -= static_cast<MathType>(y);

        _setYear(static_cast<YearType>(years));
    }

    inline Date::Month Date::month() const noexcept {
        return getMonth();
    }

    inline Date::Month Date::getMonth() const noexcept {
        return static_cast<Month>(_month);
    }

    inline void Date::month(const Month month) noexcept {
        setMonth(month);
    }

    inline void Date::setMonth(const Month month) noexcept {
        if (Month::Invalid == month)
            return;

        _month = static_cast<MonthType>(month);
        _day = std::min(_day, getDaysInMonth());
    }

    inline Date::MonthType Date::monthValue() const noexcept {
        return getMonthValue();
    }

    inline Date::MonthType Date::getMonthValue() const noexcept {
        return _month;
    }

    inline void Date::month(const MathType month) noexcept {
        setMonth(month);
    }

    inline void Date::setMonth(const MathType month) noexcept {
        if (static_cast<MathType>(0) == month)
            return _addMonths<false>(static_cast<MathType>(1));

        if (static_cast<MathType>(0) > month)
            return _addMonths<false>((-month) + static_cast<MathType>(1));

        if (month <= static_cast<MathType>(Month::December)) {
            _month = static_cast<MonthType>(month);
            _day = std::min(_day, getDaysInMonth());
            return;
        }

        _addMonths<true>(month - static_cast<MathType>(_month));
    }

    inline void Date::addMonths(const MathType months) noexcept {
        if (static_cast<MathType>(0) == months)
            return;

        return (static_cast<MathType>(0) < months) ? _addMonths<true>(months) : _addMonths<false>(-months);
    }

    inline Date::DayType Date::day() const noexcept {
        return getDay();
    }

    inline Date::DayType Date::getDay() const noexcept {
        return _day;
    }

    inline void Date::day(const MathType day) noexcept {
        return setDay(day);
    }

    inline void Date::setDay(const MathType day) noexcept {
        if (static_cast<DayType>(0) == day)
            return _addDays<false>(static_cast<MathType>(1));

        if (static_cast<DayType>(0) > day)
            return _addDays<false>((-day) + static_cast<MathType>(1));

        if (day <= static_cast<MathType>(getDaysInMonth())) {
            _day = static_cast<DayType>(day);
            return;
        }

        _addDays<true>(day - static_cast<MathType>(_day));
    }

    inline void Date::addDays(const MathType days) noexcept {
        if (static_cast<MathType>(0) == days)
            return;

        return (static_cast<MathType>(0) < days) ? _addDays<true>(days) : _addDays<false>(-days);
    }

    inline Date::DayOfWeek Date::dayOfWeek() const noexcept {
        return getDayOfWeek();
    }

    inline Date::DayOfWeek Date::getDayOfWeek() const noexcept {
        return _getDayOfWeek();
    }

    inline void Date::setDayOfWeek(const DayOfWeek dayOfWeek) noexcept {
        if (DayOfWeek::Invalid != dayOfWeek)
            addDays(static_cast<MathType>(_day) - static_cast<MathType>(getDayOfWeekValue()));
    }

    inline Date::DayType Date::getDayOfWeekValue() const noexcept {
        return static_cast<DayType>(getDayOfWeek());
    }

    inline void Date::setDayOfWeek(const DayType dayOfWeek) noexcept {
        if (static_cast<DayType>(DayOfWeek::Sunday) <= dayOfWeek &&
            dayOfWeek <= static_cast<DayType>(DayOfWeek::Saturday))
            addDays(static_cast<MathType>(_day) - static_cast<MathType>(dayOfWeek));
    }

    inline void Date::setDate(const MathType day, const MathType month, const MathType year) noexcept {
        setYear(year);
        setMonth(month);
        setDay(year);
    }

    // Instance-based utility functions.
    inline void Date::_resetDate() noexcept {
        _year = YearMin;
        _month = static_cast<MonthType>(Month::January);
        _day = static_cast<DayType>(1);
    }

    inline bool Date::isLeapYear() const noexcept {
        return _isLeapYear(_year);
    }

    inline Date::DayType Date::getDaysInMonth() const noexcept {
        return _getDaysInMonth(_year, _month);
    }

    // Parsing.
    inline Date::DayOfWeek Date::_parseDayOfWeek(const std::string_view dayOfWeek) noexcept {
        if (static_cast<std::size_t>(3) != dayOfWeek.length())
            return DayOfWeek::Invalid;

        for (const auto &[d, s]: DayOfWeekNameAbbreviations) {
            if (_c(dayOfWeek.data(), s.data()))
                return static_cast<DayOfWeek>(d);
        }

        return DayOfWeek::Invalid;
    }

    inline bool Date::_parseDay(const std::string_view day) noexcept {
        if (static_cast<std::size_t>(2) != day.length() || !RFC::IsDigit(day))
            return false;

        _day = _p<DayType>(day);
        return true;
    }

    inline bool Date::_parseMonth(const std::string_view month) noexcept {
        if (static_cast<std::size_t>(3) != month.length())
            return false;

        for (const auto &[m, s]: MonthNameAbbreviations) {
            if (_c(month.data(), s.data())) {
                _month = static_cast<MonthType>(m);
                return true;
            }
        }

        return false;
    }

    inline bool Date::_parseYear(const std::string_view year) noexcept {
        if (static_cast<std::size_t>(4) != year.length() || !RFC::IsDigit(year))
            return false;

        _year = _p<YearType>(year);
        return true;
    }

    inline bool Date::_parseDate(std::string_view date) noexcept {
        const bool hasDayOfWeek = (static_cast<std::size_t>(16) == date.length());
        if (!hasDayOfWeek && static_cast<std::size_t>(11) != date.length())
            return false;

        const DayOfWeek dayOfWeek = (hasDayOfWeek ? _parseDayOfWeek(date.substr(0, 3)) : DayOfWeek::Invalid);
        if (hasDayOfWeek) {
            if (DayOfWeek::Invalid == dayOfWeek)
                return false;

            date.remove_prefix(static_cast<std::size_t>(5));
        }

        if (!_parseDay(date.substr(0, 2)) || ' ' != date[2] ||
            !_parseMonth(date.substr(3, 3)) || ' ' != date[6] ||
            !_parseYear(date.substr(7, 4)) ||
            !IsDateValid(_day, _month, _year) ||
            (hasDayOfWeek && dayOfWeek != _getDayOfWeek())) {
            _resetDate();
            return false;
        }

        return true;
    }

    // Operators.
    inline Date::MathType Date::_n() const noexcept {
        return static_cast<MathType>(_year) * static_cast<MathType>(1'00'00) +
               static_cast<MathType>(_month) * static_cast<MathType>(1'00) +
               static_cast<MathType>(_day);
    }

    template<typename CompareOp>
    inline bool Date::_compare(const Date &date) const noexcept {
        return CompareOp()(_n(), date._n());
    }

    inline bool Date::operator==(const Date &date) const noexcept {
        return _compare<std::equal_to<> >(date);
    }

    inline bool Date::operator!=(const Date &date) const noexcept {
        return _compare<std::not_equal_to<> >(date);
    }

    inline bool Date::operator<(const Date &date) const noexcept {
        return _compare<std::less<> >(date);
    }

    inline bool Date::operator<=(const Date &date) const noexcept {
        return _compare<std::less_equal<> >(date);
    }

    inline bool Date::operator>(const Date &date) const noexcept {
        return _compare<std::greater<> >(date);
    }

    inline bool Date::operator>=(const Date &date) const noexcept {
        return _compare<std::greater_equal<> >(date);
    }

    // Static utility functions.
    inline bool Date::_isLeapYear(const YearType year) noexcept {
        return static_cast<YearType>(0) < year &&
               ((static_cast<YearType>(0) == (year % static_cast<YearType>(400))) ||
                ((static_cast<YearType>(0) == (year % static_cast<YearType>(4))) &&
                 static_cast<YearType>(0) != (year % static_cast<YearType>(100))));
    }

    inline Date::DayType Date::_getDaysInMonth(const YearType year, const MonthType month) noexcept {
        switch (month) {
            case static_cast<MonthType>(Month::January):
            case static_cast<MonthType>(Month::March):
            case static_cast<MonthType>(Month::May):
            case static_cast<MonthType>(Month::July):
            case static_cast<MonthType>(Month::August):
            case static_cast<MonthType>(Month::October):
            case static_cast<MonthType>(Month::December):
                return static_cast<DayType>(31);
            case static_cast<MonthType>(Month::April):
            case static_cast<MonthType>(Month::June):
            case static_cast<MonthType>(Month::September):
            case static_cast<MonthType>(Month::November):
                return static_cast<DayType>(30);
            case static_cast<MonthType>(Month::February):
                return _isLeapYear(year) ? static_cast<DayType>(29) : static_cast<DayType>(28);
            default:
                return static_cast<DayType>(0);
        }
    }

    template<auto Callback>
    inline Date Date::_today(const std::chrono::system_clock::time_point tp) noexcept {
        const std::time_t n = std::chrono::system_clock::to_time_t(tp);
        const std::tm *t = Callback(&n);

        Date date;
        date._year = static_cast<YearType>(t->tm_year + static_cast<YearType>(1900));
        date._month = static_cast<MonthType>(t->tm_mon + static_cast<MonthType>(1));
        date._day = static_cast<DayType>(t->tm_mday);

        return date;
    }

    inline bool Date::_c(const char *s1, const char *s2) noexcept {
        return 0 == std::memcmp(s1, s2, static_cast<std::size_t>(3));
    }

    template<typename T>
    inline T Date::_p(const std::string_view s) noexcept {
        T t = static_cast<T>(0);

        for (const char c: s)
            t = (t * static_cast<T>(10)) + static_cast<T>(c - '0');

        return t;
    }

    inline Date Date::Today() noexcept {
        const std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
        return _today<std::localtime>(tp);
    }

    inline Date Date::Today(const Zone &zone) noexcept {
        const auto tp = (std::chrono::system_clock::now() + std::chrono::minutes(zone.getTimezoneOffsetInMinutes()));
        return _today<std::gmtime>(tp);
    }

    inline bool Date::IsDateValid(const MathType day, const MathType month, const MathType year) noexcept {
        if (static_cast<MathType>(YearMin) > year || year > static_cast<MathType>(YearMax))
            return false;

        if (static_cast<MathType>(static_cast<MonthType>(Month::January)) > month ||
            month > static_cast<MathType>(static_cast<MonthType>(Month::December)))
            return false;

        return static_cast<MathType>(0) < day && day <= static_cast<MathType>(_getDaysInMonth(year, month));
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_DATE_IPP
