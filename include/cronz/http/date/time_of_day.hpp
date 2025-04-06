/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_TIME_OF_DAY_HPP
#define CRONZ_HTTP_DATE_TIME_OF_DAY_HPP 1

#include "cronz/http/date/flags.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Time of day milliseconds component.
     * @class TimeOfDayMillisecondsComponent
     */
    class TimeOfDayMillisecondsComponent {
    public:
        /**
         * @name Static constants and type definitions.
         */
        /** @{ */
        /**
         * @brief Milliseconds type.
         */
        using MillisecondsType = std::int_fast16_t;

        /**
         * @brief Math type.
         */
        using MathType = std::int_fast64_t;

        /**
         * @brief Milliseconds maximum value.
         */
        inline static constexpr MillisecondsType MillisecondsMax = static_cast<MillisecondsType>(999);

        /**
         * @brief Milliseconds minimum value.
         */
        inline static constexpr MillisecondsType MillisecondsMin = static_cast<MillisecondsType>(0);

        /**
         * @brief Milliseconds divisor.
         */
        inline static constexpr MillisecondsType MillisecondsDivisor =
                MillisecondsMax + static_cast<MillisecondsType>(1);

        /** @} */
    protected:
        // Constructors & Destructors.
        TimeOfDayMillisecondsComponent() noexcept = default;

        explicit TimeOfDayMillisecondsComponent(MillisecondsType milliseconds) noexcept;

        ~TimeOfDayMillisecondsComponent() noexcept = default;

        // Properties.
        MillisecondsType _milliseconds = MillisecondsMin;

        // Virtual.
        virtual void _addSeconds(MathType) noexcept {
        }

        // Parsing.
        CRONZ_NODISCARD_L1 bool _parseMilliseconds(std::string_view milliseconds) noexcept;

    public:
        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the milliseconds.
         * @return The milliseconds.
         */
        CRONZ_NODISCARD_L1 MillisecondsType milliseconds() const noexcept;

        /**
         * @brief Returns the milliseconds.
         * @return The milliseconds.
         */
        CRONZ_NODISCARD_L1 MillisecondsType getMilliseconds() const noexcept;

        /**
         * @brief Changes the milliseconds.
         * @param[in] milliseconds The milliseconds value to be assigned.
         */
        void milliseconds(MathType milliseconds) noexcept;

        /**
         * @brief Changes the milliseconds.
         * @param[in] milliseconds The milliseconds value to be assigned.
         */
        void setMilliseconds(MathType milliseconds) noexcept;

        /**
         * @brief Changes the milliseconds.
         * @param[in] milliseconds Milliseconds to be added.
         */
        void addMilliseconds(MathType milliseconds) noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    struct TimeOfDayMillisecondsComponentDummy {
    };

CRONZ_END_HTTP_INTERNAL_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Time of day class.
     * @tparam ConfigurationFlags The configuration flags.
     * @class TimeOfDay
     */
    template<DateConfigurationFlags ConfigurationFlags = DefaultDateConfigurationFlags>
    class TimeOfDay : public std::conditional_t<
                CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<ConfigurationFlags>(),
                TimeOfDayMillisecondsComponent,
                CRONZ_HTTP_NAMESPACE_INTERNAL::TimeOfDayMillisecondsComponentDummy> {
    public:
        /**
         * @name Static constants and type definitions.
         */
        /** @{ */
        /**
         * @brief Tells whether milliseconds are enabled.
         * @remark This is a compile-time constant.
         */
        inline static constexpr bool AreMillisecondsEnabled =
                CRONZ_HTTP_NAMESPACE_INTERNAL::AreMillisecondsEnabled<ConfigurationFlags>();

        /**
         * @brief Hours type.
         * @type std::int_fast8_t HoursType
         */
        using HoursType = std::int_fast8_t;

        /**
         * @brief Minutes type.
         * @type std::int_fast8_t MinutesType
         */
        using MinutesType = std::int_fast8_t;

        /**
         * @brief Seconds type.
         * @type std::int_fast8_t SecondsType
         */
        using SecondsType = std::int_fast8_t;

        /**
         * @brief Math type.
         * @type std::int_fast64_t MathType
         */
        using MathType = std::int_fast64_t;

        /**
         * @brief Time of day type.
         * @type TimeOfDay<AllowLeapSecond, AllowMilliseconds> TimeOfDayType
         */
        using TimeOfDayType = TimeOfDay<ConfigurationFlags>;

        /**
         * @brief Hours maximum value.
         */
        inline static constexpr HoursType HoursMax = static_cast<HoursType>(23);

        /**
         * @brief Hours minimum value.
         */
        inline static constexpr HoursType HoursMin = static_cast<HoursType>(0);

        /**
         * @brief Hours divisor.
         */
        inline static constexpr HoursType HoursDivisor = HoursMax + static_cast<HoursType>(1);

        /**
         * @brief Minutes maximum value.
         */
        inline static constexpr MinutesType MinutesMax = static_cast<MinutesType>(59);

        /**
         * @brief Minutes minimum value.
         */
        inline static constexpr MinutesType MinutesMin = static_cast<MinutesType>(0);

        /**
         * @brief Minutes divisor.
         */
        inline static constexpr MinutesType MinutesDivisor = MinutesMax + static_cast<MinutesType>(1);

        /**
         * @brief Seconds maximum value.
         */
        inline static constexpr SecondsType SecondsMax = static_cast<SecondsType>(59);

        /**
         * @brief Seconds minimum value.
         */
        inline static constexpr SecondsType SecondsMin = static_cast<SecondsType>(0);

        /**
         * @brief Seconds divisor.
         */
        inline static constexpr SecondsType SecondsDivisor = SecondsMax + static_cast<SecondsType>(1);

        /**
         * @brief Leap second divisor.
         */
        inline static constexpr SecondsType LeapSecondDivisor = SecondsDivisor + static_cast<SecondsType>(1);

        /** @} */
    private:
        // Properties.
        HoursType _hours = HoursMin;
        MinutesType _minutes = MinutesMin;
        SecondsType _seconds = SecondsMin;

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 MathType _n() const noexcept;

        void _resetTimeOfDay() noexcept;

        // Operators.
        template<typename CompareOp, DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool _compare(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        // Parsing.
        template<typename T, T Min, T Max>
        CRONZ_NODISCARD_L1 static bool _parseTimeOfDayComponent(T &component, char c1, char c2) noexcept;

        // Static utility functions.
        template<auto Callback>
        CRONZ_NODISCARD_L1 static TimeOfDayType _current() noexcept;

        template<DateConfigurationFlags DstConfigurationFlags, DateConfigurationFlags SrcConfigurationFlags>
        static void _assign(TimeOfDay<DstConfigurationFlags> &dst,
                            const TimeOfDay<SrcConfigurationFlags> &src) noexcept;

    protected:
        // Parsing.
        CRONZ_NODISCARD_L1 bool _parseTimeOfDay(std::string_view timeOfDay) noexcept;

        // Virtual.
        virtual void _addDays(MathType) noexcept {
        }

        void _addSeconds(const MathType seconds) noexcept requires(AreMillisecondsEnabled) {
            if (static_cast<MathType>(0) == seconds)
                return;
        }

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        TimeOfDay() noexcept = default;

        /**
         * @brief Copy constructor.
         * @param[in] timeOfDay The `TimeOfDay` object to be copied.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        explicit(false) TimeOfDay(const TimeOfDay<IConfigurationFlags> &timeOfDay) noexcept;

        /**
         * @brief Constructor with hours, minutes and seconds values.
         * @param[in] hours The hours value to be assigned.
         * @param[in] minutes The minutes value to be assigned.
         * @param[in] seconds The seconds value to be assigned.
         * @remark Value overflow is handled by the class.
         */
        TimeOfDay(MathType hours, MathType minutes, MathType seconds = static_cast<MathType>(0)) noexcept requires(!
            AreMillisecondsEnabled);

        /**
         * @brief Constructor with hours, minutes and seconds values.
         * @param[in] hours The hours value to be assigned.
         * @param[in] minutes The minutes value to be assigned.
         * @param[in] seconds The seconds value to be assigned.
         * @param[in] milliseconds The milliseconds value to be assigned.
         * @remark Value overflow is handled by the class.
         */
        TimeOfDay(MathType hours, MathType minutes, MathType seconds = static_cast<MathType>(0),
                  MathType milliseconds = static_cast<MathType>(0)) noexcept requires(AreMillisecondsEnabled);

        /**
         * @brief Constructor with a string representation of the time of day.
         * @param[in] timeOfDay The string representation of the time of day.
         * @remark The string representation must be in one of the following formats:
         * - `HH:MM`
         * - `HH:MM:SS`
         * - `HH:MM:SS.mmm` (if milliseconds are enabled)
         */
        explicit(false) TimeOfDay(std::string_view timeOfDay) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the hours.
         * @return The hours.
         */
        CRONZ_NODISCARD_L1 HoursType hours() const noexcept;

        /**
         * @brief Returns the hours.
         * @return The hours.
         */
        CRONZ_NODISCARD_L1 HoursType getHours() const noexcept;

        /**
         * @brief Changes the hours.
         * @param[in] hours The hours value to be assigned.
         */
        void hours(MathType hours) noexcept;

        /**
         * @brief Changes the hours.
         * @param[in] hours The hours value to be assigned.
         */
        void setHours(MathType hours) noexcept;

        /**
         * @brief Changes the hours.
         * @param[in] hours Hours to be added.
         */
        void addHours(MathType hours) noexcept;

        /**
         * @brief Returns the minutes.
         * @return The minutes.
         */
        CRONZ_NODISCARD_L1 MinutesType minutes() const noexcept;

        /**
         * @brief Returns the minutes.
         * @return The minutes.
         */
        CRONZ_NODISCARD_L1 MinutesType getMinutes() const noexcept;

        /**
         * @brief Changes the minutes.
         * @param[in] minutes The minutes value to be assigned.
         */
        void minutes(MathType minutes) noexcept;

        /**
         * @brief Changes the minutes.
         * @param[in] minutes The minutes value to be assigned.
         */
        void setMinutes(MathType minutes) noexcept;

        /**
         * @brief Changes the minutes.
         * @param[in] minutes Minutes to be added.
         */
        void addMinutes(MathType minutes) noexcept;

        /**
         * @brief Returns the seconds.
         * @return The seconds.
         */
        CRONZ_NODISCARD_L1 SecondsType seconds() const noexcept;

        /**
         * @brief Returns the seconds.
         * @return The seconds.
         */
        CRONZ_NODISCARD_L1 SecondsType getSeconds() const noexcept;

        /**
         * @brief Changes the seconds.
         * @param[in] seconds The seconds value to be assigned.
         */
        void seconds(MathType seconds) noexcept;

        /**
         * @brief Changes the seconds.
         * @param[in] seconds The seconds value to be assigned.
         */
        void setSeconds(MathType seconds) noexcept;

        /**
         * @brief Changes the seconds.
         * @param[in] seconds Seconds to be added.
         */
        void addSeconds(MathType seconds) noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Assignment operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be assigned.
         * @param[in] timeOfDay The `TimeOfDay` object to be assigned.
         * @return The current object.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        TimeOfDayType &operator=(const TimeOfDay<IConfigurationFlags> &timeOfDay) noexcept;

        /**
         * @brief Equality operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the two objects are equal.
         * @return `false` if the two objects are not equal.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator==(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /**
         * @brief Inequality operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the two objects are not equal.
         * @return `false` if the two objects are equal.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator!=(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /**
         * @brief Less than operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the current object is less than the `timeOfDay` object.
         * @return `false` if the current object is not less than the `timeOfDay` object.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator<(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /**
         * @brief Less than or equal to operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the current object is less than or equal to the `timeOfDay` object.
         * @return `false` if the current object is not less than or equal to the `timeOfDay` object.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator<=(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /**
         * @brief Greater than operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the current object is greater than the `timeOfDay` object.
         * @return `false` if the current object is not greater than the `timeOfDay` object.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator>(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /**
         * @brief Greater than or equal to operator.
         * @tparam IConfigurationFlags The configuration flags of the `TimeOfDay` object to be compared.
         * @param[in] timeOfDay The `TimeOfDay` object to be compared.
         * @return `true` if the current object is greater than or equal to the `timeOfDay` object.
         * @return `false` if the current object is not greater than or equal to the `timeOfDay` object.
         */
        template<DateConfigurationFlags IConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator>=(const TimeOfDay<IConfigurationFlags> &timeOfDay) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~TimeOfDay() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Returns a `TimeOfDay` container initialized with the local time.
         * @return `TimeOfDay` container initialized with the local time.
         */
        CRONZ_NODISCARD_L1 static TimeOfDayType CurrentTimeOfDay() noexcept;

        /**
         * @brief Returns a `TimeOfDay` container initialized with the GMT/UTC time.
         * @return `TimeOfDay` container initialized with the GMT/UTC time.
         */
        CRONZ_NODISCARD_L1 static TimeOfDayType CurrentTimeOfDayGMT() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/time_of_day.ipp"

#endif // CRONZ_HTTP_DATE_TIME_OF_DAY_HPP
