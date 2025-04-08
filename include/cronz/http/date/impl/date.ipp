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

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    inline Date::Date(const MathType day, const MathType month, const MathType year) noexcept {
        setDate(day, month, year);
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

    inline void Date::setDate(const MathType day, const MathType month, const MathType year) noexcept {
        setYear(year);
        setMonth(month);
        setDay(year);
    }

    // Instance-based utility functions.
    inline bool Date::isLeapYear() const noexcept {
        return static_cast<YearType>(0) < _year &&
               ((static_cast<YearType>(0) == (_year % static_cast<YearType>(400))) ||
                ((static_cast<YearType>(0) == (_year % static_cast<YearType>(4))) &&
                 static_cast<YearType>(0) != (_year % static_cast<YearType>(100))));
    }

    inline Date::DayType Date::getDaysInMonth() const noexcept {
        switch (_month) {
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
                return isLeapYear() ? static_cast<DayType>(29) : static_cast<DayType>(28);
            default:
                return static_cast<DayType>(0);
        }
    }

    // Static utility functions.
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

    inline Date Date::Today() noexcept {
        const std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
        return _today<std::localtime>(tp);
    }

    inline Date Date::Today(const Zone &zone) noexcept {
        const auto tp = (std::chrono::system_clock::now() + std::chrono::minutes(zone.getTimezoneOffsetInMinutes()));
        return _today<std::gmtime>(tp);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_DATE_IPP
