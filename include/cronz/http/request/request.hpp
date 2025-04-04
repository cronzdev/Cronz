/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_REQUEST_REQUEST_HPP
#define CRONZ_HTTP_REQUEST_REQUEST_HPP 1

#include "cronz/http/method/method.hpp"
#include "cronz/http/header.hpp"
#include "cronz/http/version.hpp"
#include "cronz/uri.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Represents an HTTP request.
     * @struct Request
     */
    struct Request final {
        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief HTTP method.
         */
        Method method;

        /**
         * @brief Request headers.
         */
        HeaderManager headers;

        /**
         * @brief Request URI.
         */
        URI uri;

        /**
         * @brief Request body.
         */
        std::string body;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Resets all properties of the request.
         */
        void reset() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/request/impl/request.ipp"

#endif // CRONZ_HTTP_REQUEST_REQUEST_HPP
