/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_PATH_IPP
#define CRONZ_URI_IMPL_PATH_IPP 1

#include "cronz/uri/path.hpp"

#include "cronz/rfc/rule/path.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Constructors.
    inline Path::Path(const std::string_view path) noexcept {
        [[maybe_unused]] const bool _ = parse(path);
    }

    // Properties.
    inline bool Path::isRoot() const noexcept {
        return _root;
    }

    inline void Path::setRoot(const bool root) noexcept {
        _root = root;
    }

    inline std::size_t Path::count() const noexcept {
        return _segments.size();
    }

    inline bool Path::empty() const noexcept {
        return _segments.empty() && !isRoot();
    }

    inline std::size_t Path::length() const noexcept {
        if (_segments.empty())
            return isRoot() ? static_cast<std::size_t>(1) : static_cast<std::size_t>(0);

        std::size_t len = count();

        if (!isRoot())
            --len;

        for (const std::string &segment: _segments)
            len += URICalculateEncodedComponentLength(segment);

        return len;
    }

    // Instance-based utility functions.
    inline bool Path::_insert(const ArrayType::const_iterator position, const std::string_view path,
                              const bool raw) noexcept {
        std::vector<std::string> segments{};

        if (raw) {
            try {
                segments.emplace_back(path);
            } catch (...) {
                return false;
            }
        } else {
            if (!_segmentize(path, segments))
                return false;
        }

        if (segments.empty())
            return true;

        if (_segments.empty()) {
            _segments.swap(segments);
            return true;
        }

        try {
            _segments.insert(position, segments.begin(), segments.end());
            return true;
        } catch (...) {
            return false;
        }
    }

    inline bool Path::append(const std::string_view segment, const bool raw) noexcept {
        return _insert(_segments.cend(), segment, raw);
    }

    inline bool Path::prepend(const std::string_view segment, const bool raw) noexcept {
        if (!_insert(_segments.cbegin(), segment, raw))
            return false;

        _root = (!raw && !segment.empty() && '/' == segment.front());
        return true;
    }

    inline bool Path::parse(const std::string_view path) noexcept {
        std::vector<std::string> segments{};
        if (!_segmentize(path, segments))
            return false;

        _root = (!path.empty() && '/' == path.front());
        _segments.swap(segments);
        return true;
    }

    inline std::string Path::stringify() const noexcept {
        std::string str;
        return stringify(str) ? str : std::string();
    }

    inline bool Path::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool Path::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        bool _first = !isRoot();
        for (const std::string &segment: _segments) {
            if (!_first)
                str[offset++] = '/';

            if (!URIEncodeComponent(segment, str, offset))
                return false;

            _first = false;
        }

        return true;
    }

    inline void Path::clear() noexcept {
        _segments.clear();
    }

    // Iterators.
    inline constexpr Path::Iterator Path::begin() noexcept {
        return _segments.begin();
    }

    inline constexpr Path::ConstIterator Path::begin() const noexcept {
        return _segments.cbegin();
    }

    inline constexpr Path::Iterator Path::end() noexcept {
        return _segments.end();
    }

    inline constexpr Path::ConstIterator Path::end() const noexcept {
        return _segments.cend();
    }

    inline constexpr Path::ConstIterator Path::cbegin() const noexcept {
        return _segments.cbegin();
    }

    inline constexpr Path::ConstIterator Path::cend() const noexcept {
        return _segments.cend();
    }

    inline constexpr Path::ReverseIterator Path::rbegin() noexcept {
        return _segments.rbegin();
    }

    inline constexpr Path::ReverseIterator Path::rend() noexcept {
        return _segments.rend();
    }

    inline constexpr Path::ConstReverseIterator Path::crbegin() const noexcept {
        return _segments.crbegin();
    }

    inline constexpr Path::ConstReverseIterator Path::crend() const noexcept {
        return _segments.crend();
    }

    // Segments.
    inline constexpr std::string &Path::at(const std::size_t position) {
        return _segments.at(position);
    }

    inline constexpr const std::string &Path::at(const std::size_t position) const {
        return _segments.at(position);
    }

    inline constexpr Path::Iterator Path::removeAt(const std::size_t position) noexcept {
        if (position >= _segments.size())
            return _segments.end();

        Iterator it = _segments.begin();
        std::advance(it, static_cast<std::ptrdiff_t>(position));
        return removeAt<Iterator>(it);
    }

    template<typename IteratorType>
        requires (std::is_same_v<IteratorType, Path::Iterator> || std::is_same_v<IteratorType, Path::ConstIterator>)
    inline constexpr IteratorType Path::removeAt(IteratorType position) noexcept {
        if (_segments.begin() > position || _segments.end() <= position)
            return _segments.end();

        return _segments.erase(position);
    }

    // Operators.
    inline Path::operator bool() const noexcept {
        return !empty();
    }

    inline Path &Path::operator=(const std::string_view path) noexcept {
        [[maybe_unused]] const bool _ = parse(path);
        return *this;
    }

    inline constexpr std::string &Path::operator[](const std::size_t position) {
        return _segments[position];
    }

    inline constexpr const std::string &Path::operator[](const std::size_t position) const {
        return _segments[position];
    }

    // Static utility functions.
    inline bool Path::_segmentize(const std::string_view path, std::vector<std::string> &segments) noexcept {
        segments.clear();

        if (path.empty())
            return true;

        if (static_cast<std::size_t>(1) == path.length() && '/' == path[0])
            return true;

        if (!RFC::IsPath(path))
            return false;

        const std::size_t slashCount = std::ranges::count_if(path, [](const char c) noexcept -> bool {
            return '/' == c;
        }) + static_cast<std::size_t>('/' == path[0] ? 0 : 1);

        try {
            segments.reserve(slashCount);
        } catch (...) {
            return false;
        }

        const char *const beg = path.cbegin();
        const char *const end = path.cend();

        const char *pos = beg;
        if ('/' == *pos)
            ++pos;

        while (pos < end) {
            const char *const slash = std::ranges::find(pos, end, '/');
            const auto length = static_cast<std::size_t>(std::distance(pos, slash));

            std::string segment{};
            try {
                segment.append(pos, length);
            } catch (...) {
                return false;
            }

            if (!segment.empty() && !URIEncodeComponentInPlace(segment))
                return false;

            printf("segment: <%s>\n", segment.c_str());

            segments.emplace_back(std::move(segment));

            pos = slash + static_cast<std::ptrdiff_t>(1);
        }

        return true;
    }

CRONZ_END_URI_NAMESPACE

#endif //CRONZ_URI_IMPL_PATH_IPP
