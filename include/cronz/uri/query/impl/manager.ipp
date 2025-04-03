/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_QUERY_IMPL_MANAGER_IPP
#define CRONZ_URI_QUERY_IMPL_MANAGER_IPP 1

#include "cronz/uri/query/manager.hpp"
#include "cronz/uri/encode.hpp"
#include "cronz/uri/decode.hpp"

#include <ranges>

CRONZ_BEGIN_URI_NAMESPACE
    // Properties.
    inline std::size_t QueryManager::count(const bool unique) const noexcept {
        if (unique)
            return _fields.size();

        auto c = static_cast<std::size_t>(0);
        for (const ImmutableQueryField *field: _fields) {
            if (field->isArray())
                c += field->size();
        }

        return c;
    }

    inline std::size_t QueryManager::length() const noexcept {
        if (empty())
            return static_cast<std::size_t>(0);

        std::size_t l = count(true) - static_cast<std::size_t>(1);

        for (const ImmutableQueryField *field: _fields)
            l += field->length();

        return l;
    }

    inline bool QueryManager::empty() const noexcept {
        return _fields.empty();
    }

    // Fields.
    inline bool QueryManager::contains(const std::string_view name) const {
        return std::ranges::any_of(_fields, [&name](const ImmutableQueryField *field) noexcept -> bool {
            return field->_cn(name);
        });
    }

    inline ImmutableQueryField *QueryManager::get(const std::string_view name) const noexcept {
        for (ImmutableQueryField *field: _fields) {
            if (field->_cn(name))
                return field;
        }

        return nullptr;
    }

    inline ImmutableQueryField *QueryManager::create(const std::string_view name) noexcept {
        if (ImmutableQueryField *field = get(name);
            nullptr != field)
            return field;

        try {
            auto field = new(std::nothrow) ImmutableQueryField(name);
            if (nullptr == field)
                return nullptr;

            return _fields.emplace_back(field);
        } catch (...) {
            return nullptr;
        }
    }

    template<bool Renamable>
    inline ImmutableQueryField *QueryManager::create(const QueryField<Renamable> &field) noexcept {
        ImmutableQueryField *f = get(field.name());
        if (nullptr != f) {
            try {
                f->_values.assign(field._values);
                return f;
            } catch (...) {
                return nullptr;
            }
        }

        try {
            f = new(std::nothrow) ImmutableQueryField(field._name);
            if (nullptr == f)
                return nullptr;

            f->_values.assign(field._values);

            _fields.emplace_back(f);

            return f;
        } catch (...) {
            delete f;
            return nullptr;
        }
    }

    inline bool QueryManager::remove(const std::string_view name) noexcept {
        for (auto it = _fields.cbegin(); it != _fields.cend(); ++it) {
            if ((*it)->_cn(name)) {
                _fields.erase(it);
                return true;
            }
        }

        return false;
    }

    inline bool QueryManager::remove(const ImmutableQueryField *field) noexcept {
        if (nullptr == field)
            return false;

        for (auto it = _fields.cbegin(); it != _fields.cend(); ++it) {
            if ((*it) == field) {
                delete field;
                _fields.erase(it);
                return true;
            }
        }

        return false;
    }

    template<typename IteratorType>
        requires (std::is_same_v<IteratorType, QueryManager::Iterator> || std::is_same_v<IteratorType,
                      QueryManager::ConstIterator>)
    inline constexpr IteratorType QueryManager::remove(IteratorType position) noexcept {
        if (_fields.begin() > position || _fields.end() <= position)
            return _fields.end();

        return _fields.erase(position);
    }

    // Parsing & Stringification.
    inline bool QueryManager::parse(const std::string_view str) noexcept {
        std::unordered_map<std::string, ImmutableQueryField *> fields;
        std::vector<ImmutableQueryField *> _f{};

        const char *const beg = str.cbegin();
        const char *const end = str.cend();

        const char *pos = beg;
        while (pos < end) {
            const char *const amp = std::ranges::find(pos, end, '&');
            if (static_cast<std::size_t>(0) != static_cast<std::size_t>(std::distance(pos, amp))) {
                std::string name;
                std::string value;

                if (!_split(pos, amp, name, value))
                    goto parse_error;

                if (const auto it = fields.find(name);
                    fields.end() == it) {
                    auto field = new(std::nothrow) ImmutableQueryField;
                    if (nullptr == field)
                        goto parse_error;

                    try {
                        fields.emplace(name, field);

                        field->_name.swap(name);
                        field->_values.push_back(std::move(value));
                    } catch (...) {
                        delete field;
                        goto parse_error;
                    }
                } else {
                    ImmutableQueryField *field = it->second;
                    if (nullptr == field)
                        goto parse_error;

                    try {
                        field->_values.push_back(std::move(value));
                    } catch (...) {
                        goto parse_error;
                    }
                }
            }

            pos = amp + static_cast<std::ptrdiff_t>(1);
        }

        try {
            _f.reserve(fields.size());
        } catch (...) {
            goto parse_error;
        }

        for (ImmutableQueryField *field: fields | std::views::values)
            _f.emplace_back(field);

        _f.swap(_fields);

        for (const ImmutableQueryField *field: _f)
            delete field;

        return true;

    parse_error:
        for (const ImmutableQueryField *field: fields | std::views::values)
            delete field;

        return false;
    }

    inline std::string QueryManager::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            return {};

        return str;
    }

    inline bool QueryManager::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool QueryManager::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        bool first = true;
        for (const ImmutableQueryField *field: _fields) {
            if (!first)
                str[offset++] = '&';

            if (!field->stringify(str, offset))
                return false;

            first = false;
        }

        return true;
    }

    // Iterators.
    inline constexpr QueryManager::Iterator QueryManager::begin() noexcept {
        return _fields.begin();
    }

    inline constexpr QueryManager::ConstIterator QueryManager::begin() const noexcept {
        return _fields.cbegin();
    }

    inline constexpr QueryManager::Iterator QueryManager::end() noexcept {
        return _fields.end();
    }

    inline constexpr QueryManager::ConstIterator QueryManager::end() const noexcept {
        return _fields.cend();
    }

    inline constexpr QueryManager::ConstIterator QueryManager::cbegin() const noexcept {
        return _fields.cbegin();
    }

    inline constexpr QueryManager::ConstIterator QueryManager::cend() const noexcept {
        return _fields.cend();
    }

    inline constexpr QueryManager::ReverseIterator QueryManager::rbegin() noexcept {
        return _fields.rbegin();
    }

    inline constexpr QueryManager::ReverseIterator QueryManager::rend() noexcept {
        return _fields.rend();
    }

    inline constexpr QueryManager::ConstReverseIterator QueryManager::crbegin() const noexcept {
        return _fields.crbegin();
    }

    inline constexpr QueryManager::ConstReverseIterator QueryManager::crend() const noexcept {
        return _fields.crend();
    }

    // Operators.
    inline QueryManager::operator bool() const noexcept {
        return !empty();
    }

    inline ImmutableQueryField *QueryManager::operator[](const std::string_view name) const noexcept {
        return get(name);
    }

    // Static utility functions.
    inline bool QueryManager::_split(const char *beg, const char *end, std::string &name, std::string &value) noexcept {
        const char *const eq = std::ranges::find(beg, end, '=');

        try {
            name.assign(beg, eq);

            if (eq != end)
                value.assign(eq + static_cast<std::ptrdiff_t>(1), end);
        } catch (...) {
            return false;
        }

        const bool array = (static_cast<std::size_t>(2) < name.length() &&
                            '[' == name[name.length() - static_cast<std::size_t>(2)] &&
                            ']' == name[name.length() - static_cast<std::size_t>(1)]);
        if (array) {
            name.pop_back();
            name.pop_back();
        }

        return URIDecodeComponentInPlace(name) && URIDecodeComponentInPlace(value);
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_QUERY_IMPL_MANAGER_IPP
