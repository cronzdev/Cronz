/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_IMPL_PATH_IPP
#define CRONZ_RFC_RULE_IMPL_PATH_IPP 1

#include "cronz/rfc/rule/path.hpp"
#include "cronz/rfc/rule/pchar.hpp"

#include <algorithm>

CRONZ_BEGIN_RFC_NAMESPACE
    inline bool IsPath(const std::string_view path) noexcept {
        return path.empty() ||
               IsPathAbEmpty(path) || IsPathAbsolute(path) ||
               IsPathNoScheme(path) || IsPathRootless(path);
    }

    inline bool IsPathAbEmpty(std::string_view path) noexcept {
        return path.empty() || IsPathAbsolute(std::move(path));
    }

    inline bool IsPathAbsolute(std::string_view path) noexcept {
        if (path.empty() || '/' != path.front())
            return false;

        path.remove_prefix(static_cast<std::size_t>(1));
        return IsPathRootless(std::move(path));
    }

    inline bool IsPathNoScheme(const std::string_view path) noexcept {
        if (path.empty() || '/' == path.front() || ':' == path.front())
            return false;

        const char *beg = path.cbegin();
        const char *const end = path.cend();

        bool first = true;

        while (beg < end) {
            const char *const slash = std::ranges::find(beg, end, '/');
            if (first && slash == beg)
                return false;

            if (const std::string_view segment(beg, slash);
                !IsSegment(segment))
                return false;

            beg = slash + static_cast<std::ptrdiff_t>(1);
            first = false;
        }

        return true;
    }

    inline bool IsPathRootless(const std::string_view path) noexcept {
        if (path.empty() || '/' == path.front())
            return false;

        const char *beg = path.cbegin();
        const char *const end = path.cend();

        bool first = true;

        while (beg < end) {
            const char *const slash = std::ranges::find(beg, end, '/');
            if (first && slash == beg)
                return false;

            if (const std::string_view segment(beg, slash);
                !IsSegment(segment))
                return false;

            beg = slash + static_cast<std::ptrdiff_t>(1);
            first = false;
        }

        return true;
    }

    inline bool IsPathEmpty(const std::string_view path) noexcept {
        return path.empty();
    }

    inline bool IsSegment(const std::string_view segment) noexcept {
        return IsPChar(segment);
    }

    inline bool IsSegmentNz(const std::string_view segment) noexcept {
        return !segment.empty() && IsSegment(segment);
    }

    inline bool IsSegmentNzNc(const std::string_view segment) noexcept {
        return IsSegmentNz(segment) && std::ranges::none_of(segment, [](const char c) noexcept -> bool {
            return ':' == c;
        });
    }

CRONZ_END_RFC_NAMESPACE

#endif // CRONZ_RFC_RULE_IMPL_PATH_IPP
