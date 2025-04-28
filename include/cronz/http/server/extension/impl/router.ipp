/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP
#define CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP 1

#include "cronz/http/server/extension/router.hpp"
#include "cronz/rfc/rule/domain.hpp"
#include "cronz/uri/path.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructor & Destructor.
    template<typename ServerConnectionRefType>
    inline ServerRouterHost<ServerConnectionRefType>::ServerRouterHost(std::shared_mutex &m) noexcept : _lock(m) {
    }

    // Static utility functions.
    template<typename ServerConnectionRefType>
    inline bool ServerRouterHost<ServerConnectionRefType>::_parse(const std::string_view path, Route &route) noexcept {
        std::vector<std::string_view> segments{};

        const std::size_t sc = std::ranges::count(path, '/') + static_cast<std::size_t>(1);
        try {
            segments.reserve(sc);
        } catch (...) {
            return false;
        }

        try {
            route.path.assign(path);
            route.parts.reserve(sc);
        } catch (...) {
            return false;
        }

        for (const char *cur = path.cbegin(), *end = path.cend(); cur < end;) {
            const char *const slash = std::ranges::find(cur, end, '/');
            if (static_cast<std::size_t>(0) != static_cast<std::size_t>(std::distance(cur, slash))) {
                try {
                    segments.emplace_back(cur, slash);
                } catch (...) {
                    return false;
                }
            }

            cur = std::next(slash);
        }

        for (const std::string_view segment: segments) {
            if (segment.empty())
                return false;

            typename Route::RoutePart rp{};

            if ('{' == segment.front() && '}' == segment.back()) {
                rp.isWildcard = true;

                if (const auto name = std::string_view(&segment[1], segment.end() - 1);
                    !name.empty()) {
                    try {
                        rp.segment.assign(name);
                    } catch (...) {
                        return false;
                    }
                }
            } else {
                if (!RFC::IsSegment(segment))
                    return false;

                rp.isWildcard = false;

                try {
                    rp.segment.assign(segment);
                } catch (...) {
                    return false;
                }
            }

            try {
                if (rp.isWildcard) {
                    if (route.params.contains(rp.segment))
                        return false;

                    route.params.emplace(rp.segment, route.parts.size());
                }

                route.parts.push_back(std::move(rp));
            } catch (...) {
                return false;
            }
        }

        return true;
    }

    template<typename ServerConnectionRefType>
    inline bool ServerRouterHost<ServerConnectionRefType>::_split(const std::string_view hostname,
                                                                  std::vector<Part> &parts) noexcept {
        if (hostname.empty() || hostname.size() > RFC::MAX_DOMAIN_LENGTH)
            return false;

        const std::size_t count = std::ranges::count(hostname, '.') + static_cast<std::size_t>(1);
        try {
            parts.resize(count);
        } catch (...) {
            return false;
        }

        const char *const beg = hostname.cbegin();
        const char *const end = hostname.cend();

        auto index = static_cast<std::size_t>(0);
        const char *cur = beg;
        while (cur < end) {
            const char *const dot = std::ranges::find(cur, end, '.');
            const auto len = static_cast<std::size_t>(std::distance(cur, dot));
            if (static_cast<std::size_t>(0) == len)
                goto split_bad;


            auto &[label, isWildcard] = parts[index++];
            if (static_cast<std::size_t>(1) == len && '*' == *cur) {
                isWildcard = true;
            } else {
                label = std::string_view(cur, dot);
                if (!RFC::IsLabel(label))
                    goto split_bad;
            }

            cur = std::next(dot);
        }

        if (index != count)
            goto split_bad;

        return true;

    split_bad:
        parts.clear();
        return false;
    }

    template<typename ServerConnectionRefType>
    inline bool ServerRouterHost<ServerConnectionRefType>::_match(const std::vector<Part> &p1,
                                                                  const std::vector<Part> &p2) noexcept {
        return (p1.size() == p2.size()) &&
               std::ranges::equal(p1, p2, [](const Part &l, const Part &r) -> bool {
                   return l.isWildcard || r.isWildcard || (l.label == r.label);
               });
    }

    template<typename ServerConnectionRefType>
    inline bool ServerRouterHost<ServerConnectionRefType>::onRoute(const std::string_view path,
                                                                   RequestParamCallbackType callback) noexcept {
        return onRoute(Method(), path, callback);
    }

    template<typename ServerConnectionRefType>
    inline bool ServerRouterHost<ServerConnectionRefType>::onRoute(const Method &method, const std::string_view path,
                                                                   RequestParamCallbackType callback) noexcept {
        std::lock_guard _(_lock);

        if (!method.value.empty() && !method.isValid())
            return false;

        for (auto it = _routes.begin(); it != _routes.end(); ++it) {
            if (it->method == method && it->path == path) {
                if (nullptr == callback)
                    _routes.erase(it);
                else
                    it->callback = callback;

                return true;
            }
        }

        Route r{};
        if (!_parse(path, r))
            return false;

        try {
            _routes.emplace_back(std::move(r));
        } catch (...) {
            return false;
        }

        return true;
    }

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    // Host management.
    template<typename ServerConnectionRefType>
    inline typename ServerRouter<ServerConnectionRefType>::ServerRouterHostRefType
    ServerRouter<ServerConnectionRefType>::createHost(const std::string_view hostname) noexcept {
        std::lock_guard _(_lock);

        std::vector<typename ServerRouterHostType::Part> parts{};
        if (!ServerRouterHostType::_split(hostname, parts))
            return nullptr;

        for (const ServerRouterHostRefType &host: _hosts) {
            if (host->_domain == hostname)
                return host;
        }

        auto host = new(std::nothrow) ServerRouterHostType(_lock);
        if (nullptr == host)
            return nullptr;

        try {
            host->_domain.assign(hostname);
            host->_parts.swap(parts);

            auto pos = std::ranges::find_if(_hosts, [&host](ServerRouterHostRefType h) noexcept -> bool {
                if (host->_parts.size() < h->_parts.size())
                    return true;

                if (host->_parts.size() > h->_parts.size())
                    return false;

                for (auto i = static_cast<std::size_t>(0); i < host->_parts.size(); ++i) {
                    if (!host->_parts[i].isWildcard && h->_parts[i].isWildcard)
                        return true;

                    if (host->_parts[i].isWildcard && !h->_parts[i].isWildcard)
                        return false;
                }

                return false;
            });

            _hosts.insert(pos, host);
        } catch (...) {
            delete host;
            return nullptr;
        }

        return host;
    }

    template<typename ServerConnectionRefType>
    inline typename ServerRouter<ServerConnectionRefType>::ServerRouterHostRefType
    ServerRouter<ServerConnectionRefType>::getHost(const std::string_view hostname) noexcept {
        std::lock_guard _(_lock);
        for (const ServerRouterHostRefType &host: _hosts) {
            if (host->_domain == hostname)
                return host;
        }

        return nullptr;
    }

    template<typename ServerConnectionRefType>
    inline typename ServerRouter<ServerConnectionRefType>::ServerRouterHostRefType
    ServerRouter<ServerConnectionRefType>::matchHost(const std::string_view hostname) noexcept {
        std::vector<typename ServerRouterHostType::Part> parts{};
        if (!ServerRouterHostType::_split(hostname, parts))
            return nullptr;

        return matchHost(parts);
    }

    template<typename ServerConnectionRefType>
    inline typename ServerRouter<ServerConnectionRefType>::ServerRouterHostRefType
    ServerRouter<ServerConnectionRefType>::matchHost(
        const std::vector<typename ServerRouterHostType::Part> &parts) noexcept {
        std::lock_guard _(_lock);

        for (const ServerRouterHostRefType &host: _hosts) {
            if (ServerRouterHostType::_match(host->_parts, parts))
                return host;
        }

        return nullptr;
    }

    template<typename ServerConnectionRefType>
    inline void ServerRouter<ServerConnectionRefType>::deleteHost(const std::string_view hostname) noexcept {
        std::lock_guard _(_lock);

        for (auto it = _hosts.begin(); it != _hosts.end(); ++it) {
            if ((*it)->_domain == hostname) {
                delete *it;
                _hosts.erase(it);
                return;
            }
        }
    }

    template<typename ServerConnectionRefType>
    inline void ServerRouter<ServerConnectionRefType>::deleteHost(ServerRouterHostRefType host) noexcept {
        std::lock_guard _(_lock);

        for (auto it = _hosts.begin(); it != _hosts.end(); ++it) {
            if (*it == host) {
                delete *it;
                _hosts.erase(it);
                return;
            }
        }
    }

    template<typename ServerConnectionRefType>
    inline void ServerRouter<ServerConnectionRefType>::deleteAllHosts() noexcept {
        std::lock_guard _(_lock);

        for (auto &host: _hosts)
            delete host;

        _hosts.clear();
    }

    template<typename ServerConnectionRefType>
    inline bool ServerRouter<ServerConnectionRefType>::createDefaultHost() noexcept {
        std::lock_guard _(_lock);

        if (nullptr == _defaultHost)
            _defaultHost = new(std::nothrow) ServerRouterHostType(_lock);

        return nullptr != _defaultHost;
    }

    template<typename ServerConnectionRefType>
    inline typename ServerRouter<ServerConnectionRefType>::ServerRouterHostRefType
    ServerRouter<ServerConnectionRefType>::getDefaultHost() noexcept {
        std::lock_guard _(_lock);
        return _defaultHost;
    }

    template<typename ServerConnectionRefType>
    inline void ServerRouter<ServerConnectionRefType>::deleteDefaultHost() noexcept {
        std::lock_guard _(_lock);

        if (nullptr != _defaultHost) {
            delete _defaultHost;
            _defaultHost = nullptr;
        }
    }

    // Destructor.
    template<typename ServerConnectionRefType>
    inline ServerRouter<ServerConnectionRefType>::~ServerRouter() noexcept {
        deleteDefaultHost();
        deleteAllHosts();
    }

CRONZ_END_HTTP_NAMESPACE

CRONZ_BEGIN_HTTP_NAMESPACE
    // Extension setup.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerRouterExtension<Version, ConfigurationFlags>::install() noexcept {
        uninstall();

        if (!router.createDefaultHost())
            return false;

        return true;
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline void ServerRouterExtension<Version, ConfigurationFlags>::uninstall() noexcept {
    }

    // Interceptors.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline bool ServerRouterExtension<Version, ConfigurationFlags>::onBeforeRequest(
        const ServerConnectionRefType &connection, const Request &request, Response &response) {
        return true;
    }

    // Constructors and destructors.
    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline ServerRouterExtension<Version, ConfigurationFlags>::ServerRouterExtension(
        const ServerInterfaceType *server) noexcept : ServerExtension<Version, ConfigurationFlags>(server) {
    }

    template<Version::Enum Version, ServerConfigurationFlags ConfigurationFlags>
    inline ServerRouterExtension<Version, ConfigurationFlags>::~ServerRouterExtension() noexcept {
        ServerRouterExtension<Version, ConfigurationFlags>::uninstall();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_SERVER_EXTENSION_IMPL_ROUTER_IPP
