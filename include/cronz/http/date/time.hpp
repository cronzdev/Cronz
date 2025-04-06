/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_TIME_HPP
#define CRONZ_HTTP_DATE_TIME_HPP 1

#include "cronz/http/date/zone.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<DateConfigurationFlags ConfigurationFlags = DefaultDateConfigurationFlags>
    class Time : public TimeOfDay<ConfigurationFlags>, public Zone {
    public:
        /**
         * @name Static constants and type definitions.
         */
        /** @{ */
        /**
         * @brief Time type.
         */
        using TimeType = Time<ConfigurationFlags>;

        /**
         * @brief Time of day type.
         */
        using TimeOfDayType = typename TimeOfDay<ConfigurationFlags>::TimeOfDayType;

        /**
         * @brief Zone type.
         */
        using ZoneType = Zone;

        /** @} */

    private:
        // Parsing.
        CRONZ_NODISCARD_L1 bool _parseTime(std::string_view time) noexcept;

        // Instance-based utility functions.
        void _resetTime() noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Time() noexcept = default;

        /**
         * @brief Constructor with time of day and zone.
         * @param[in] timeOfDay The time of day.
         * @param[in] zone The zone.
         */
        explicit(false) Time(const TimeOfDayType &timeOfDay, const ZoneType &zone = ZoneType::CurrentZone()) noexcept;

        /**
         * @brief Constructor with time string.
         * @param[in] time The time string to parse.
         */
        explicit(false) Time(std::string_view time) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Get the time of day.
         * @return The time of day.
         */
        CRONZ_NODISCARD_L1 TimeOfDayType timeOfDay() const noexcept;

        /**
         * @brief Get the time of day.
         * @return The time of day.
         */
        CRONZ_NODISCARD_L1 TimeOfDayType getTimeOfDay() const noexcept;

        /**
         * @brief Get the zone.
         * @return The zone.
         */
        CRONZ_NODISCARD_L1 ZoneType zone() const noexcept;

        /**
         * @brief Get the zone.
         * @return The zone.
         */
        CRONZ_NODISCARD_L1 ZoneType getZone() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~Time() noexcept override = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/time.ipp"

#endif // CRONZ_HTTP_DATE_TIME_HPP
