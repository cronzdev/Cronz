/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_COOKIE_DATE_HPP
#define CRONZ_HTTP_COOKIE_DATE_HPP 1

#include "cronz/http/date.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Cookie date type.
     * @type DateTime<DateTimeConfigurationFlags{0}> CookieDate
     */
    using CookieDate = DateTime<DateTimeConfigurationFlags{0}>;

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_COOKIE_DATE_HPP
