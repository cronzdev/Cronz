/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_ZONE_HPP
#define CRONZ_HTTP_DATE_ZONE_HPP 1

#include "cronz/http/date/flags.hpp"

#include <ctime>
#include <chrono>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Time zone class.
     * @class Zone
     */
    class Zone {
    public:
        /**
         * @name Static constants and types.
         */
        /** @{ */
        /**
         * @brief Zone offset type.
         */
        using ZoneOffsetType = std::int_fast16_t;

        /**
         * @brief Time zones and their offsets to UTC.
         * @enum Offset
         * @remark Currently, only these following time zones are supported for parsing and stringification.
         */
        enum Offset : ZoneOffsetType {
            /**
             * @brief Atlantic Daylight Time.
             */
            ADT = static_cast<ZoneOffsetType>(-300),

            /**
             * @brief Atlantic Standard Time.
             */
            AST = static_cast<ZoneOffsetType>(-400),

            /**
             * @brief British Summer Time.
             */
            BST = static_cast<ZoneOffsetType>(100),

            /**
             * @brief Central European Time.
             */
            CET = static_cast<ZoneOffsetType>(100),

            /**
             * @brief China Standard Time.
             */
            CST = static_cast<ZoneOffsetType>(800),

            /**
             * @brief Eastern Daylight Time.
             */
            EDT = static_cast<ZoneOffsetType>(-400),

            /**
             * @brief Eastern Standard Time.
             */
            EST = static_cast<ZoneOffsetType>(-500),

            /**
             * @brief Greenwich Mean Time.
             */
            GMT = static_cast<ZoneOffsetType>(0),

            /**
             * @brief Japan Standard Time.
             */
            JST = static_cast<ZoneOffsetType>(900),

            /**
             * @brief Pacific Standard Time.
             */
            PST = static_cast<ZoneOffsetType>(-800),

            /**
             * @brief Pacific Daylight Time.
             */
            PDT = static_cast<ZoneOffsetType>(-700),

            /**
             * @brief Coordinated Universal Time.
             */
            UTC = static_cast<ZoneOffsetType>(0)
        };

        /**
         * @brief Time zone offset abbreviations.
         */
        static const std::array<std::pair<Offset, std::string_view>, static_cast<std::size_t>(12)>
        OffsetAbbreviations;

        /** @} */

    private:
        // Properties.
        ZoneOffsetType _offset = static_cast<ZoneOffsetType>(0);

        // Parsing.
        CRONZ_NODISCARD_L1 bool _parseOffset(std::string_view offset) noexcept;

        CRONZ_NODISCARD_L1 bool _parseZone(std::string_view zone) noexcept;

    protected:
        // Instance-based utility functions.
        void _resetZone() noexcept;

        CRONZ_NODISCARD_L1 bool _parseTimezone(std::string_view timezone) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Zone() noexcept = default;

        /**
         * @brief Constructor with offset.
         * @param[in] offset The offset to UTC.
         */
        explicit(false) Zone(ZoneOffsetType offset) noexcept;

        /**
         * @brief Constructor with offset.
         * @param[in] offset The offset to UTC.
         */
        explicit(false) Zone(Offset offset) noexcept;

        /**
         * @brief Constructor with offset abbreviation.
         * @param[in] zone The offset value or zone abbreviation.
         */
        explicit(false) Zone(std::string_view zone) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the timezone offset value.
         * @return The timezone offset value.
         */
        CRONZ_NODISCARD_L1 ZoneOffsetType timezoneOffset() const noexcept;

        /**
         * @brief Returns the timezone offset value.
         * @return The timezone offset value.
         */
        CRONZ_NODISCARD_L1 ZoneOffsetType getTimezoneOffset() const noexcept;

        /**
         * @brief Changes the timezone offset value.
         * @param[in] offset The timezone offset value to be assigned.
         * @return `true` if the timezone offset value is changed successfully.
         * @return `false` if the timezone offset value is not changed.
         * @remark The offset is limited to the range `-2359` through `+2359`.
         */
        CRONZ_NODISCARD_L2 bool timezoneOffset(ZoneOffsetType offset) noexcept;

        /**
         * @brief Changes the timezone offset value.
         * @param[in] offset The timezone offset value to be assigned.
         * @return `true` if the timezone offset value is changed successfully.
         * @return `false` if the timezone offset value is not changed.
         * @remark The offset is limited to the range `-2359` through `+2359`.
         */
        CRONZ_NODISCARD_L2 bool setTimezoneOffset(ZoneOffsetType offset) noexcept;

        /**
         * @brief Returns the timezone offset value in minutes.
         * @return The timezone offset value in minutes.
         */
        CRONZ_NODISCARD_L1 ZoneOffsetType getTimezoneOffsetInMinutes() const noexcept;

        /**
         * @brief Changes the timezone offset value in minutes.
         * @param[in] minutes The timezone offset value in minutes to be assigned.
         * @return `true` if the timezone offset value is changed successfully.
         * @return `false` if the timezone offset value is not changed.
         */
        CRONZ_NODISCARD_L2 bool setTimezoneOffsetInMinutes(ZoneOffsetType minutes) noexcept;

        /**
         * @brief Changes the timezone offset value.
         * @param[in] zone The timezone offset value to be assigned.
         * @return `true` if the timezone offset value is changed successfully.
         * @return `false` if the timezone offset value is not changed.
         */
        void setTimezone(const Zone &zone) noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Equality operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the two objects are equal.
         * @return `false` if the two objects are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(const Zone &zone) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the two objects are not equal.
         * @return `false` if the two objects are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const Zone &zone) const noexcept;

        /**
         * @brief Less than operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the current object is less than the `zone` object.
         * @return `false` if the current object is not less than the `zone` object.
         */
        CRONZ_NODISCARD_L1 bool operator<(const Zone &zone) const noexcept;

        /**
         * @brief Less than or equal to operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the current object is less than or equal to the `zone` object.
         * @return `false` if the current object is not less than or equal to the `zone` object.
         */
        CRONZ_NODISCARD_L1 bool operator<=(const Zone &zone) const noexcept;

        /**
         * @brief Greater than operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the current object is greater than the `zone` object.
         * @return `false` if the current object is not greater than the `zone` object.
         */
        CRONZ_NODISCARD_L1 bool operator>(const Zone &zone) const noexcept;

        /**
         * @brief Greater than or equal to operator.
         * @param[in] zone The `Zone` object to be compared.
         * @return `true` if the current object is greater than or equal to the `zone` object.
         * @return `false` if the current object is not greater than or equal to the `zone` object.
         */
        CRONZ_NODISCARD_L1 bool operator>=(const Zone &zone) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        virtual ~Zone() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Returns the current timezone.
         * @return The current timezone.
         */
        CRONZ_NODISCARD_L1 static Zone CurrentZone() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/date/impl/zone.ipp"

#endif // CRONZ_HTTP_DATE_ZONE_HPP
