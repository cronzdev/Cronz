/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_FRAGMENT_IPP
#define CRONZ_URI_IMPL_FRAGMENT_IPP 1

#include "cronz/uri/fragment.hpp"

#include "cronz/rfc/rule/pchar.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Constructors.
    inline Fragment::Fragment(const std::string_view fragment) noexcept {
        [[maybe_unused]] const bool _ = set(fragment);
    }

    // Properties.
    inline std::string_view Fragment::get() const noexcept {
        return _value;
    }

    inline bool Fragment::set(const std::string_view fragment) noexcept {
        try {
            _value.assign(fragment);
            return true;
        } catch (...) {
            return false;
        }
    }

    inline std::size_t Fragment::length() const noexcept {
        return URICalculateEncodedComponentLength(_value);
    }

    inline bool Fragment::empty() const noexcept {
        return _value.empty();
    }

    inline void Fragment::clear() noexcept {
        _value.clear();
    }

    // Parsing & Stringification.
    inline bool Fragment::parse(std::string_view fragment) noexcept {
        auto i = static_cast<std::size_t>(0);
        while (i < fragment.size()) {
            const char c = fragment[i];

            if (!RFC::IsPChar(c) && '/' != c && '?' != c)
                return false;

            ++i;

            if ('%' != c)
                continue;

            if ((static_cast<std::size_t>(2) + i) >= fragment.size())
                return false;

            if (!RFC::IsHexDig(fragment[i]) ||
                !RFC::IsHexDig(fragment[i + static_cast<std::size_t>(1)]))
                return false;

            i += static_cast<std::size_t>(2);
        }

        if (i != fragment.size())
            return false;

        if (URIDecodeComponent(fragment, _value))
            return true;

        _value.clear();
        return false;
    }

    inline std::string Fragment::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            return {};

        return str;
    }

    inline bool Fragment::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool Fragment::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.size()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        return URIEncodeComponent(_value, str, offset);
    }

    // Operators.
    inline Fragment::operator bool() const noexcept {
        return !_value.empty();
    }

    inline Fragment::operator std::string_view() const noexcept {
        return get();
    }

    inline Fragment &Fragment::operator=(const std::string_view fragment) noexcept {
        [[maybe_unused]] const bool _ = set(fragment);
        return *this;
    }

    inline bool Fragment::operator==(const std::string_view fragment) const noexcept {
        return _value == fragment;
    }

    inline bool Fragment::operator==(const Fragment &fragment) const noexcept {
        return _value == fragment._value;
    }

    inline bool Fragment::operator!=(const std::string_view fragment) const noexcept {
        return _value != fragment;
    }

    inline bool Fragment::operator!=(const Fragment &fragment) const noexcept {
        return _value != fragment._value;
    }

    // Friends.
    inline bool operator==(const std::string_view fragment, const Fragment &instance) noexcept {
        return fragment == instance._value;
    }

    inline bool operator!=(const std::string_view fragment, const Fragment &instance) noexcept {
        return fragment != instance._value;
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_IMPL_FRAGMENT_IPP
