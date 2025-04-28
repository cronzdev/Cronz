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

#include <functional>
#include <optional>
#include <shared_mutex>

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, typename ServerConnectionRefType>
    class ServerRouter;

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    class ServerRouterExtension;
CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    struct ServerRouterRouteParams : std::unordered_map<std::string, std::string> {
    };

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, typename ServerConnectionRefType>
    class ServerRouterHost {
    public:
        // Static type definitions.
        struct Part {
            std::string_view label{};
            bool isWildcard = false;
        };

        using RequestCallbackType = std::function<bool(const ServerConnectionRefType &connection,
                                                       const Request &request, Response &response)>;

        using RequestParamCallbackType = std::function<bool(const ServerConnectionRefType &connection,
                                                            const Request &request, Response &response,
                                                            const ServerRouterRouteParams &params)>;

    private:
        // Static type definitions.
        struct Route {
            struct RoutePart {
                std::string segment{};
                bool isWildcard = false;
            };

            Method method{};
            std::string path{};
            std::vector<RoutePart> parts{};
            std::unordered_map<std::string, std::size_t> params{};

            RequestParamCallbackType callback{};
        };

        // Properties.
        std::string _domain{};
        std::vector<Part> _parts{};
        std::vector<Route> _routes{};
        std::shared_mutex &_lock;

        std::optional<RequestCallbackType> _onRouteMatch = std::nullopt;
        std::optional<RequestCallbackType> _onFallback = std::nullopt;

        // Constructor & Destructor.
        explicit ServerRouterHost(std::shared_mutex &m) noexcept;

        ~ServerRouterHost() noexcept = default;

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 bool _match(const Path &path, ServerConnectionRefType connection, const Request &request,
                                       Response &response, bool &r) noexcept;

        // Static utility functions.
        CRONZ_NODISCARD_L1 static bool _parse(std::string_view path, Route &route) noexcept;

        CRONZ_NODISCARD_L1 static bool _split(std::string_view hostname, std::vector<Part> &parts) noexcept;

        CRONZ_NODISCARD_L1 static bool _match(const std::vector<Part> &p1, const std::vector<Part> &p2) noexcept;

        // Friends.
        friend class ServerRouter<Version, ConfigurationFlags, ServerConnectionRefType>;
        friend class ServerRouterExtension<Version, ConfigurationFlags>;

    public:
        void onRouteMatch(RequestCallbackType callback) noexcept;

        void onFallback(RequestCallbackType callback) noexcept;

        CRONZ_NODISCARD_L1 bool onRoute(std::string_view path, RequestParamCallbackType callback) noexcept;

        CRONZ_NODISCARD_L1 bool onRoute(const Method &method, std::string_view path,
                                        RequestParamCallbackType callback) noexcept;
    };

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags, typename ServerConnectionRefType>
    class ServerRouter {
    public:
        using ServerRouterHostType = ServerRouterHost<Version, ConfigurationFlags, ServerConnectionRefType>;
        using ServerRouterHostRefType = ServerRouterHostType *;

    private:
        // Properties.
        std::vector<ServerRouterHostRefType> _hosts{};
        ServerRouterHostRefType _defaultHost = nullptr;

        std::shared_mutex _lock{};

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        ServerRouter() noexcept = default;

        /** @} */

        /**
         * @name Host management.
         */
        /** @{ */
        /**
         * @brief Creates a new host.
         * @param[in] hostname Hostname to create.
         * @return Pointer to the created host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType createHost(std::string_view hostname) noexcept;

        /**
         * @brief Gets a host by its hostname.
         * @param[in] hostname Hostname to get.
         * @return Pointer to the host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType getHost(std::string_view hostname) noexcept;

        /**
         * @brief Matches a host by its hostname.
         * @param[in] hostname Hostname to match.
         * @return Pointer to the matched host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType matchHost(std::string_view hostname) noexcept;

        /**
         * @brief Matches a host by its parts.
         * @param[in] parts Parts to match.
         * @return Pointer to the matched host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType matchHost(
            const std::vector<typename ServerRouterHostType::Part> &parts) noexcept;

        /**
         * @brief Matches a host by its hostname.
         * @param[in] host Hostname to match.
         * @return Pointer to the matched host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType matchHost(const Host &host) noexcept;

        /**
         * @brief Deletes a host by its hostname.
         * @param[in] hostname Hostname to delete.
         */
        void deleteHost(std::string_view hostname) noexcept;

        /**
         * @brief Deletes a host.
         * @param[in] host Host to delete.
         */
        void deleteHost(ServerRouterHostRefType host) noexcept;

        /**
         * @brief Deletes all hosts.
         */
        void deleteAllHosts() noexcept;

        /**
         * @brief Creates a default host.
         * @return `true` if the default host is created successfully.
         * @return `false` if the default host creation fails.
         */
        CRONZ_NODISCARD_L1 bool createDefaultHost() noexcept;

        /**
         * @brief Gets the default host.
         * @return Pointer to the default host.
         */
        CRONZ_NODISCARD_L1 ServerRouterHostRefType getDefaultHost() noexcept;

        /**
         * @brief Deletes the default host.
         */
        void deleteDefaultHost() noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~ServerRouter() noexcept;

        /** @} */
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
    public:
        /**
         * @name Static type definitions.
         */
        /** @{ */
        using ServerConnectionRefType = typename ServerExtension<Version, ConfigurationFlags>::ServerConnectionRefType;
        using ServerInterfaceType = typename ServerExtension<Version, ConfigurationFlags>::ServerInterfaceType;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        ServerRouter<Version, ConfigurationFlags, ServerConnectionRefType> router{};

        /** @} */

    protected:
        // Extension setup.
        bool install() noexcept override;

        void uninstall() noexcept override;

        // Interceptors.
        bool onBeforeRequest(const ServerConnectionRefType &connection, const Request &request,
                             Response &response) override;

        // Constructor & Destructor.
        explicit ServerRouterExtension(const ServerInterfaceType *server) noexcept;

        ~ServerRouterExtension() noexcept override;
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/server/extension/impl/router.ipp"

#endif // CRONZ_HTTP_SERVER_EXTENSION_ROUTER_HPP
