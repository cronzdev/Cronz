/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_AUTHORITY_IMPL_AUTHORITY_IPP
#define CRONZ_URI_AUTHORITY_IMPL_AUTHORITY_IPP 1

#include "cronz/uri/authority/authority.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Properties.
    inline std::size_t Authority::length(const bool includePassword) const noexcept {
        auto len = static_cast<std::size_t>(0);

        if (userInformation) {
            len += userInformation.length(includePassword);
            ++len;
        }

        if (host)
            len += host.length();

        if (InvalidPort != port) {
            ++len;
            len += CalculatePortLength(port);
        }

        return len;
    }

    inline bool Authority::empty() const noexcept {
        return userInformation.empty() && host.empty() && InvalidPort == port;
    }

    inline void Authority::clear() noexcept {
        userInformation.clear();
        host.clear();
        port = InvalidPort;
    }

    // Parsing & Stringification.
    inline bool Authority::parse(const std::string_view authority) noexcept {
        clear();

        const char *beg = authority.cbegin();
        const char *end = authority.cend();

        const char *cursor = std::ranges::find(beg, end, '@');
        if (end != cursor) {
            if (!userInformation.parse(std::string_view(beg, cursor)))
                goto parse_bad;

            beg = cursor + static_cast<std::size_t>(1);
        }

        if (const std::string_view::size_type p = authority.find_last_of(":]");
            std::string_view::npos != p && ']' != authority[p]) {
            cursor = authority.data() + p + static_cast<std::size_t>(1);
            if (!ParsePort(std::string_view(cursor, end), port))
                goto parse_bad;

            end = cursor - static_cast<std::size_t>(1);
        }

        if (beg != end) {
            if (!host.assign(std::string_view(beg, end))) {
                goto parse_bad;
            }
        }

        return true;

    parse_bad:

        clear();
        return false;
    }

    inline std::string Authority::stringify(const bool includePassword) const noexcept {
        std::string str;
        return stringify(str, includePassword) ? str : std::string();
    }

    inline bool Authority::stringify(std::string &str, const bool includePassword) const noexcept {
        str.clear();

        auto offset = static_cast<std::size_t>(0);
        return stringify(str, offset, includePassword);
    }

    inline bool Authority::stringify(std::string &str, std::size_t &offset, const bool includePassword) const noexcept {
        if (const std::size_t len = (length() + offset);
            str.length() < len) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (userInformation) {
            if (!userInformation.stringify(str, offset, includePassword))
                return false;

            str[offset++] = '@';
        }

        if (host && !host.stringify(str, offset))
            return false;

        if (InvalidPort != port) {
            str[offset++] = ':';
            if (!StringifyPort(port, str, offset))
                return false;
        }

        return true;
    }

    // Operators.
    inline Authority::operator bool() const noexcept {
        return !empty();
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_AUTHORITY_IMPL_AUTHORITY_IPP
