/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_DATE_IPP
#define CRONZ_HTTP_DATE_IMPL_DATE_IPP 1

#include "cronz/http/date/date.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline Date::YearType Date::year() const noexcept {
        return getYear();
    }

    inline Date::YearType Date::getYear() const noexcept {
        return _year;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_DATE_IPP
