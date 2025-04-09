/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_TIME_OF_DAY_IPP
#define CRONZ_HTTP_DATE_IMPL_TIME_OF_DAY_IPP 1

#include "cronz/http/date/time_of_day.hpp"

#include "cronz/rfc/rule/date_time.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors & Destructors.
    inline TimeOfDayMillisecondsComponent::TimeOfDayMillisecondsComponent(
        const MillisecondsType milliseconds) noexcept {
        addMilliseconds(milliseconds);
    }

    // Properties.
    inline TimeOfDayMillisecondsComponent::MillisecondsType
    TimeOfDayMillisecondsComponent::milliseconds() const noexcept {
        return getMilliseconds();
    }

    inline TimeOfDayMillisecondsComponent::MillisecondsType
    TimeOfDayMillisecondsComponent::getMilliseconds() const noexcept {
        return _milliseconds;
    }

    inline void TimeOfDayMillisecondsComponent::milliseconds(const MathType milliseconds) noexcept {
        setMilliseconds(milliseconds);
    }

    inline void TimeOfDayMillisecondsComponent::setMilliseconds(const MathType milliseconds) noexcept {
        _milliseconds = static_cast<MillisecondsType>(milliseconds % static_cast<MathType>(MillisecondsDivisor));
        _addSeconds(static_cast<MathType>(milliseconds / static_cast<MathType>(MillisecondsDivisor)));
    }

    inline void TimeOfDayMillisecondsComponent::addMilliseconds(const MathType milliseconds) noexcept {
        setMilliseconds(milliseconds + static_cast<MathType>(_milliseconds));
    }

    // Parsing.
    inline bool TimeOfDayMillisecondsComponent::_parseMilliseconds(const std::string_view milliseconds) noexcept {
        if (static_cast<std::size_t>(3) < milliseconds.length() || !RFC::IsDigit(milliseconds))
            return false;

        _milliseconds = MillisecondsMin;

        auto index = static_cast<std::size_t>(0);
        while (index < milliseconds.length())
            _milliseconds = (_milliseconds * static_cast<MillisecondsType>(10)) +
                            static_cast<MillisecondsType>(milliseconds[index++] - '0');

        while (index < static_cast<std::size_t>(3)) {
            _milliseconds = (_milliseconds * static_cast<MillisecondsType>(10));
            ++index;
        }

        return true;
    }

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline TimeOfDay<ConfigurationFlags>::TimeOfDay(const TimeOfDay<IConfigurationFlags> &timeOfDay) noexcept {
        _assign(this, timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline TimeOfDay<ConfigurationFlags>::TimeOfDay(const MathType hours, const MathType minutes,
                                                    const MathType seconds) noexcept requires (!
        TimeOfDay<ConfigurationFlags>::AreMillisecondsEnabled) {
        addMinutes(minutes);
        addSeconds(seconds);
        addHours(hours);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline TimeOfDay<ConfigurationFlags>::TimeOfDay(const MathType hours, const MathType minutes,
                                                    const MathType seconds,
                                                    const MathType milliseconds) noexcept requires (
        TimeOfDay<ConfigurationFlags>::AreMillisecondsEnabled) {
        this->addMilliseconds(milliseconds);
        addSeconds(seconds);
        addMinutes(minutes);
        addHours(hours);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline TimeOfDay<ConfigurationFlags>::TimeOfDay(const std::string_view timeOfDay) noexcept {
        [[maybe_unused]] const bool result = _parseTimeOfDay(timeOfDay);
    }

    // Properties.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<typename T, T Max, T Divisor>
    inline typename TimeOfDay<ConfigurationFlags>::MathType
    TimeOfDay<ConfigurationFlags>::_s(T &v, MathType c) noexcept {
        auto u = static_cast<MathType>(0);

        if (static_cast<MathType>(0) > c) {
            while (static_cast<MathType>(0) > c) {
                c += static_cast<MathType>(Divisor);
                --u;
            }
        } else {
            while (static_cast<MathType>(Max) < c) {
                c -= static_cast<MathType>(Divisor);
                ++u;
            }
        }

        v = static_cast<T>(c);
        return u;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::HoursType TimeOfDay<ConfigurationFlags>::hours() const noexcept {
        return getHours();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::HoursType TimeOfDay<ConfigurationFlags>::getHours() const noexcept {
        return _hours;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::hours(const MathType hours) noexcept {
        setHours(hours);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::setHours(const MathType hours) noexcept {
        _addDays(_s<HoursType, HoursMax, HoursDivisor>(_hours, hours));
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::addHours(const MathType hours) noexcept {
        setHours(hours + static_cast<MathType>(_hours));
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::HoursType TimeOfDay<ConfigurationFlags>::minutes() const noexcept {
        return getMinutes();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::MinutesType TimeOfDay<
        ConfigurationFlags>::getMinutes() const noexcept {
        return _minutes;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::minutes(const MathType minutes) noexcept {
        setMinutes(minutes);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::setMinutes(const MathType minutes) noexcept {
        addHours(_s<MinutesType, MinutesMax, MinutesDivisor>(_minutes, minutes));
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::addMinutes(const MathType minutes) noexcept {
        setMinutes(minutes + static_cast<MathType>(_minutes));
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::HoursType TimeOfDay<ConfigurationFlags>::seconds() const noexcept {
        return getSeconds();
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::SecondsType TimeOfDay<
        ConfigurationFlags>::getSeconds() const noexcept {
        return _seconds;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::seconds(const MathType seconds) noexcept {
        setSeconds(seconds);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::setSeconds(const MathType seconds) noexcept {
        addMinutes(_s<SecondsType, SecondsMax, SecondsDivisor>(_seconds, seconds));
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    void TimeOfDay<ConfigurationFlags>::addSeconds(const MathType seconds) noexcept {
        setSeconds(seconds + static_cast<MathType>(_seconds));
    }

    // Instance-based utility functions.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::MathType TimeOfDay<ConfigurationFlags>::_n() const noexcept {
        if constexpr (AreMillisecondsEnabled)
            return static_cast<MathType>(_hours) * static_cast<MathType>(1'00'00'000) +
                   static_cast<MathType>(_minutes) * static_cast<MathType>(1'00'000) +
                   static_cast<MathType>(_seconds) * static_cast<MathType>(1'000) +
                   static_cast<MathType>(this->_milliseconds);
        else
            return static_cast<MathType>(_hours) * static_cast<MathType>(1'00'00) +
                   static_cast<MathType>(_minutes) * static_cast<MathType>(1'00) +
                   static_cast<MathType>(_seconds);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline void TimeOfDay<ConfigurationFlags>::_resetTimeOfDay() noexcept {
        _hours = HoursMin;
        _minutes = MinutesMin;
        _seconds = SecondsMin;

        if constexpr (AreMillisecondsEnabled)
            this->_milliseconds = this->MillisecondsMin;
    }

    // Operators.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<typename CompareOp, DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<
        ConfigurationFlags>::_compare(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return CompareOp()(_n(), timeOfDay._n());
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::TimeOfDayType &TimeOfDay<ConfigurationFlags>::operator=(
        const TimeOfDay<IConfigurationFlags> &timeOfDay) noexcept {
        _assign(this, timeOfDay);
        return *this;
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator==(
        const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::equal_to<> >(timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator!=(
        const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::not_equal_to<> >(timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator
    <(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::less<> >(timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator<=(
        const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::less_equal<> >(timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator
    >(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::greater<> >(timeOfDay);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags IConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::operator>=(
        const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept {
        return _compare<std::greater_equal<> >(timeOfDay);
    }

    // Parsing.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<typename T, T Min, T Max>
    inline bool TimeOfDay<ConfigurationFlags>::_parseTimeOfDayComponent(T &component, const char c1,
                                                                        const char c2) noexcept {
        if (!RFC::IsDigit(c1) || !RFC::IsDigit(c2))
            return false;

        component = static_cast<T>(c1 - '0') * static_cast<T>(10) +
                    static_cast<T>(c2 - '0');
        return (Min <= component && component <= Max);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline bool TimeOfDay<ConfigurationFlags>::_parseTimeOfDay(std::string_view timeOfDay) noexcept {
        if (static_cast<std::size_t>(5) > timeOfDay.length())
            goto parse_bad;

        if (!_parseTimeOfDayComponent<HoursType, HoursMin, HoursMax>(this->_hours, timeOfDay[0], timeOfDay[1]) ||
            ':' != timeOfDay[2] ||
            !_parseTimeOfDayComponent<MinutesType, MinutesMin, MinutesMax>(this->_minutes, timeOfDay[3], timeOfDay[4]))
            goto parse_bad;

        if (static_cast<std::size_t>(5) == timeOfDay.length())
            return true;

        if (static_cast<std::size_t>(8) > timeOfDay.length() ||
            ':' != timeOfDay[5] ||
            !_parseTimeOfDayComponent<SecondsType, SecondsMin, SecondsMax>(this->_seconds, timeOfDay[6], timeOfDay[7]))
            goto parse_bad;

        if (static_cast<std::size_t>(8) == timeOfDay.length())
            return true;

        if constexpr (AreMillisecondsEnabled) {
            if ('.' != timeOfDay[8])
                goto parse_bad;

            if (static_cast<std::size_t>(9) == timeOfDay.length())
                return true;

            timeOfDay.remove_prefix(static_cast<std::size_t>(9));
            if (!this->_parseMilliseconds(timeOfDay))
                goto parse_bad;
        } else {
            goto parse_bad;
        }

        return true;

    parse_bad:
        _resetTimeOfDay();
        return false;
    }

    // Static utility functions.
    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<auto Callback>
    inline typename TimeOfDay<ConfigurationFlags>::TimeOfDayType
    TimeOfDay<ConfigurationFlags>::_current(const std::chrono::system_clock::time_point &tp) noexcept {
        const std::time_t c = std::chrono::system_clock::to_time_t(tp);
        const std::tm *t = Callback(&c);

        if constexpr (AreMillisecondsEnabled) {
            return TimeOfDayType(
                static_cast<MathType>(t->tm_hour),
                static_cast<MathType>(t->tm_min),
                static_cast<MathType>(t->tm_sec),
                static_cast<MathType>(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).
                                      count() %
                                      static_cast<MathType>(TimeOfDayMillisecondsComponent::MillisecondsDivisor))
            );
        } else {
            return TimeOfDayType(
                static_cast<MathType>(t->tm_hour),
                static_cast<MathType>(t->tm_min),
                static_cast<MathType>(t->tm_sec)
            );
        }
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    template<DateTimeConfigurationFlags DstConfigurationFlags, DateTimeConfigurationFlags SrcConfigurationFlags>
    inline void TimeOfDay<ConfigurationFlags>::_assign(TimeOfDay<DstConfigurationFlags> &dst,
                                                       const TimeOfDay<SrcConfigurationFlags> &src) noexcept {
        dst._hours = src._hours;
        dst._minutes = src._minutes;
        dst._seconds = src._seconds;

        if constexpr (TimeOfDay<DstConfigurationFlags>::AreMillisecondsEnabled) {
            if constexpr (TimeOfDay<SrcConfigurationFlags>::AreMillisecondsEnabled)
                dst._milliseconds = src._milliseconds;
            else
                dst._milliseconds = TimeOfDay<DstConfigurationFlags>::MillisecondsMin;
        }
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::TimeOfDayType
    TimeOfDay<ConfigurationFlags>::CurrentTimeOfDay() noexcept {
        const auto tp = std::chrono::system_clock::now();
        return _current<std::localtime>(tp);
    }

    template<DateTimeConfigurationFlags ConfigurationFlags>
    inline typename TimeOfDay<ConfigurationFlags>::TimeOfDayType
    TimeOfDay<ConfigurationFlags>::CurrentTimeOfDay(const Zone &zone) noexcept {
        const auto tp = (std::chrono::system_clock::now() + std::chrono::minutes(zone.getTimezoneOffsetInMinutes()));
        return _current<std::gmtime>(tp);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_TIME_OF_DAY_IPP
