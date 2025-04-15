/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_CALLBACK_HPP
#define CRONZ_HTTP_SERVER_CALLBACK_HPP 1

#include "cronz/http/server/connection.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    struct ServerCallbacks {
    public:
        using ServerConnectionType = ServerConnection<Version, ConfigurationFlags>;
        using ServerConnectionRefType = ServerConnectionRef<Version, ConfigurationFlags>;

    protected:
        friend class ServerConnection<Version, ConfigurationFlags>;
        friend class CRONZ_NAMESPACE_INTERNAL::ServerWorker<Version, ConfigurationFlags>;

        virtual void _request(const ServerConnectionRefType &connection, const Request &request,
                              Response &response) noexcept = 0;

    public:
        virtual ~ServerCallbacks() = default;


        /**
         * @name Callbacks.
         */
        /** @{ */
        /**
         * @brief Called when a new connection is accepted.
         * @param[in] address Address of the connection.
         * @return `true` to accept the connection.
         * @return `false` to reject the connection.
         * @remark This function is called on the server thread. Thus, until this function returns, the server will not
         * be able to accept new connections.
         * @TODO Make this function asynchronous.
         */
        virtual bool onAccept(const ConnectionAddress &address) noexcept = 0;

        /**
         * @brief Called when a request is received.
         * @param[in] connection Connection reference.
         * @param[in] request Request object.
         * @param[out] response Response object.
         * @remark This function is called on the worker thread. Thus, until this function returns, the worker will not
         * be able to process other requests.
         */
        virtual void onRequest(const ServerConnectionRefType &connection, const Request &request,
                               Response &response) noexcept = 0;

        /**
         * @brief Called when a connection is closed.
         * @param[in] connection Connection reference.
         * @remark This function is called on the worker thread. Thus, until this function returns, the worker will not
         * be able to process other requests.
         */
        virtual void onConnectionClosed(const ServerConnectionRefType &connection) noexcept = 0;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_CALLBACK_HPP
