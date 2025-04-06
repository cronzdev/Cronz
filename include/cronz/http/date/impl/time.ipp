/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_TIME_IPP
#define CRONZ_HTTP_DATE_IMPL_TIME_IPP 1

#include "cronz/http/date/time.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    template<DateConfigurationFlags ConfigurationFlags>
    Time<ConfigurationFlags>::Time(const TimeOfDayType &timeOfDay, const ZoneType &zone) noexcept
        : TimeOfDay<ConfigurationFlags>(timeOfDay), Zone(zone) {
    }

    // Properties.
    template<DateConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::ZoneType Time<ConfigurationFlags>::zone() const noexcept {
        return getZone();
    }

    template<DateConfigurationFlags ConfigurationFlags>
    inline typename Time<ConfigurationFlags>::ZoneType Time<ConfigurationFlags>::getZone() const noexcept {
        return *this;
    }
CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_TIME_IPP
