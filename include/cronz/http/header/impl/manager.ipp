/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_HEADER_IMPL_MANAGER_IPP
#define CRONZ_HTTP_HEADER_IMPL_MANAGER_IPP 1

#include "cronz/http/header/manager.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline std::size_t HeaderManager::count() const noexcept {
        return _fields.size();
    }

    inline bool HeaderManager::empty() const noexcept {
        return _fields.empty();
    }

    inline std::size_t HeaderManager::length() const noexcept {
        std::size_t len = count() * static_cast<std::size_t>(2);
        for (const HeaderField *field: _fields) {
            if (!field->empty())
                len += field->length();
            else
                len -= static_cast<std::size_t>(2);
        }

        return len;
    }

    // Fields.
    inline HeaderField *HeaderManager::_get(const std::string_view name, const HeaderField *after) const noexcept {
        bool _after = (nullptr == after);
        for (HeaderField *field: _fields) {
            if (_after) {
                if (field->_cn(name))
                    return field;

                continue;
            }

            if (field == after)
                _after = true;
        }

        return nullptr;
    }

    inline bool HeaderManager::contains(std::string_view name) const noexcept {
        return std::ranges::any_of(_fields, [&name](const HeaderField *field) noexcept -> bool {
            return field->_cn(name);
        });
    }

    inline std::size_t HeaderManager::count(std::string_view name) const noexcept {
        return std::ranges::count_if(_fields, [&name](const HeaderField *field) noexcept -> bool {
            return field->_cn(name);
        });
    }

    inline HeaderField *HeaderManager::get(const std::string_view name, const HeaderField *after) noexcept {
        return _get(name, after);
    }

    inline const HeaderField *HeaderManager::get(const std::string_view name, const HeaderField *after) const noexcept {
        return _get(name, after);
    }

    inline HeaderField *HeaderManager::create(const std::string_view name) noexcept {
        return create(name, std::string_view());
    }

    inline HeaderField *HeaderManager::create(const std::string_view name, const std::string_view value) noexcept {
        if (!RFC::IsHeaderFieldName(name) || !RFC::IsHeaderFieldValue(value))
            return nullptr;

        const auto field = new(std::nothrow) HeaderField;
        if (nullptr == field)
            return nullptr;

        try {
            field->_name.assign(name);
            field->_value.assign(value);

            _fields.push_back(field);

            return field;
        } catch (...) {
            delete field;
            return nullptr;
        }
    }

    inline HeaderField *HeaderManager::create(const HeaderField &field) noexcept {
        return create(field._name, field._value);
    }

    inline bool HeaderManager::remove(const std::string_view name) noexcept {
        bool _r = false;
        for (auto it = _fields.begin(); it != _fields.end();) {
            if ((*it)->_cn(name)) {
                delete (*it);
                it = _fields.erase(it);
                _r = true;
            } else {
                ++it;
            }
        }

        return _r;
    }

    inline bool HeaderManager::remove(const HeaderField *field) noexcept {
        for (auto it = _fields.begin(); it != _fields.end(); ++it) {
            if ((*it) == field) {
                delete (*it);
                _fields.erase(it);

                return true;
            }
        }

        return false;
    }

    inline void HeaderManager::remove(const std::function<bool(HeaderField *field)> &fun) noexcept {
        for (auto it = _fields.begin(); it != _fields.end();) {
            if (HeaderField *field = *it;
                fun(field)) {
                delete field;
                it = _fields.erase(it);
            } else {
                ++it;
            }
        }
    }

    template<typename IteratorType>
        requires (std::is_same_v<IteratorType, HeaderManager::Iterator> || std::is_same_v<IteratorType,
                      HeaderManager::ConstIterator>)
    inline IteratorType HeaderManager::remove(IteratorType iterator) noexcept {
        if (iterator < begin() || iterator >= end())
            return end();

        return _fields.erase(iterator);
    }

    template<typename ReturnType>
        requires (std::is_same_v<ReturnType, void> || std::is_convertible_v<ReturnType, bool>)
    inline void HeaderManager::forEach(const std::function<ReturnType(HeaderField *field)> &fun) const noexcept {
        for (HeaderField *field: _fields) {
            if constexpr (std::is_same_v<ReturnType, void>)
                fun(field);
            else if (!fun(field))
                break;
        }
    }

    template<typename ReturnType>
        requires (std::is_same_v<ReturnType, void> || std::is_convertible_v<ReturnType, bool>)
    inline void HeaderManager::forEach(const std::string_view name,
                                       const std::function<ReturnType(HeaderField *field)> &fun) const noexcept {
        for (HeaderField *field: _fields) {
            if (field->_cn(name)) {
                if constexpr (std::is_same_v<ReturnType, void>)
                    fun(field);
                else if (!fun(field))
                    break;
            }
        }
    }

    // Parsing & Stringification.
    inline bool HeaderManager::parse(const std::string_view headers) noexcept {
        clear();

        const char *const beg = headers.cbegin();
        const char *const end = headers.cend();

        const char *pos = beg;
        while (pos < end) {
            const char *const cr = std::ranges::find(pos, end, '\r');
            if (cr == end)
                return false;

            const char *const lf = std::ranges::find(pos, end, '\n');
            if (lf == end)
                return false;

            if (lf != std::next(cr))
                return false;

            auto field = new(std::nothrow) HeaderField;
            if (!field->parse(std::string_view(pos, cr)))
                goto parse_error;

            try {
                _fields.push_back(field);
            } catch (...) {
                delete field;
                goto parse_error;
            }

            pos = std::next(lf);
        }

        return true;

    parse_error:
        clear();
        return false;
    }

    inline std::string HeaderManager::stringify() const noexcept {
        if (std::string str;
            stringify(str))
            return str;

        return {};
    }

    inline bool HeaderManager::stringify(std::string &str) const noexcept {
        str.clear();

        if (auto offset = static_cast<std::size_t>(0);
            stringify(str, offset))
            return true;

        str.clear();
        return false;
    }

    inline bool HeaderManager::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        for (const HeaderField *field: _fields) {
            if (!field->empty() && !field->stringify(str, offset))
                return false;

            str[offset++] = '\r';
            str[offset++] = '\n';
        }

        return true;
    }

    // Instance-based utility functions.
    inline void HeaderManager::clear() noexcept {
        for (const HeaderField *field: _fields)
            delete field;

        _fields.clear();
    }

    // Iterators.
    inline constexpr HeaderManager::Iterator HeaderManager::begin() noexcept {
        return _fields.begin();
    }

    inline constexpr HeaderManager::ConstIterator HeaderManager::begin() const noexcept {
        return _fields.cbegin();
    }

    inline constexpr HeaderManager::Iterator HeaderManager::end() noexcept {
        return _fields.end();
    }

    inline constexpr HeaderManager::ConstIterator HeaderManager::end() const noexcept {
        return _fields.cend();
    }

    inline constexpr HeaderManager::ConstIterator HeaderManager::cbegin() const noexcept {
        return _fields.cbegin();
    }

    inline constexpr HeaderManager::ConstIterator HeaderManager::cend() const noexcept {
        return _fields.cend();
    }

    inline constexpr HeaderManager::ReverseIterator HeaderManager::rbegin() noexcept {
        return _fields.rbegin();
    }

    inline constexpr HeaderManager::ReverseIterator HeaderManager::rend() noexcept {
        return _fields.rend();
    }

    inline constexpr HeaderManager::ConstReverseIterator HeaderManager::crbegin() const noexcept {
        return _fields.crbegin();
    }

    inline constexpr HeaderManager::ConstReverseIterator HeaderManager::crend() const noexcept {
        return _fields.crend();
    }

    // Operators.
    inline HeaderManager::operator bool() const noexcept {
        return !empty();
    }

    // Destructor.
    inline HeaderManager::~HeaderManager() noexcept {
        clear();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_HEADER_IMPL_MANAGER_IPP
