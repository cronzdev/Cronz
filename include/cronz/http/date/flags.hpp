/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_FLAGS_HPP
#define CRONZ_HTTP_DATE_FLAGS_HPP 1

#include "cronz/http/types.hpp"

#include <cstdint>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Date configuration flags.
     * @enum DateTimeConfigurationFlagBits
     */
    enum DateTimeConfigurationFlagBits : std::uint64_t {
        /**
         * @brief Enables milliseconds in `TimeOfDay` class.
         */
        DATE_TIME_ENABLE_MILLISECONDS = 0x0000000000000001,
    };

    /**
     * @ingroup cronz_http
     * @brief Date configuration flag type.
     * @typedef std::uint64_t DateConfigurationFlags
     */
    typedef std::uint64_t DateTimeConfigurationFlags;

    /**
     * @ingroup cronz_http
     * @brief Default date configuration flags.
     */
    inline constexpr DateTimeConfigurationFlags DefaultDateTimeConfigurationFlags = 0;

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<DateTimeConfigurationFlags ConfigurationFlags>
    CRONZ_NODISCARD_L1 constexpr bool AreMillisecondsEnabled() noexcept;

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#include "cronz/http/date/impl/flags.ipp"

#endif // CRONZ_HTTP_DATE_FLAGS_HPP
