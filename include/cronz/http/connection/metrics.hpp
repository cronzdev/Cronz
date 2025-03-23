/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_CONNECTION_METRICS_HPP
#define CRONZ_HTTP_CONNECTION_METRICS_HPP 1

#include "cronz/http/types.hpp"

#include <chrono>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Connection metrics.
     * @class ConnectionMetrics
     */
    struct ConnectionMetrics {
        /**
        * @name Properties.
        */
        /** @{ */
        /**
         * @brief Start time.
         */
        std::chrono::system_clock::time_point timeStarted;

        /**
         * @brief Close time.
         */
        std::chrono::system_clock::time_point timeClosed;

        /**
         * @brief Number of requests received/sent.
         */
        std::size_t numRequests = static_cast<std::size_t>(0);

        /**
         * @brief Total bytes received.
         */
        std::size_t totalBytesIn = static_cast<std::size_t>(0);

        /**
         * @brief Total bytes sent.
         */
        std::size_t totalBytesOut = static_cast<std::size_t>(0);

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Resets the metrics.
         */
        void reset() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/connection/impl/metrics.ipp"

#endif // CRONZ_HTTP_CONNECTION_METRICS_HPP
