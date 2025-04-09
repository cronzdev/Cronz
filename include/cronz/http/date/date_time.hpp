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
    template<DateTimeConfigurationFlags ConfigurationFlags = DefaultDateTimeConfigurationFlags>
    class DateTime final : public Date, public Time<ConfigurationFlags> {
    public:
        using DateTimeType = DateTime<ConfigurationFlags>;

        using DateType = Date;

        using TimeType = Time<ConfigurationFlags>;

        using MathType = std::int64_t;

        using TimestampType = MathType;

        inline static constexpr std::size_t DateTimeLength = static_cast<std::size_t>(31);

    private:
        // Properties.
        template<bool IncludeMilliseconds, YearType FirstYear>
        CRONZ_NODISCARD_L1 TimestampType _timestamp() const noexcept;

        // Parsing.
        CRONZ_NODISCARD_L1 bool _parseDateTime(std::string_view dateTime) noexcept;

        void _resetDateTime() noexcept;

        // Operators.
        template<DateTimeConfigurationFlags IConfigurationFlags, typename CompareOp>
        CRONZ_NODISCARD_L1 bool _c(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

    protected:
        // Virtual.
        void _addDays(const MathType days) noexcept override {
            addDays(days);
        }

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        DateTime() noexcept = default;

        /**
         * @brief Constructor with date and time.
         * @param[in] date The date to set.
         * @param[in] time The time to set.
         */
        explicit(false) DateTime(const Date &date, const TimeType &time = TimeType()) noexcept;

        /**
         * @brief Constructor with date and time string.
         * @param[in] dateTime The date and time string to parse.
         */
        explicit(false) DateTime(std::string_view dateTime) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the date part of the DateTime.
         * @return The date part of the DateTime.
         */
        CRONZ_NODISCARD_L1 DateType date() const noexcept;

        /**
         * @brief Returns the date part of the DateTime.
         * @return The date part of the DateTime.
         */
        CRONZ_NODISCARD_L1 DateType getDate() const noexcept;

        /**
         * @brief Returns the time part of the DateTime.
         * @return The time part of the DateTime.
         */
        CRONZ_NODISCARD_L1 TimeType time() const noexcept;

        /**
         * @brief Returns the time part of the DateTime.
         * @return The time part of the DateTime.
         */
        CRONZ_NODISCARD_L1 TimeType getTime() const noexcept;

        /**
         * @brief Returns the timestamp of the DateTime.
         * @return The timestamp of the DateTime.
         * @remark If the DateTime is configured to include milliseconds, the timestamp will be in milliseconds.
         * @remark If the DateTime is configured to not include milliseconds, the timestamp will be in seconds.
         */
        CRONZ_NODISCARD_L1 TimestampType timestamp() const noexcept;

        /**
         * @brief Returns the timestamp of the DateTime.
         * @return The timestamp of the DateTime.
         * @remark If the DateTime is configured to include milliseconds, the timestamp will be in milliseconds.
         * @remark If the DateTime is configured to not include milliseconds, the timestamp will be in seconds.
         */
        CRONZ_NODISCARD_L1 TimestampType getTimestamp() const noexcept;

        /**
         * @brief Returns the timestamp of the DateTime in seconds.
         * @return The timestamp of the DateTime in seconds.
         */
        CRONZ_NODISCARD_L1 TimestampType getTimestampInSeconds() const noexcept;

        /**
         * @brief Returns the timestamp of the DateTime in milliseconds.
         * @return The timestamp of the DateTime in milliseconds.
         */
        CRONZ_NODISCARD_L1 TimestampType getTimestampInMilliseconds() const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Equality operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is equal to the given DateTime.
         * @return `false` if the DateTime is not equal to the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator==(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /**
         * @brief Inequality operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is not equal to the given DateTime.
         * @return `false` if the DateTime is equal to the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator!=(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /**
         * @brief Less than operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is less than the given DateTime.
         * @return `false` if the DateTime is not less than the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator<(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /**
         * @brief Less than or equal to operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is less than or equal to the given DateTime.
         * @return `false` if the DateTime is not less than or equal to the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator<=(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /**
         * @brief Greater than operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is greater than the given DateTime.
         * @return `false` if the DateTime is not greater than the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator>(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /**
         * @brief Greater than or equal to operator.
         * @tparam IConfigurationFlags The configuration flags for the DateTime to compare with.
         * @param[in] dateTime The DateTime to compare with.
         * @return `true` if the DateTime is greater than or equal to the given DateTime.
         * @return `false` if the DateTime is not greater than or equal to the given DateTime.
         */
        template<DateTimeConfigurationFlags IConfigurationFlags = ConfigurationFlags>
        CRONZ_NODISCARD_L1 bool operator>=(const DateTime<IConfigurationFlags> &dateTime) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~DateTime() noexcept override = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/date_time.ipp"

#endif // CRONZ_HTTP_DATE_DATE_TIME_HPP
