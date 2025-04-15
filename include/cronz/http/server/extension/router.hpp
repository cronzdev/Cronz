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
    // class ServerRouterExtension;
CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    class ServerRouterHost {
        // Friends.
        // friend class ServerRouterExtension;
    };

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Router extension.
     * @class ServerRouterExtension
     * @remark This class is not intended to be used directly. It is used as a base class for server extensions.
     */
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class ServerRouterExtension : public ServerExtension<Version, ConfigurationFlags> {
        using ServerConnectionRefType = typename ServerExtension<Version, ConfigurationFlags>::ServerConnectionRefType;

        // Properties.
        std::vector<ServerRouterHost *> _hosts{};

        ServerRouterHost *_default = nullptr;

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
         * @brief Default constructor.
         */
        explicit ServerRouterExtension() noexcept = default;

        /** @} */

        /**
         * @name Interceptors.
         */
        /** @{ */
        bool onBeforeRequest(const ServerConnectionRefType &connection, const Request &request, Response &response) override {
            const bool r = ((rand() % 100) > 50);
            printf("onBeforeRequest >> %i\n", r);
            return r;
        }

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~ServerRouterExtension() noexcept override {
            ServerRouterExtension::uninstall();
        }

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/extension/impl/router.ipp"

#endif // CRONZ_HTTP_SERVER_EXTENSION_ROUTER_HPP
