/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_URL_IPP
#define CRONZ_URI_IMPL_URL_IPP 1

#include "cronz/uri/url.hpp"

CRONZ_BEGIN_URL_NAMESPACE
    // Parsing & Stringification.
    inline bool URL::_schema(const char *&pos, const char *const end) noexcept {
        if (const std::ranges::subrange<const char *> range = std::ranges::search(
                pos, end, SchemeSeparator.data(), SchemeSeparator.data() + SchemeSeparator.length());
            !range.empty()) {
            if (range.cbegin() == range.cend())
                return false;

            if (!scheme.set(std::string_view(pos, range.cbegin())))
                return false;

            pos = range.end();
        }

        return true;
    }

    inline bool URL::parse(const std::string_view str) noexcept {
        const char *pos = str.cbegin();
        const char *const end = str.cend();

        if (!_schema(pos, end))
            goto parse_bad;

        return true;

    parse_bad:
        clear();
        return false;
    }

    // Instance-based utility functions.
    inline bool URL::empty() const noexcept {
        return scheme.empty();
    }

    inline void URL::clear() noexcept {
        scheme.clear();
    }

CRONZ_END_URL_NAMESPACE

#endif // CRONZ_URI_IMPL_URL_IPP
