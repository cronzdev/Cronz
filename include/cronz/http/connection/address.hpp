/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_CONNECTION_ADDRESS_HPP
#define CRONZ_HTTP_CONNECTION_ADDRESS_HPP 1

#include "cronz/http/types.hpp"
#include "cronz/uri/authority/port.hpp"

#include <string>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Connection address.
     * @class ConnectionAddress
     */
    struct ConnectionAddress {
        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Remote address.
         */
        std::string address;

        /**
         * @brief Remote port.
         */
        Port port = InvalidPort;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Resets the connection address and port.
         */
        void reset() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/connection/impl/address.ipp"

#endif // CRONZ_HTTP_CONNECTION_ADDRESS_HPP
