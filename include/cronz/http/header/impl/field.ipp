/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_HEADER_IMPL_FIELD_IPP
#define CRONZ_HTTP_HEADER_IMPL_FIELD_IPP 1

#include "cronz/http/header/field.hpp"

#include "cronz/rfc/rule/alpha.hpp"
#include "cronz/rfc/rule/header.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline const std::string &HeaderField::name() const noexcept {
        return _name;
    }

    inline bool HeaderField::name(const std::string_view name) noexcept {
        if (!RFC::IsHeaderFieldName(name))
            return false;

        try {
            _name.assign(name);
        } catch (...) {
            return false;
        }

        _normalize(_name);
        return true;
    }

    inline const std::string &HeaderField::value() const noexcept {
        return _value;
    }

    inline bool HeaderField::value(const std::string_view value) noexcept {
        if (!RFC::IsHeaderFieldValue(value))
            return false;

        try {
            _value.assign(value);
        } catch (...) {
            return false;
        }

        return true;
    }

    inline std::size_t HeaderField::length() const noexcept {
        return _name.length() + static_cast<std::size_t>(2) + _value.length();
    }

    inline bool HeaderField::empty() const noexcept {
        return _name.empty();
    }

    // Parsing & Stringification.
    inline bool HeaderField::parse(const std::string_view header) noexcept {
        const char *const beg = header.cbegin();
        const char *const end = header.cend();

        const char *const colon = std::find(beg, end, ':');
        if (colon == end)
            return false;

        const std::string_view name(beg, colon);
        if (!RFC::IsHeaderFieldName(name))
            return false;

        std::string_view value(colon + static_cast<std::ptrdiff_t>(1), end);
        if (static_cast<std::size_t>(2) <= value.length()) {
            if ('\r' == value[value.length() - static_cast<std::size_t>(2)] &&
                '\n' == value[value.length() - static_cast<std::size_t>(1)])
                value.remove_suffix(static_cast<std::size_t>(2));
        }

        while (!value.empty()) {
            if (const char c = value.front();
                RFC::IsSpace(c) || RFC::IsHorizontalTab(c))
                value.remove_prefix(static_cast<std::size_t>(1));
            else
                break;
        }

        while (!value.empty()) {
            if (const char c = value.back();
                RFC::IsSpace(c) || RFC::IsHorizontalTab(c))
                value.remove_suffix(static_cast<std::size_t>(1));
            else
                break;
        }

        if (!RFC::IsHeaderFieldValue(value))
            return false;

        try {
            _name.assign(name);
            _value.assign(value);
        } catch (...) {
            return false;
        }

        _normalize(_name);
        return true;
    }

    inline std::string HeaderField::stringify() const noexcept {
        if (std::string str;
            stringify(str))
            return str;

        return {};
    }

    inline bool HeaderField::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool HeaderField::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        memcpy(&str[offset], _name.data(), _name.length());
        offset += _name.length();

        str[offset++] = ':';
        str[offset++] = ' ';

        memcpy(&str[offset], _value.data(), _value.length());
        offset += _value.length();

        return true;
    }

    // Instance-based utility functions.
    inline bool HeaderField::_cn(const std::string_view name) const noexcept {
        return RFC::CompareAlphaCaseInsensitive(name, _name);
    }

    template<typename ConvertibleType>
        requires (std::is_integral_v<ConvertibleType> || std::is_floating_point_v<ConvertibleType> ||
                  std::is_same_v<ConvertibleType, std::string> || std::is_same_v<ConvertibleType, std::vector<char> >)
    inline bool HeaderField::as(ConvertibleType &val) const noexcept {
        if constexpr (std::is_integral_v<ConvertibleType>) {
            char *err = nullptr;
            const long long num = std::strtoll(_value.c_str(), &err, 10);
            if (err == _value.c_str() || *err != '\0')
                return false;

            if (num < std::numeric_limits<ConvertibleType>::min() ||
                num > std::numeric_limits<ConvertibleType>::max())
                return false;

            val = static_cast<ConvertibleType>(num);
            return true;
        }

        if constexpr (std::is_floating_point_v<ConvertibleType>) {
            char *err = nullptr;
            val = std::strtod(_value.c_str(), &err);
            if (err == _value.c_str() || *err != '\0')
                return false;

            return true;
        }

        if constexpr (std::is_same_v<ConvertibleType, std::string>) {
            try {
                val.assign(_value);
                return true;
            } catch (...) {
                return false;
            }
        }

        if constexpr (std::is_same_v<ConvertibleType, std::vector<char> >) {
            try {
                val.assign(_value.begin(), _value.end());
                return true;
            } catch (...) {
                return false;
            }
        }

        return false;
    }

    // Static utility functions.
    inline void HeaderField::_normalize(std::string &str) noexcept {
        bool _alpha = false;
        for (char &c: str) {
            const bool a = RFC::IsAlpha(c);
            if (a && _alpha)
                c = RFC::ToAlphaLower(c);

            if (a && !_alpha)
                c = RFC::ToAlphaUpper(c);

            _alpha = a;
        }
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_HEADER_IMPL_FIELD_IPP
