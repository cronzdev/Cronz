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

#include "cronz/http/server/interface.hpp"
#include "cronz/http/version.hpp"

#include <concepts>

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
        using ServerInterfaceType = ServerInterface<Version, ConfigurationFlags>;
        using ServerConnectionRefType = typename ServerCallbacks<Version, ConfigurationFlags>::ServerConnectionRefType;

        const ServerInterfaceType *const server;

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
        /**
         * @brief Interceptor function for request processing.
         * @param[in] connection Pointer to the server connection.
         * @param[in] request Reference to the request object.
         * @param[out] response Reference to the response object.
         * @return `true` if the request should be passed to the next interceptor or the server.
         * @return `false` if the request processing should be concluded here.
         * @remark This function is called before the request is processed. It can be used to modify the request or
         * response objects.
         */
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
         * @brief Constructor with server parameter.
         * @param[in] server Pointer to the server interface.
         * @remark This constructor is used to initialize the server extension.
         */
        explicit ServerExtension(const ServerInterfaceType *server) noexcept : server(server) {
        }

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

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @remark This constructor is deleted. Use the constructor with the server parameter.
         */
        ServerExtension() = delete;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_EXTENSION_BASE_HPP
