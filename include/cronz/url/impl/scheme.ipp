/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_IMPL_SCHEME_IPP
#define CRONZ_URL_IMPL_SCHEME_IPP 1

#include "cronz/url/scheme.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline Scheme::Scheme() noexcept = default;

    inline Scheme::Scheme(const std::string &value) noexcept {
        [[maybe_unused]] const bool _ = setValue(value);
    }

    // Getters & Setters.
    inline const std::string& Scheme::getValue() const noexcept {
        return value_;
    }

    inline bool Scheme::setValue(const char *value) noexcept {
        return setValue(value, std::strlen(value));
    }

    inline bool Scheme::setValue(const char *value, const std::size_t &length) noexcept {
        if (nullptr == value || static_cast<std::size_t>(0) == length) {
            clear();
            return true;
        }

        std::string temp;
        try {
            temp.resize(length);
            memcpy(temp.data(), value, length);
        }
        catch (...) {
            return false;
        }

        for (auto &c : temp) {
            if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || '+' == c || '-' == c || '.' == c)
                continue;

            if ('A' <= c && c <= 'Z')
                c += ('a' - 'A');
            else
                return false;
        }

        if (!('a' <= temp[0] && temp[0] <= 'z'))
            return false;

        value_.swap(temp);

        return true;
    }

    inline bool Scheme::setValue(const std::string &value) noexcept {
        return setValue(value.data(), value.length());
    }

    // Properties.
    inline std::size_t Scheme::length() const noexcept {
        return value_.length();
    }

    inline bool Scheme::empty() const noexcept {
        return value_.empty();
    }

    inline void Scheme::clear() noexcept {
        value_.clear();
    }

    // Stringification.
    inline std::string Scheme::stringify() const noexcept {
        return value_;
    }

    inline bool Scheme::stringify(std::string &str) const noexcept {
        try {
            str.assign(value_);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    inline bool Scheme::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (const std::size_t len = value_.length() + offset; len > str.length()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        memcpy(&str[offset], value_.data(), value_.length());

        return true;
    }

    // Operators.
    inline Scheme::operator bool() const noexcept {
        return !empty();
    }

    inline Scheme::operator const std::string&() const noexcept {
        return getValue();
    }

    inline Scheme& Scheme::operator=(const std::string &value) noexcept {
        [[maybe_unused]] const bool _ = setValue(value);
        return *this;
    }

    inline bool Scheme::operator==(const Scheme &scheme) const noexcept {
        return value_ == scheme.value_;
    }

    inline bool Scheme::operator==(const std::string &scheme) const noexcept {
        auto offset = static_cast<std::size_t>(0);
        return scheme.length() == value_.length() && std::ranges::all_of(value_, [&](const char &c) -> bool {
            const char &c2 = value_[offset++];
            return c == c2 || (('A' <= c && c <= 'Z') ? (c2 == (c - ' ')) : false);
        });
    }

    inline bool Scheme::operator!=(const Scheme &scheme) const noexcept {
        return value_ != scheme.value_;
    }

    inline bool Scheme::operator!=(const std::string &scheme) const noexcept {
        return !operator==(scheme);
    }

    // Destructor.
    inline Scheme::~Scheme() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif //
