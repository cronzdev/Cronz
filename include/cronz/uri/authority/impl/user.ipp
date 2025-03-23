/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_USER_IMPL_USER_IPP
#define CRONZ_URI_USER_IMPL_USER_IPP 1

#include "cronz/uri/authority/user.hpp"

#include "cronz/uri/encode.hpp"
#include "cronz/uri/decode.hpp"

#include "cronz/rfc/rule/delims.hpp"
#include "cronz/rfc/rule/unreserved.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Constructors.
    inline UserInformation::UserInformation(const std::string_view user, const std::string_view password) noexcept {
        if (!setUser(user) || !setPassword(password))
            clear();
    }

    // Properties.
    inline bool UserInformation::_assign(const std::string_view value, std::string &component) noexcept {
        if (!_test(value))
            return false;

        try {
            component.assign(value);
        } catch (...) {
            return false;
        }

        return true;
    }

    inline std::string_view UserInformation::user() const noexcept {
        return getUser();
    }

    inline bool UserInformation::user(const std::string_view user) noexcept {
        return setUser(user);
    }

    inline std::string_view UserInformation::getUser() const noexcept {
        return _user;
    }

    inline bool UserInformation::setUser(const std::string_view user) noexcept {
        return _assign(user, _user);
    }

    inline std::string_view UserInformation::password() const noexcept {
        return getPassword();
    }

    inline bool UserInformation::password(const std::string_view password) noexcept {
        return setPassword(password);
    }

    inline std::string_view UserInformation::getPassword() const noexcept {
        return _password;
    }

    inline bool UserInformation::setPassword(const std::string_view password) noexcept {
        return _assign(password, _password);
    }

    inline std::size_t UserInformation::length(const bool includePassword) const noexcept {
        std::size_t len = URICalculateEncodedComponentLength(_user);

        if (includePassword && !_password.empty()) {
            ++len;
            len += URICalculateEncodedComponentLength(_password);
        }

        return len;
    }

    inline bool UserInformation::empty() const noexcept {
        return _user.empty() && _password.empty();
    }

    inline void UserInformation::clear() noexcept {
        _user.clear();
        _password.clear();
    }

    // Parsing & Stringification.
    inline bool UserInformation::parse(const std::string_view str) noexcept {
        clear();

        if (str.empty())
            return true;

        const char *const beg = str.cbegin();
        const char *const end = str.cend();

        const char *colon = std::ranges::find(beg, end, ':');

        auto length = static_cast<std::size_t>(std::ranges::distance(beg, colon));
        if (static_cast<std::size_t>(0) != length) {
            if (const auto sv = std::string_view(beg, length);
                !_assign(sv, _user))
                goto parse_bad;

            if (!URIEncodeComponentInPlace(_user))
                goto parse_bad;
        }

        if (colon == end)
            return true;

        std::ranges::advance(colon, static_cast<std::ptrdiff_t>(1));

        length = static_cast<std::size_t>(std::ranges::distance(colon, end));
        if (static_cast<std::size_t>(0) != length) {
            if (const std::string_view sv(colon, length);
                !_assign(sv, _password))
                goto parse_bad;

            if (!URIEncodeComponentInPlace(_password))
                goto parse_bad;
        }

        return true;

    parse_bad:
        clear();
        return false;
    }

    inline std::string UserInformation::stringify(const bool includePassword) const noexcept {
        std::string str;
        return stringify(str, includePassword) ? str : std::string();
    }

    inline bool UserInformation::stringify(std::string &str, const bool includePassword) const noexcept {
        str.clear();

        auto offset = static_cast<std::size_t>(0);
        return stringify(str, offset, includePassword);
    }

    inline bool UserInformation::stringify(std::string &str, std::size_t &offset,
                                           const bool includePassword) const noexcept {
        if (empty())
            return true;

        if (const std::size_t len = (length(includePassword) + offset);
            str.length() < len) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (!_user.empty() && !URIDecodeComponent(_user, str, offset))
            return false;

        if (!_password.empty() && includePassword) {
            str[offset++] = ':';
            if (!URIDecodeComponent(_password, str, offset))
                return false;
        }

        return true;
    }

    // Operators.
    inline UserInformation::operator bool() const noexcept {
        return !empty();
    }

    // Static utility functions.
    inline bool UserInformation::_test(const std::string_view str) noexcept {
        auto pos = static_cast<std::size_t>(0);
        while (pos < str.length()) {
            const char c = str[pos];
            if (RFC::IsUnreserved(c) || RFC::IsSubDelim(c) || ':' == c) {
                ++pos;
                continue;
            }

            if ('%' == c) {
                if (static_cast<std::size_t>(pos + 2) >= str.length())
                    return false;

                if (!RFC::IsHexDig(str[pos + static_cast<std::size_t>(1)]) ||
                    !RFC::IsHexDig(str[pos + static_cast<std::size_t>(2)]))
                    return false;

                pos += static_cast<std::size_t>(3);
                continue;
            }

            return false;
        }

        return pos == str.length();
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_USER_IMPL_USER_IPP
