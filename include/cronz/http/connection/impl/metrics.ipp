/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_CONNECTION_IMPL_METRICS_IPP
#define CRONZ_HTTP_CONNECTION_IMPL_METRICS_IPP 1

#include "cronz/http/connection/metrics.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Instance-based utility functions.
    inline void ConnectionMetrics::reset() noexcept {
        timeStarted = std::chrono::system_clock::now();
        timeClosed = timeStarted;

        numRequests = static_cast<std::size_t>(0);

        totalBytesIn = static_cast<std::size_t>(0);
        totalBytesOut = static_cast<std::size_t>(0);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_CONNECTION_IMPL_METRICS_IPP
