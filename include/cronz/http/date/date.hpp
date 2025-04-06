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

#include "cronz/http/types.hpp"

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

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Date() noexcept = default;

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
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/date.ipp"

#endif // CRONZ_HTTP_DATE_DATE_HPP
