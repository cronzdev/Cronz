/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_URI_IPP
#define CRONZ_URI_IMPL_URI_IPP 1

#include "cronz/uri/uri.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Properties.
    inline std::size_t URI::length() const noexcept {
        auto l = static_cast<std::size_t>(0);

        if (scheme) {
            l += static_cast<std::size_t>(1);
            l += scheme.length();
        }

        if (authority) {
            l += static_cast<std::size_t>(2);
            l += authority.length();
        }

        if (path) {
            if (authority)
                l += static_cast<std::size_t>(1);

            l += path.length();
        }

        if (query) {
            l += static_cast<std::size_t>(1);
            l += query.length();
        }

        if (fragment) {
            l += static_cast<std::size_t>(1);
            l += fragment.length();
        }

        return l;
    }

    // Parsing & Stringification.
    inline bool URI::_scheme(const char *&pos, const char *const end) noexcept {
        if (pos >= end)
            return true;

        const char *const colon = std::ranges::find(pos, end, ':');
        if (end == colon)
            return true;

        if (!scheme.set(std::string_view(pos, colon)))
            return false;

        pos = colon + static_cast<std::ptrdiff_t>(1);
        return true;
    }

    inline bool URI::_authority(const char *&pos, const char *end) noexcept {
        static constexpr std::array<char, static_cast<std::size_t>(3)> delimiters = {'/', '?', '#'};

        if (pos >= end)
            return true;

        if ('/' != *pos)
            return true;

        std::advance(pos, static_cast<std::ptrdiff_t>(1));
        if (end == pos || '/' != *pos)
            return false;

        std::advance(pos, static_cast<std::ptrdiff_t>(1));

        if (end == pos)
            return true;

        const char *const delimiter = std::ranges::find_first_of(pos, end, delimiters.cbegin(), delimiters.cend());
        if (!authority.parse(std::string_view(pos, delimiter)))
            return false;

        pos = delimiter;
        return true;
    }

    inline bool URI::_path(const char *&pos, const char *end) noexcept {
        static constexpr std::array<char, static_cast<std::size_t>(2)> delimiters = {'?', '#'};

        if (pos >= end)
            return true;

        const char *const delimiter = std::ranges::find_first_of(pos, end, delimiters.cbegin(), delimiters.cend());
        if (!path.parse(std::string_view(pos, delimiter)))
            return false;

        pos = delimiter;
        return true;
    }

    inline bool URI::_query(const char *&pos, const char *end) noexcept {
        if (pos >= end || '?' != *pos)
            return true;

        std::advance(pos, static_cast<std::ptrdiff_t>(1));

        const char *delimiter = std::ranges::find(pos, end, '#');
        if (!query.parse(std::string_view(pos, delimiter)))
            return false;

        pos = delimiter;
        return true;
    }

    inline bool URI::_fragment(const char *&pos, const char *end) noexcept {
        if (pos >= end || '#' != *pos)
            return true;

        std::advance(pos, static_cast<std::ptrdiff_t>(1));
        if (!fragment.parse(std::string_view(pos, end)))
            return false;

        pos = end;
        return true;
    }

    inline bool URI::parse(const std::string_view str) noexcept {
        clear();

        const char *pos = str.cbegin();
        const char *const end = str.cend();

        if (!_scheme(pos, end))
            goto parse_bad;

        if (!_authority(pos, end))
            goto parse_bad;

        if (!_path(pos, end))
            goto parse_bad;

        if (!_query(pos, end))
            goto parse_bad;

        if (!_fragment(pos, end))
            goto parse_bad;

        if (pos >= end)
            return true;

    parse_bad:
        clear();
        return false;
    }

    inline std::string URI::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            return {};

        return str;
    }

    inline bool URI::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool URI::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.size()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (scheme) {
            if (!scheme.stringify(str, offset))
                return false;

            str[offset++] = ':';
        }

        if (authority) {
            str[offset++] = '/';
            str[offset++] = '/';

            if (!authority.stringify(str, offset))
                return false;
        }

        if (path) {
            if (authority)
                str[offset++] = '/';

            if (!path.stringify(str, offset))
                return false;
        }

        if (query) {
            str[offset++] = '?';

            if (!query.stringify(str, offset))
                return false;
        }

        if (fragment) {
            str[offset++] = '#';

            if (!fragment.stringify(str, offset))
                return false;
        }

        return true;
    }

    // Instance-based utility functions.
    inline bool URI::empty() const noexcept {
        return scheme.empty();
    }

    inline void URI::clear() noexcept {
        scheme.clear();
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_IMPL_URI_IPP
