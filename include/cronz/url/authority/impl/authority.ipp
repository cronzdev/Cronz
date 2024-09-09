/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_IMPL_AUTHORITY_IPP
#define CRONZ_URL_AUTHORITY_IMPL_AUTHORITY_IPP 1

#include "cronz/url/authority/authority.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline Authority::Authority() noexcept = default;

    // Properties.
    inline std::size_t Authority::length() const noexcept {
        std::size_t len = host.length();

        if (userInformation) {
            len += userInformation.length();
            len += static_cast<std::size_t>(1);
        }

        if (host)
            len += host.length();

        if (static_cast<Port>(0) != port) {
            len += CalculatePortLength(port);
            len += static_cast<std::size_t>(1);
        }

        return len;
    }

    // Parsing & Stringification.
    inline bool Authority::parse(const char *str) noexcept {
        return parse(str, std::strlen(str));
    }

    inline bool Authority::parse(const char *str, const std::size_t &length) noexcept {
        clear();

        const char *const end = str + length;
        const char *previous = str;

        const char *next = std::ranges::find(previous, end, '@');
        if (end != next) {
            if (!userInformation.parse(previous, next - previous))
                goto bad;

            previous = next + static_cast<std::size_t>(1);
        }

        next = std::ranges::find(previous, end, ':');
        if (!host.parse(previous, next - previous))
            goto bad;

        if (end == next)
            return true;

        previous = next + static_cast<std::size_t>(1);

        if (previous < end && !ParsePort(previous, end - previous))
            goto bad;

        return true;

    bad:
        clear();

        return false;
    }

    inline bool Authority::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline std::string Authority::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            str.clear();

        return str;
    }

    inline bool Authority::stringify(std::string &str) const noexcept {
        str.clear();
        return stringify(str, static_cast<std::size_t>(0));
    }

    inline bool Authority::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (empty())
            return true;

        if (const std::size_t len = length() + offset; len > str.length()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        std::size_t o = offset;

        if (userInformation) {
            if (!userInformation.stringify(str, o))
                return false;

            o += userInformation.length();
            str[o++] = '@';
        }

        if (!host.stringify(str, o))
            return false;

        o += host.length();

        if (static_cast<Port>(0) != port) {
            str[o++] = ':';

            if (!StringifyPort(port, str, o))
                return false;
        }

        return true;
    }

    // Instance-based utility functions.
    inline bool Authority::empty() const noexcept {
        return userInformation.empty() && host.empty() && static_cast<Port>(0) == port;
    }

    inline void Authority::clear() noexcept {
        userInformation.clear();
        host.clear();
        port = static_cast<Port>(0);
    }

    // Operators.
    inline Authority::operator bool() const noexcept {
        return !empty();
    }

    // Destructors.
    inline Authority::~Authority() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_AUTHORITY_IMPL_AUTHORITY_IPP
