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
        /**
         * @name Static constants and type definitions.
         */
        /** @{ */
        using TimeType = Time<ConfigurationFlags>;

        using TimeOfDayType = typename TimeOfDay<ConfigurationFlags>::TimeOfDayType;

        using ZoneType = Zone;
        /** @} */

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

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 ZoneType zone() const noexcept;

        CRONZ_NODISCARD_L1 ZoneType getZone() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~Time() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/time.ipp"

#endif // CRONZ_HTTP_DATE_TIME_HPP
