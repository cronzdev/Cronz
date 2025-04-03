/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_QUERY_IMPL_FIELD_IPP
#define CRONZ_URI_QUERY_IMPL_FIELD_IPP 1

#include "cronz/uri/query/field.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Constructors.
    template<bool Renamable>
    inline QueryField<Renamable>::QueryField(const std::string_view name) noexcept : _name(name) {
    }

    // Properties.
    template<bool Renamable>
    template<typename StringifiableType>
    inline bool QueryField<Renamable>::_stringify(StringifiableType value, std::string &str) noexcept {
        try {
            if constexpr (std::is_integral_v<StringifiableType> || std::is_floating_point_v<StringifiableType>)
                str.assign(std::to_string(value));
            else
                str.assign(value);

            return true;
        } catch (...) {
            return false;
        }
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::_cn(const std::string_view name) const noexcept {
        return (_name.length() == name.length()) &&
               (0 == memcmp(_name.data(), name.data(), _name.length()));
    }

    template<bool Renamable>
    inline std::string_view QueryField<Renamable>::name() const noexcept {
        return _name;
    }

    template<bool Renamable>
    inline std::string &QueryField<Renamable>::name() noexcept requires Renamable {
        return _name;
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::name(const std::string_view name) noexcept requires Renamable {
        try {
            _name.assign(name);
            return true;
        } catch (...) {
            return false;
        }
    }

    template<bool Renamable>
    inline const std::string &QueryField<Renamable>::value() const noexcept {
        static const std::string _;
        return !_values.empty() ? _values[0] : _;
    }

    template<bool Renamable>
    inline std::vector<std::string> &QueryField<Renamable>::values() noexcept {
        return _values;
    }

    template<bool Renamable>
    inline const std::vector<std::string> &QueryField<Renamable>::values() const noexcept {
        return _values;
    }

    template<bool Renamable>
    inline constexpr std::string &QueryField<Renamable>::at(const std::size_t position) noexcept {
        return _values.at(position);
    }

    template<bool Renamable>
    inline constexpr const std::string &QueryField<Renamable>::at(const std::size_t position) const noexcept {
        return _values.at(position);
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::isArray() const noexcept {
        return static_cast<std::size_t>(1) < _values.size();
    }

    template<bool Renamable>
    inline std::size_t QueryField<Renamable>::size() const noexcept {
        return _values.size();
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::empty() const noexcept {
        return _values.empty();
    }

    template<bool Renamable>
    inline std::size_t QueryField<Renamable>::length() const noexcept {
        if (_values.empty())
            return URICalculateEncodedComponentLength(_name);

        std::size_t l = URICalculateEncodedComponentLength(_name);
        if (isArray()) {
            l = ((l + static_cast<std::size_t>(2)) * _values.size());
            l += (_values.size() - static_cast<std::size_t>(1));
        }

        l += _values.size();

        for (const std::string &value: _values) {
            if (!value.empty())
                l += URICalculateEncodedComponentLength(value);
        }

        return l;
    }

    // Stringification.
    template<bool Renamable>
    inline std::string QueryField<Renamable>::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            return {};

        return str;
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    template<bool Renamable>
    inline bool QueryField<Renamable>::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (_values.empty())
            return URIEncodeComponent(_name, str, offset);

        if (!isArray()) {
            if (!URIEncodeComponent(_name, str, offset))
                return false;

            str[offset++] = '=';

            const std::string &value = _values[0];
            return value.empty() || URIEncodeComponent(value, str, offset);
        }

        const std::size_t pos = offset;

        if (!URIEncodeComponent(_name, str, offset))
            return false;

        str[offset++] = '[';
        str[offset++] = ']';

        const std::size_t len = offset - pos;

        bool _f = true;
        for (const std::string &value: _values) {
            if (!_f) {
                str[offset++] = '&';
                memcpy(&str[offset], &str[pos], len);
                offset += len;
            }

            str[offset++] = '=';

            if (!value.empty()) {
                if (!URIEncodeComponent(value, str, offset))
                    return false;
            }

            _f = false;
        }

        return true;
    }

    // Operators.
    template<bool Renamable>
    inline constexpr std::string &QueryField<Renamable>::operator[](std::size_t position) noexcept {
        return _values[position];
    }

    template<bool Renamable>
    inline constexpr const std::string &QueryField<Renamable>::operator[](std::size_t position) const noexcept {
        return _values[position];
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_QUERY_IMPL_FIELD_IPP
