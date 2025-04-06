/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_FLAGS_IPP
#define CRONZ_HTTP_DATE_IMPL_FLAGS_IPP 1

#include "cronz/http/date/flags.hpp"

CRONZ_BEGIN_HTTP_INTERNAL_NAMESPACE
    template<DateConfigurationFlags ConfigurationFlags>
    inline constexpr bool AreMillisecondsEnabled() noexcept {
        return static_cast<bool>(ConfigurationFlags & DATE_ENABLE_MILLISECONDS);
    }

CRONZ_END_HTTP_INTERNAL_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_FLAGS_IPP
