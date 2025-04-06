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
    // Properties.
    template<DateConfigurationFlags ConfigurationFlags>
    inline Zone Time<ConfigurationFlags>::getZone() const noexcept {
        return getZone();
    }

    template<DateConfigurationFlags ConfigurationFlags>
    inline Zone Time<ConfigurationFlags>::getZone() const noexcept {
        ZoneType z;
        z._offset = this->_offset;
        return z;
    }
CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_TIME_IPP
