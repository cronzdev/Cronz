/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_IMPL_PORT_IPP
#define CRONZ_URL_AUTHORITY_IMPL_PORT_IPP 1

#include "cronz/url/authority/port.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    inline Port ParsePort(const std::string &str) noexcept {
        return ParsePort(str.c_str(), str.length());
    }

    inline Port ParsePort(const char *str, const std::size_t &length) noexcept {
        Port port;
        return ParsePort(str, length, port) ? port : static_cast<Port>(0);
    }

    inline bool ParsePort(const std::string &str, Port &port) noexcept {
        return ParsePort(str.c_str(), str.length(), port);
    }

    inline bool ParsePort(const char *str, const std::size_t &length, Port &port) noexcept {
        if (static_cast<std::size_t>(0) == length || length > static_cast<std::size_t>(5))
            return false;

        port = static_cast<Port>(0);
        for (auto i = static_cast<std::size_t>(0); i < length; ++i) {
            if (const char &c = str[i]; '0' <= c && c <= '9') {
                const Port digit = static_cast<Port>(c - '0');
                if (static_cast<std::size_t>(4) != i) {
                    port = (port * static_cast<Port>(10)) + digit;
                }
                else {
                    if (static_cast<Port>(6553) < port)
                        return false;

                    if (static_cast<Port>(6553) == port && static_cast<Port>(6) < digit)
                        return false;

                    port = (port * static_cast<Port>(10)) + digit;
                }
            }
            else {
                return false;
            }
        }

        return true;
    }

    inline std::string StringifyPort(const Port &port) noexcept {
        std::string str;
        if (!StringifyPort(port, str))
            str.clear();

        return str;
    }

    inline bool StringifyPort(const Port &port, std::string &str) noexcept {
        str.clear();
        return StringifyPort(port, str, static_cast<std::size_t>(0));
    }

    inline bool StringifyPort(const Port &port, std::string &str, const std::size_t &offset) noexcept {
        const std::size_t portLength = CalculatePortLength(port);
        std::size_t len = portLength + offset;
        if (len > str.length()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        Port p = port;
        while (len != offset) {
            const char digit = static_cast<char>('0' + (p % static_cast<Port>(10)));
            str[--len] = digit;

            p /= static_cast<Port>(10);
        }

        return true;
    }

    inline Port GetSchemePort(const Scheme &scheme) noexcept {
        const std::string &value = scheme.getValue();
        if (Scheme::FTP == value)
            return static_cast<Port>(21);

        if (Scheme::SFTP == value)
            return static_cast<Port>(22);

        if (Scheme::HTTP == value)
            return static_cast<Port>(80);

        if (Scheme::HTTPS == value)
            return static_cast<Port>(443);

        return static_cast<Port>(0);
    }

    inline std::size_t CalculatePortLength(Port port) noexcept {
        auto len = static_cast<std::size_t>(1);

        while (static_cast<Port>(9) < port) {
            port /= static_cast<Port>(10);
            ++len;
        }

        return len;
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_AUTHORITY_IMPL_PORT_IPP
