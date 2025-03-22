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
        if (std::ranges::all_of(fragment, [](const char c) -> bool {
            return RFC::IsPChar(c) || '/' == c || '?' == c;
        })) {
            try {
                _value.assign(fragment);
                return true;
            } catch (...) {
                return false;
            }
        }

        return false;
    }

    inline bool Fragment::empty() const noexcept {
        return _value.empty();
    }

    inline void Fragment::clear() noexcept {
        _value.clear();
    }

    // Operators.
    inline Fragment::operator bool() const noexcept {
        return _value.empty();
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
