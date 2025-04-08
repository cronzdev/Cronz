/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_DATE_HPP
#define CRONZ_HTTP_DATE_DATE_HPP 1

#include "cronz/http/date/zone.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class Date {
    public:
        /**
         * @name Static constants and types.
         */
        /** @{ */
        /**
         * @brief Day type.
         */
        using DayType = std::int_fast8_t;

        /**
         * @brief Date type.
         */
        using DateType = std::int_fast8_t;

        /**
         * @brief Month type.
         */
        using MonthType = std::int_fast8_t;

        /**
         * @brief Year type.
         */
        using YearType = std::int_fast16_t;

        /**
         * @brief Year maximum value.
         */
        inline static constexpr YearType YearMax = static_cast<YearType>(9999);

        /**
         * @brief Year minimum value.
         */
        inline static constexpr YearType YearMin = static_cast<YearType>(1970);

        /**
         * @brief Math type.
         */
        using MathType = std::int_fast64_t;

        /**
         * @brief Days of week.
         * @enum DayOfWeek
         */
        enum class DayOfWeek : DayType {
            /**
             * @brief Sunday.
             */
            Sunday = static_cast<DayType>(0),

            /**
             * @brief Monday.
             */
            Monday = static_cast<DayType>(1),

            /**
             * @brief Tuesday.
             */
            Tuesday = static_cast<DayType>(2),

            /**
             * @brief Wednesday.
             */
            Wednesday = static_cast<DayType>(3),

            /**
             * @brief Thursday.
             */
            Thursday = static_cast<DayType>(4),

            /**
             * @brief Friday.
             */
            Friday = static_cast<DayType>(5),

            /**
             * @brief Saturday.
             */
            Saturday = static_cast<DayType>(6),

            /**
             * @brief Invalid value.
             */
            Invalid = static_cast<DayType>(-1)
        };

        /**
         * @brief Months.
         * @enum Month
         */
        enum class Month : MonthType {
            /**
             * @brief January.
             */
            January = static_cast<MonthType>(1),

            /**
             * @brief February.
             */
            February = static_cast<MonthType>(2),

            /**
             * @brief March.
             */
            March = static_cast<MonthType>(3),

            /**
             * @brief April.
             */
            April = static_cast<MonthType>(4),

            /**
             * @brief May.
             */
            May = static_cast<MonthType>(5),

            /**
             * @brief June.
             */
            June = static_cast<MonthType>(6),

            /**
             * @brief July.
             */
            July = static_cast<MonthType>(7),

            /**
             * @brief August.
             */
            August = static_cast<MonthType>(8),

            /**
             * @brief September.
             */
            September = static_cast<MonthType>(9),

            /**
             * @brief October.
             */
            October = static_cast<MonthType>(10),

            /**
             * @brief November.
             */
            November = static_cast<MonthType>(11),

            /**
             * @brief December.
             */
            December = static_cast<MonthType>(12),

            /**
             * @brief Invalid value.
             */
            Invalid = static_cast<MonthType>(-1)
        };

        /** @} */
    private:
        // Properties.
        YearType _year = YearMin;
        MonthType _month = static_cast<MonthType>(Month::January);
        DayType _day = static_cast<DayType>(1);

        void _setYear(YearType year) noexcept;

        template<bool AddOrSubtract>
        void _addMonths(MathType months) noexcept;

        template<bool AddOrSubtract>
        void _addDays(MathType days) noexcept;

        CRONZ_NODISCARD_L1 DayOfWeek _getDayOfWeek() const noexcept;

        // Static utility functions.
        template<auto Callback>
        CRONZ_NODISCARD_L1 static Date _today(std::chrono::system_clock::time_point tp) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Date() noexcept = default;

        /**
         * @brief Constructor with year, month and day values.
         * @param[in] year Year to be assigned.
         * @param[in] month Month to be assigned.
         * @param[in] day Day to be assigned.
         * @remark Value overflow is handled by the class.
         */
        Date(MathType day, MathType month, MathType year) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the current year.
         * @return Current year.
         */
        CRONZ_NODISCARD_L1 YearType year() const noexcept;

        /**
         * @brief Returns the current year.
         * @return Current year.
         */
        CRONZ_NODISCARD_L1 YearType getYear() const noexcept;

        /**
         * @brief Sets the current year.
         * @param[in] year Year to be set.
         * @remark If `year` is out of range (1900-9999), the year is normalized. For example, the year `10001` will be
         * normalized as `1901`.
         * @remark If `February 29` is carried to a non-leap year, it is updated as `February 28`.
         */
        void year(MathType year) noexcept;

        /**
         * @brief Sets the current year.
         * @param[in] year Year to be set.
         * @remark If `year` is out of range (1970-9999), the year is normalized. For example, the year `10001` will be
         * normalized as `1971`.
         * @remark If `February 29` is carried to a non-leap year, it is updated as `February 28`.
         */
        void setYear(MathType year) noexcept;

        /**
         * @brief Adds to the current year.
         * @param[in] years Year to be added.
         * @remark If `year` is out of range (1970-9999), the year is normalized. For example, the year `10001` will be
         * normalized as `1971`.
         * @remark If `February 29` is carried to a non-leap year, it is updated as `February 28`.
         */
        void addYears(MathType years) noexcept;

        /**
         * @brief Returns the current month.
         * @return Current month.
         */
        CRONZ_NODISCARD_L1 Month month() const noexcept;

        /**
         * @brief Returns the current month.
         * @return Current month.
         */
        CRONZ_NODISCARD_L1 Month getMonth() const noexcept;

        /**
         * @brief Sets the current month.
         * @param[in] month Month to be set.
         * @remark If `month` is `Month::Invalid`, nothing happens.
         */
        void month(Month month) noexcept;

        /**
         * @brief Sets the current month.
         * @param[in] month Month to be set.
         * @remark If `month` is `Month::Invalid`, nothing happens.
         */
        void setMonth(Month month) noexcept;

        /**
         * @brief Returns the current month value.
         * @return Current month value.
         */
        CRONZ_NODISCARD_L1 MonthType monthValue() const noexcept;

        /**
         * @brief Returns the current month value.
         * @return Current month value.
         */
        CRONZ_NODISCARD_L1 MonthType getMonthValue() const noexcept;

        /**
         * @brief Sets the current month.
         * @param[in] month Month to be set.
         */
        void month(MathType month) noexcept;

        /**
         * @brief Sets the current month.
         * @param[in] month Month to be set.
         */
        void setMonth(MathType month) noexcept;

        /**
         * @brief Adds to the current month.
         * @param[in] months Months to be added.
         */
        void addMonths(MathType months) noexcept;

        /**
         * @brief Returns the current day (of the month).
         * @return Current day (of the month).
         */
        CRONZ_NODISCARD_L1 DayType day() const noexcept;

        /**
         * @brief Returns the current day (of the month).
         * @return Current day (of the month).
         */
        CRONZ_NODISCARD_L1 DayType getDay() const noexcept;

        /**
         * @brief Sets the current day (of the month).
         * @param[in] day Day to be set.
         * @remark If `day` is out of range (1-28/29/30/31), the day is normalized and the month is
         * incremented/decremented accordingly. For example, the day `32` in the month `January` will update the month
         * as `February` and the day as `1`.
         */
        void day(MathType day) noexcept;

        /**
         * @brief Sets the current day (of the month).
         * @param[in] day Day to be set.
         * @remark If `day` is out of range (1-28/29/30/31), the day is normalized and the month is
         * incremented/decremented accordingly. For example, the day `32` in the month `January` will update the month
         * as `February` and the day as `1`.
         */
        void setDay(MathType day) noexcept;

        /**
         * @brief Adds days the current day (of the month).
         * @param[in] days Day to be added.
         * @remark If `day` is out of range (1-28/29/30/31), the day is normalized and the month is
         * incremented/decremented accordingly. For example, the day `32` in the month `January` will update the month
         * as `February` and the day as `1`.
         */
        void addDays(MathType days) noexcept;

        /**
         * @brief Returns the current day of the week.
         * @return Current day of the week.
         */
        CRONZ_NODISCARD_L1 DayOfWeek dayOfWeek() const noexcept;

        /**
         * @brief Returns the current day of the week.
         * @return Current day of the week.
         */
        CRONZ_NODISCARD_L1 DayOfWeek getDayOfWeek() const noexcept;

        /**
         * @brief Sets the current date.
         * @param[in] day Day to be set.
         * @param[in] month Month to be set.
         * @param[in] year Year to be set.
         * @remark Value overflow is handled by the class.
         */
        void setDate(MathType day, MathType month, MathType year) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Tells if the current year is a leap year.
         * @return `true` if the current year is a leap year.
         * @return `false` if the current year is not a leap year.
         */
        CRONZ_NODISCARD_L1 bool isLeapYear() const noexcept;

        /**
         * @brief Returns the number of days in the current month.
         * @return Number of days in the current month.
         * @remark Leap years are taken into account for February.
         */
        CRONZ_NODISCARD_L1 DayType getDaysInMonth() const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~Date() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Returns the current date.
         * @return The current date.
         */
        CRONZ_NODISCARD_L1 static Date Today() noexcept;

        /**
         * @brief Returns the current date in the specified zone.
         * @param[in] zone The zone to be used.
         * @return The current date in the specified zone.
         */
        CRONZ_NODISCARD_L1 static Date Today(const Zone &zone) noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/date.ipp"

#endif // CRONZ_HTTP_DATE_DATE_HPP
