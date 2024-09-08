/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_QUERY_IMPL_MANAGER_IPP
#define CRONZ_URL_QUERY_IMPL_MANAGER_IPP 1

#include "cronz/url/query/manager.hpp"

#include <algorithm>
#include <set>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline QueryManager::QueryManager() noexcept = default;

    // Query fields.
    inline bool QueryManager::contains(const std::string &name) const noexcept {
        return std::ranges::any_of(fields_, [&name](const QueryField<false> &field) -> bool {
            return name == field.name_;
        });
    }

    inline QueryManager::QueryFieldType* QueryManager::get(const std::string &name) noexcept {
        for (auto &field : fields_) {
            if (name == field.name_)
                return &field;
        }

        return nullptr;
    }

    inline QueryManager::QueryFieldType* QueryManager::create(const std::string &name) noexcept {
        QueryFieldType *field = get(name);
        if (nullptr == field) {
            try {
                QueryFieldType &ref = fields_.emplace_back(name);
                field = &ref;
            }
            catch (...) {
            }
        }

        return field;
    }

    inline bool QueryManager::remove(const std::string &name) noexcept {
        for (auto it = fields_.begin(); it != fields_.end(); ++it) {
            if (name == it->name_) {
                fields_.erase(it);
                return true;
            }
        }

        return false;
    }

    inline bool QueryManager::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline bool QueryManager::parse(const char *str, const std::size_t &length) noexcept {
        ArrayType tempFields;
        try {
            tempFields.assign(fields_.begin(), fields_.end());
        }
        catch (...) {
            return false;
        }

        std::set<std::string> arrayMarkings;

        const char *const end = str + length;
        const char *previous = str;
        while (previous < end) {
            const char *fieldSeparator = std::ranges::find(previous, end, '&');

            const char *valueSeparator = std::ranges::find(previous, fieldSeparator, '=');
            const std::size_t valueLength = ((valueSeparator == fieldSeparator)
                                                 ? static_cast<std::size_t>(0)
                                                 : (fieldSeparator - valueSeparator - static_cast<std::size_t>(1)));

            std::size_t nameLength = valueSeparator - previous;
            const bool isArray = (static_cast<std::size_t>(2) <= nameLength && '[' == previous[nameLength - static_cast<
                std::size_t>(2)] && ']' == previous[nameLength - static_cast<std::size_t>(1)]);
            if (isArray)
                nameLength -= static_cast<std::size_t>(2);

            std::string fieldName;
            std::string fieldValue;
            if (!Decode(previous, nameLength, fieldName) ||
                !Decode(&valueSeparator[1], valueLength, fieldValue))
                goto bad;

            if (QueryFieldType *field = get(fieldName); nullptr != field) {
                const bool isMarkedAsArray = arrayMarkings.contains(fieldName);

                if (isArray) {
                    if (!isMarkedAsArray && !field->isArray()) {
                        try {
                            arrayMarkings.insert(fieldName);
                        }
                        catch (...) {
                            goto bad;
                        }

                        field->value_.swap(fieldValue);
                    }
                    else {
                        if (!field->addValue(fieldValue))
                            goto bad;
                    }
                }
                else {
                    if (isMarkedAsArray)
                        arrayMarkings.erase(fieldName);

                    if (field->isArray())
                        field->clearValues();

                    field->value_.swap(fieldValue);
                }
            }
            else {
                field = create(fieldName);
                if (nullptr == field)
                    goto bad;

                field->value_.swap(fieldValue);

                if (isArray) {
                    try {
                        arrayMarkings.insert(fieldName);
                    }
                    catch (...) {
                        goto bad;
                    }
                }
            }

            previous = fieldSeparator + static_cast<std::size_t>(1);
        }

        return true;

    bad:
        fields_.swap(tempFields);
        return false;
    }

    inline void QueryManager::clear() noexcept {
        fields_.clear();
    }

    // Properties.
    inline std::size_t QueryManager::length() const noexcept {
        if (empty())
            return static_cast<std::size_t>(0);

        std::size_t l = fields_.size() - static_cast<std::size_t>(1);

        for (const QueryFieldType &field : fields_)
            l += field.length();

        return l;
    }

    inline bool QueryManager::empty() const noexcept {
        return fields_.empty();
    }

    // Conversion.
    inline std::string QueryManager::stringify() const noexcept {
        std::string str;
        [[maybe_unused]] const bool _ = stringify(str);
        return str;
    }

    inline bool QueryManager::stringify(std::string &str) const noexcept {
        str.clear();
        return stringify(str, static_cast<std::size_t>(0));
    }

    inline bool QueryManager::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (const std::size_t len = (offset + length()); len > str.length()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        printf("qm => %llu => %c\n", offset, str[offset]);
        std::size_t o = offset;
        for (const QueryFieldType &field : fields_) {
            if (o != offset)
                str[o++] = '&';

            if (!field.stringify(str, o))
                return false;

            o += field.length();
        }

        return true;
    }

    // Operators.
    inline QueryManager::operator bool() const noexcept {
        return !empty();
    }

    // Iterators.
    inline QueryManager::Iterator QueryManager::begin() noexcept {
        return fields_.begin();
    }

    inline QueryManager::Iterator QueryManager::end() noexcept {
        return fields_.end();
    }

    inline QueryManager::ConstIterator QueryManager::cbegin() const noexcept {
        return fields_.cbegin();
    }

    inline QueryManager::ConstIterator QueryManager::cend() const noexcept {
        return fields_.cend();
    }

    inline QueryManager::ReverseIterator QueryManager::rbegin() noexcept {
        return fields_.rbegin();
    }

    inline QueryManager::ReverseIterator QueryManager::rend() noexcept {
        return fields_.rend();
    }

    inline QueryManager::ConstReverseIterator QueryManager::crbegin() const noexcept {
        return fields_.crbegin();
    }

    inline QueryManager::ConstReverseIterator QueryManager::crend() const noexcept {
        return fields_.crend();
    }

    // Destructors.
    inline QueryManager::~QueryManager() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_QUERY_IMPL_MANAGER_IPP
