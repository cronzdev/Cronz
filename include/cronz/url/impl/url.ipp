/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_IMPL_URL_IPP
#define CRONZ_URL_IMPL_URL_IPP 1

#include "cronz/url/url.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline URL::URL() noexcept = default;

    inline URL::URL(const char *str) noexcept {
        [[maybe_unused]] const bool _ = parse(str);
    }

    inline URL::URL(const char *str, const std::size_t &length) noexcept {
        [[maybe_unused]] const bool _ = parse(str, length);
    }

    inline URL::URL(const std::string &str) noexcept {
        [[maybe_unused]] const bool _ = parse(str);
    }

    // Parsing.
    inline bool URL::parseScheme_(const char *&beg, const char *end) noexcept {
        if (const auto range = std::ranges::search(beg, end, SchemeSeparator, SchemeSeparator + SchemeSeparatorLength);
            !range.empty()) {
            if (const std::size_t schemeLength = range.begin() - beg; static_cast<std::size_t>(0) == schemeLength || !
                scheme.setValue(beg, schemeLength))
                return false;

            beg = range.end();
        }

        return true;
    }

    inline bool URL::parseAuthority_(const char *&beg, const char *end) noexcept {
        static constexpr auto authoritySeparators = "/?#";
        static constexpr std::size_t authoritySeparatorsLength = std::strlen(authoritySeparators);

        const char *next = std::ranges::find_first_of(beg, end, authoritySeparators,
                                                      authoritySeparators + authoritySeparatorsLength);

        if (beg == next)
            return scheme.empty();

        if (!authority.parse(beg, next - beg))
            return false;

        beg = ((end == next) ? (end) : (next + static_cast<std::size_t>(1)));
        return true;
    }

    inline bool URL::parsePath_(const char *&beg, const char *end) noexcept {
        static constexpr auto pathSeparators = "?#";
        static constexpr std::size_t pathSeparatorsLength = std::strlen(pathSeparators);

        const char *next = std::ranges::find_first_of(beg, end, pathSeparators, pathSeparators + pathSeparatorsLength);

        if (!path.parse(beg, next - beg))
            return false;

        beg = ((end == next) ? (end) : (next + static_cast<std::size_t>(1)));
        return true;
    }

    inline bool URL::parseQuery_(const char *&beg, const char *end) noexcept {
        const char *next = std::ranges::find(beg, end, '#');

        if (!query.parse(beg, next - beg))
            return false;

        beg = ((end == next) ? end : (next + static_cast<std::size_t>(1)));
        return true;
    }

    inline bool URL::parseFragment_(const char *&beg, const char *end) noexcept {
        if (beg >= end)
            return true;

        try {
            fragment.resize(end - beg);
        }
        catch (...) {
            return false;
        }

        memcpy(fragment.data(), beg, end - beg);
        return true;
    }

    inline bool URL::parse(const char *str) noexcept {
        return parse(str, std::strlen(str));
    }

    inline bool URL::parse(const char *str, const std::size_t &length) noexcept {
        const char *const end = str + length;
        const char *beg = str;

        if (!parseScheme_(beg, end) ||
            !parseAuthority_(beg, end) ||
            !parsePath_(beg, end) ||
            !parseQuery_(beg, end) ||
            !parseFragment_(beg, end))
            goto bad;

        return true;

    bad:
        clear();
        return false;
    }

    inline bool URL::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline std::string URL::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            str.clear();

        return str;
    }

    inline bool URL::stringify(std::string &str) const noexcept {
        str.clear();
        return stringify(str, static_cast<std::size_t>(0));
    }

    inline bool URL::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (scheme && !authority)
            return false;

        if (const std::size_t len = (offset + length()); len > str.size()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        std::size_t o = offset;

        if (scheme) {
            if (!scheme.stringify(str, o))
                return false;

            o += scheme.length();

            memcpy(&str[o], SchemeSeparator, SchemeSeparatorLength);
            o += SchemeSeparatorLength;
        }

        if (authority) {
            if (!authority.stringify(str, o))
                return false;

            o += authority.length();
        }

        if (!path.stringify(str, o))
            return false;

        o += path.length();

        if (query) {
            str[o] = '?';

            if (!query.stringify(str, ++o))
                return false;

            o += query.length();
        }

        if (!fragment.empty()) {
            str[o++] = '#';
            memcpy(&str[o], fragment.c_str(), fragment.length());
        }

        return true;
    }

    // Instance-based utility functions.
    inline std::size_t URL::length() const noexcept {
        auto len = static_cast<std::size_t>(0);

        if (scheme) {
            len += scheme.length();
            len += SchemeSeparatorLength;
        }

        if (authority)
            len += authority.length();

        len += path.length();

        if (query) {
            len += query.length();
            len += static_cast<std::size_t>(1);
        }

        if (!fragment.empty()) {
            len += fragment.length();
            len += static_cast<std::size_t>(1);
        }

        return len;
    }

    inline bool URL::empty() const noexcept {
        return scheme.empty() && authority.empty() && path.empty() && query.empty() && fragment.empty();
    }

    inline void URL::clear() noexcept {
        scheme.clear();
        authority.clear();
        path.clear();
        query.clear();
        fragment.clear();
    }

    // Destructors.
    inline URL::~URL() noexcept = default;

    // Static utility functions.
    inline URL URL::Parse(const char *str) noexcept {
        return Parse(str, std::strlen(str));
    }

    inline URL URL::Parse(const char *str, const std::size_t &length) noexcept {
        URL url;
        if (!Parse(str, length, url))
            url.clear();

        return url;
    }

    inline URL URL::Parse(const std::string &str) noexcept {
        return Parse(str.c_str(), str.length());
    }

    inline bool URL::Parse(const char *str, URL &url) noexcept {
        return Parse(str, std::strlen(str), url);
    }

    inline bool URL::Parse(const char *str, const std::size_t &length, URL &url) noexcept {
        return url.parse(str, length);
    }

    inline bool URL::Parse(const std::string &str, URL &url) noexcept {
        return Parse(str.c_str(), str.length(), url);
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_IMPL_URL_IPP
