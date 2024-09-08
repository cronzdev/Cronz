/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_PATH_IMPL_MANAGER_IPP
#define CRONZ_URL_PATH_IMPL_MANAGER_IPP 1

#include "cronz/url/path/manager.hpp"
#include "cronz/url/encode.hpp"

#include <algorithm>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline PathManager::PathManager() noexcept = default;

    // Iterators.
    inline PathManager::Iterator PathManager::begin() noexcept {
        return paths_.begin();
    }

    inline PathManager::Iterator PathManager::end() noexcept {
        return paths_.end();
    }

    inline PathManager::ConstIterator PathManager::cbegin() const noexcept {
        return paths_.cbegin();
    }

    inline PathManager::ConstIterator PathManager::cend() const noexcept {
        return paths_.cend();
    }

    inline PathManager::ReverseIterator PathManager::rbegin() noexcept {
        return paths_.rbegin();
    }

    inline PathManager::ReverseIterator PathManager::rend() noexcept {
        return paths_.rend();
    }

    inline PathManager::ConstReverseIterator PathManager::crbegin() const noexcept {
        return paths_.crbegin();
    }

    inline PathManager::ConstReverseIterator PathManager::crend() const noexcept {
        return paths_.crend();
    }

    // Path management.
    inline bool PathManager::addPath(const std::string &path) noexcept {
        if (path.empty())
            return true;

        try {
            paths_.push_back(path);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    inline bool PathManager::addEncodedPath(const std::string &path) noexcept {
        std::string decoded;
        return Decode(path, decoded) && addPath(decoded);
    }

    inline std::string& PathManager::at(const std::size_t &position) noexcept {
        return paths_.at(position);
    }

    inline const std::string& PathManager::at(const std::size_t &position) const noexcept {
        return paths_.at(position);
    }

    inline void PathManager::removeAt(const std::size_t &position) noexcept {
        if (position >= paths_.size())
            return;

        auto it = paths_.begin();
        std::advance(it, position);
        paths_.erase(it);
    }

    inline PathManager::Iterator PathManager::removeAt(const Iterator &position) noexcept {
        return paths_.erase(position);
    }

    inline PathManager::ConstIterator PathManager::removeAt(const ConstIterator &position) noexcept {
        return paths_.erase(position);
    }

    inline bool PathManager::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline bool PathManager::parse(const char *str, const std::size_t &length) noexcept {
        auto added = static_cast<std::size_t>(0);

        const char *const end = str + length;
        const char *previous = str;
        while (previous < end) {
            const char *current = std::ranges::find(previous, end, '/');
            const std::size_t currentLength = current - previous;

            if (static_cast<std::size_t>(0) != currentLength) {
                std::string decoded;
                if (!Decode(previous, currentLength, decoded))
                    goto bad;

                try {
                    paths_.push_back(std::move(decoded));
                }
                catch (...) {
                    goto bad;
                }

                ++added;
            }

            previous = current + static_cast<std::size_t>(1);
        }

        return true;

    bad:
        while (added--)
            paths_.pop_back();

        return false;
    }

    inline void PathManager::clear() noexcept {
        paths_.clear();
    }

    // Properties.
    inline std::size_t PathManager::count() const noexcept {
        return paths_.size();
    }

    inline std::size_t PathManager::size() const noexcept {
        return count();
    }

    inline std::size_t PathManager::length() const noexcept {
        std::size_t len = count();

        for (const std::string &path : paths_)
            len += CalculateEncodedLength(path);

        return std::max(len, static_cast<std::size_t>(1));
    }

    inline bool PathManager::empty() const noexcept {
        return paths_.empty();
    }

    // Conversion.
    inline std::string PathManager::stringify() const noexcept {
        std::string str;
        [[maybe_unused]] const bool _ = stringify(str, static_cast<std::size_t>(0));
        return str;
    }

    inline bool PathManager::stringify(std::string &str) const noexcept {
        str.clear();
        return stringify(str, static_cast<std::size_t>(0));
    }

    inline bool PathManager::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (const std::size_t stringifiedLength = (length() + offset); stringifiedLength > str.length()) {
            try {
                str.resize(stringifiedLength);
            }
            catch (...) {
                return false;
            }
        }

        if (empty()) {
            str[offset] = '/';
            return true;
        }

        std::size_t o = offset;
        for (const std::string &path : paths_) {
            str[o++] = '/';
            o += Encode(path, &str[o]);
        }

        return true;
    }

    // Operators.
    inline PathManager::operator bool() const noexcept {
        return !empty();
    }

    inline std::string& PathManager::operator[](const std::size_t &position) noexcept {
        return at(position);
    }

    inline const std::string& PathManager::operator[](const std::size_t &position) const noexcept {
        return at(position);
    }

    // Destructors.
    inline PathManager::~PathManager() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_PATH_IMPL_MANAGER_IPP
