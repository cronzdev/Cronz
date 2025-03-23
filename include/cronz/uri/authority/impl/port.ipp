/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_AUTHORITY_IMPL_PORT_IPP
#define CRONZ_URI_AUTHORITY_IMPL_PORT_IPP 1

#include "cronz/uri/authority/port.hpp"
#include "cronz/rfc/rule/digit.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    inline Port ParsePort(const std::string_view str) noexcept {
        Port port;
        return ParsePort(str, port) ? port : InvalidPort;
    }

    inline bool ParsePort(const std::string_view str, Port &port) noexcept {
        if (static_cast<std::size_t>(5) < str.length())
            return false;

        port = InvalidPort;
        for (auto i = static_cast<std::size_t>(0); i < str.length(); ++i) {
            if (const char c = str[i]; RFC::IsDigit(c)) {
                const Port digit = static_cast<Port>(c - '0');
                if (static_cast<std::size_t>(4) != i) {
                    port = (port * static_cast<Port>(10)) + digit;
                } else {
                    if (static_cast<Port>(6553) < port)
                        return false;

                    if (static_cast<Port>(6553) == port && static_cast<Port>(6) < digit)
                        return false;

                    port = (port * static_cast<Port>(10)) + digit;
                }
            } else {
                return false;
            }
        }

        return true;
    }

    inline std::string StringifyPort(const Port port) noexcept {
        std::string str;
        return StringifyPort(port, str) ? str : std::string();
    }

    inline bool StringifyPort(const Port port, std::string &str) noexcept {
        str.clear();

        auto offset = static_cast<std::size_t>(0);
        return StringifyPort(port, str, offset);
    }

    inline bool StringifyPort(Port port, std::string &str, std::size_t &offset) noexcept {
        std::size_t portLength = CalculatePortLength(port);
        if (const std::size_t length = (portLength + offset);
            str.length() < length) {
            try {
                str.resize(length);
            } catch (...) {
                return false;
            }
        }

        if (InvalidPort == port)
            return true;

        offset += portLength;
        portLength = static_cast<std::size_t>(1);
        while (static_cast<Port>(0) != port) {
            str[offset - portLength] = static_cast<char>((port % static_cast<Port>(10)) + '0');
            port /= static_cast<Port>(10);

            ++portLength;
        }

        return true;
    }

    inline std::size_t CalculatePortLength(Port port) noexcept {
        if (InvalidPort == port)
            return static_cast<std::size_t>(0);

        auto length = static_cast<std::size_t>(1);
        while (static_cast<Port>(10) < port) {
            port /= static_cast<Port>(10);
            ++length;
        }

        return length;
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_AUTHORITY_IMPL_PORT_IPP
