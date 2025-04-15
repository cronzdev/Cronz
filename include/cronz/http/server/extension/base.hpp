/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_EXTENSION_BASE_HPP
#define CRONZ_HTTP_SERVER_EXTENSION_BASE_HPP 1

#include "cronz/http/server/callback.hpp"
#include "cronz/http/server/flags.hpp"
#include "cronz/http/version.hpp"

#include <concepts>
#include <shared_mutex>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Base class for server extensions.
     * @class ServerExtension
     * @remark This class is not intended to be used directly. It is used as a base class for server extensions.
     * @remark Constructors and destructors must be in public section.
     * @remark Extension setup functions must be in protected section.
     */
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class ServerExtension {
    protected:
        using ServerConnectionRefType = typename ServerCallbacks<Version, ConfigurationFlags>::ServerConnectionRefType;

        /**
         * @name Extension setup.
         */
        /** @{ */
        /**
         * @brief Extension installation function.
         * @return `true` if the extension is installed successfully.
         * @return `false` if the extension installation fails.
         * @remark This function is called when the server is initialized. It can be called multiple times.
         */
        virtual bool install() noexcept {
            return true;
        }

        /**
         * @brief Extension uninstallation function.
         * @remark This function is called when the server is terminated. It can be called multiple times.
         */
        virtual void uninstall() noexcept {
        }

        /** @} */

        /**
         * @name Interceptors.
         */
        /** @{ */
        virtual bool onBeforeRequest(const ServerConnectionRefType &connection, const Request &request,
                                     Response &response) {
            return true;
        }

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        ServerExtension() noexcept = default;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        virtual ~ServerExtension() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_EXTENSION_BASE_HPP
