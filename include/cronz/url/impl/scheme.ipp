/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_IMPL_SCHEME_IPP
#define CRONZ_URL_IMPL_SCHEME_IPP 1

#include "cronz/url/scheme.hpp"

#include "cronz/rfc/rule/scheme.hpp"

CRONZ_BEGIN_URL_NAMESPACE
    // Constructors.
    inline Scheme::Scheme(const std::string_view scheme) noexcept {
        [[maybe_unused]] const bool _ = set(scheme);
    }

    // Properties.
    inline std::string_view Scheme::get() const noexcept {
        return _value;
    }

    inline bool Scheme::set(const std::string_view scheme) noexcept {
        if (!RFC::IsScheme(scheme))
            return false;

        try {
            _value.assign(scheme);
        } catch (...) {
            return false;
        }

        for (char &c: _value) {
            if (RFC::IsAlphaUpper(c))
                c = static_cast<char>(c + 32);
        }

        return true;
    }

    inline std::size_t Scheme::length() const noexcept {
        return _value.length();
    }

    inline bool Scheme::empty() const noexcept {
        return _value.empty();
    }

    inline void Scheme::clear() noexcept {
        _value.clear();
    }

    // Stringification.
    inline std::string Scheme::stringify() const noexcept {
        std::string scheme;
        if (!stringify(scheme))
            scheme.clear();

        return scheme;
    }

    inline bool Scheme::stringify(std::string &scheme) const noexcept {
        auto offset = static_cast<std::size_t>(0);
        return stringify(scheme, offset);
    }

    inline bool Scheme::stringify(std::string &scheme, std::size_t &offset) const noexcept {
        if (const std::size_t length = _value.length() + offset;
            length > scheme.size()) {
            try {
                scheme.resize(length);
            } catch (...) {
                return false;
            }
        }

        memcpy(scheme.data() + offset, _value.data(), _value.length());
        offset += _value.length();

        return true;
    }

    // Instance-based utility functions.
    inline bool Scheme::compare(const std::string_view scheme) const noexcept {
        return _compare(scheme);
    }

    inline bool Scheme::compare(const Scheme &scheme) const noexcept {
        return compare(scheme._value);
    }

    // Operators.
    inline Scheme::operator bool() const noexcept {
        return !empty();
    }

    inline Scheme::operator std::string_view() const noexcept {
        return get();
    }

    inline Scheme &Scheme::operator=(const std::string_view scheme) noexcept {
        [[maybe_unused]] const bool _ = set(scheme);
        return *this;
    }

    inline bool Scheme::operator==(const std::string_view scheme) const noexcept {
        return _compare(scheme);
    }

    inline bool Scheme::operator==(const Scheme &scheme) const noexcept {
        return _compare(scheme._value);
    }

    inline bool Scheme::operator!=(const std::string_view scheme) const noexcept {
        return !_compare(scheme);
    }

    inline bool Scheme::operator!=(const Scheme &scheme) const noexcept {
        return !_compare(scheme._value);
    }

    // Static utility functions.
    inline bool Scheme::_compare(const std::string_view scheme) const noexcept {
        if (_value.length() != scheme.length())
            return false;

        return std::ranges::equal(_value, scheme, [](const char a, const char b) -> bool {
            return RFC::CompareAlphaCaseInsensitive(a, b);
        });
    }

    // Friends.
    inline bool operator==(const std::string_view scheme, const Scheme &instance) noexcept {
        return instance._compare(scheme);
    }

    inline bool operator!=(const std::string_view scheme, const Scheme &instance) noexcept {
        return !instance._compare(scheme);
    }

CRONZ_END_URL_NAMESPACE

#endif // CRONZ_URL_IMPL_SCHEME_IPP
