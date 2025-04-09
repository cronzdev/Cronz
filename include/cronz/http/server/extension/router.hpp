/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_EXTENSION_ROUTER_HPP
#define CRONZ_HTTP_SERVER_EXTENSION_ROUTER_HPP 1

#include "cronz/http/server/extension/base.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Router extension.
     * @class ServerRouterExtension
     * @remark This class is not intended to be used directly. It is used as a base class for server extensions.
     */
    class ServerRouterExtension : public ServerExtension {
    protected:
        bool install() noexcept override {
            return true;
        }

        void uninstall() noexcept override {
        }

        /**
         * @brief Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Do not use this constructor.
         * @param[in] mutex A reference to the mutex used for synchronization.
         */
        explicit ServerRouterExtension(std::shared_mutex &mutex) noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~ServerRouterExtension() noexcept override;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/extension/impl/router.ipp"

#endif // CRONZ_HTTP_SERVER_EXTENSION_ROUTER_HPP
