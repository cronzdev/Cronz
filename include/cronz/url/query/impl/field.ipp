/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_QUERY_IMPL_FIELD_IPP
#define CRONZ_URL_QUERY_IMPL_FIELD_IPP 1

#include <charconv>
#include <utility>

#include "cronz/url/query/field.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    template <bool Renamable>
    inline QueryField<Renamable>::QueryField() noexcept requires Renamable = default;

    template <bool Renamable>
    inline QueryField<Renamable>::QueryField(std::string name) : name_(std::move(name)) {
    }

    // Name.
    template <bool Renamable>
    inline std::string& QueryField<Renamable>::name() noexcept requires Renamable {
        return name_;
    }

    template <bool Renamable>
    inline const std::string& QueryField<Renamable>::name() const noexcept {
        return name_;
    }

    template <bool Renamable>
    inline const std::string& QueryField<Renamable>::getName() const noexcept {
        return name();
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::setName(const std::string &name) noexcept requires Renamable {
        try {
            name_.assign(name);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    // Value.
    template <bool Renamable>
    inline const std::string& QueryField<Renamable>::value() const noexcept {
        return value_;
    }

    template <bool Renamable>
    inline const std::string& QueryField<Renamable>::getValue() const noexcept {
        return value();
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::getValueAt(const std::size_t &position, std::string &value) const noexcept {
        std::size_t length;
        const char *first;
        getValueAt(position, first, length);
        if (nullptr == first)
            return false;

        try {
            value.resize(length);
        }
        catch (...) {
            return false;
        }

        memcpy(value.data(), first, length);
        return true;
    }

    template <bool Renamable>
    inline std::string QueryField<Renamable>::getValueAt(const std::size_t &position) const noexcept {
        std::string v;
        [[maybe_unused]] const bool _ = getValueAt(position, v);
        return v;
    }

    template <bool Renamable>
    void QueryField<Renamable>::getValueAt(const std::size_t &position, const char *&value,
                                           std::size_t &length) const noexcept {
        if (position >= indices_.size()) {
            value = nullptr;
            length = static_cast<std::size_t>(0);
            return;
        }

        value = &value_[indices_[position]];
        length = ((indices_.size() == (position + static_cast<std::size_t>(1)))
                      ? value_.length()
                      : indices_[position + static_cast<std::size_t>(1)] - static_cast<std::size_t>(1)) - indices_[
            position];
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::splitValues(std::vector<std::string> &values) const noexcept {
        values.clear();

        try {
            values.resize(indices_.size());
        }
        catch (...) {
            return false;
        }

        for (auto i = static_cast<std::size_t>(0); i < size(); ++i) {
            if (!getValueAt(i, values[i])) {
                values.clear();
                return false;
            }
        }

        return true;
    }

    template <bool Renamable>
    inline std::vector<std::string> QueryField<Renamable>::splitValues() const noexcept {
        std::vector<std::string> values;
        [[maybe_unused]] const bool _ = splitValues(values);
        return values;
    }

    template <bool Renamable>
    template <typename StringifiableType>
    inline bool QueryField<Renamable>::addValue(const StringifiableType &value) noexcept {
        if constexpr (std::is_same_v<std::string, StringifiableType>) {
            auto state = static_cast<std::uint8_t>(0);

            try {
                indices_.push_back(value_.length() + static_cast<std::size_t>(1));
                state = static_cast<std::uint8_t>(1);

                value_.push_back(',');
                state = static_cast<std::uint8_t>(2);

                value_.append(value);
                return true;
            }
            catch (...) {
            }

            if (static_cast<std::uint8_t>(1) <= state)
                indices_.pop_back();

            if (static_cast<std::uint8_t>(2) <= state)
                value_.pop_back();

            return false;
        }
        else {
            std::string v_;
            return stringify_(value, v_) && addValue(v_);
        }
    }

    template <bool Renamable>
    template <typename StringifiableType>
    inline bool QueryField<Renamable>::setValue(const StringifiableType &value) noexcept {
        if constexpr (std::is_same_v<std::string, StringifiableType>) {
            try {
                value_.assign(value);
            }
            catch (...) {
                return false;
            }

            while (static_cast<std::size_t>(1) < indices_.size())
                indices_.pop_back();

            return true;
        }
        else {
            std::string v_;
            return stringify_(value, v_) && setValue(v_);
        }
    }

    template <bool Renamable>
    template <typename StringifiableType>
    inline bool QueryField<
        Renamable>::setValueAt(const std::size_t &position, const StringifiableType &value) noexcept {
        if constexpr (std::is_same_v<std::string, StringifiableType>) {
            if (position >= indices_.size())
                return addValue(value);

            std::pair<std::size_t, std::size_t> sequence;
            sequence.first = indices_[position];
            sequence.second = ((indices_.size() == (position + static_cast<std::size_t>(1)))
                                   ? value_.length()
                                   : indices_[position + static_cast<std::size_t>(1)]) - sequence.first;

            if (indices_.size() != (position + static_cast<std::size_t>(1)))
                --sequence.second;

            try {
                value_.replace(sequence.first, sequence.second, value);
            }
            catch (...) {
                return false;
            }

            if (sequence.second == value.length())
                return true;

            auto it = indices_.begin();
            std::advance(it, position + static_cast<std::size_t>(1));

            if (value.length() > sequence.second) {
                sequence.first = value.length() - sequence.second;

                while (it != indices_.end()) {
                    (*it) += sequence.first;
                    std::advance(it, static_cast<std::size_t>(1));
                }
            }
            else {
                sequence.first = sequence.second - value.length();

                while (it != indices_.end()) {
                    (*it) -= sequence.first;
                    std::advance(it, static_cast<std::size_t>(1));
                }
            }

            return true;
        }
        else {
            std::string v_;
            return stringify_(value, v_) && setValueAt(position, v_);
        }
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::removeValueAt(const std::size_t &position) noexcept {
        if (position >= indices_.size())
            return false;

        if (!isArray()) {
            clearValues();
            return true;
        }

        std::pair<std::size_t, std::size_t> sequence;
        sequence.first = indices_[position];
        sequence.second = ((indices_.size() == (position + static_cast<std::size_t>(1)))
                               ? value_.length()
                               : indices_[position + static_cast<std::size_t>(1)]) - sequence.first;

        try {
            value_.erase(sequence.first, sequence.second);
        }
        catch (...) {
            return false;
        }

        auto indexIt = indices_.begin();
        std::advance(indexIt, position);
        indexIt = indices_.erase(indexIt);

        while (indexIt != indices_.end()) {
            (*indexIt) -= sequence.second;
            std::advance(indexIt, static_cast<std::size_t>(1));
        }

        return true;
    }

    template <bool Renamable>
    inline void QueryField<Renamable>::clearValues() noexcept {
        value_.clear();

        while (static_cast<std::size_t>(1) < indices_.size())
            indices_.pop_back();
    }

    // Properties
    template <bool Renamable>
    template <typename StringifiableType>
    inline bool QueryField<Renamable>::stringify_(const StringifiableType &value, std::string &str) noexcept {
        if constexpr (std::is_integral_v<StringifiableType> || std::is_floating_point_v<StringifiableType>) {
            try {
                str = std::to_string(value);
                return true;
            }
            catch (...) {
                return false;
            }
        }
        else {
            try {
                str.assign(value);
                return true;
            }
            catch (...) {
                return false;
            }
        }
    }

    template <bool Renamable>
    inline const std::vector<std::size_t>& QueryField<Renamable>::indices() const noexcept {
        return indices_;
    }

    template <bool Renamable>
    inline const std::vector<std::size_t>& QueryField<Renamable>::getIndices() const noexcept {
        return indices_;
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::isArray() const noexcept {
        return static_cast<std::size_t>(1) < size();
    }

    template <bool Renamable>
    inline std::size_t QueryField<Renamable>::count() const noexcept {
        return size();
    }

    template <bool Renamable>
    inline std::size_t QueryField<Renamable>::size() const noexcept {
        return indices_.size();
    }

    template <bool Renamable>
    inline std::size_t QueryField<Renamable>::length() const noexcept {
        if (isArray()) {
            std::size_t l = CalculateEncodedLength(name_);
            l += count() * static_cast<std::size_t>(4) - static_cast<std::size_t>(1);

            std::size_t valueLength;
            const char *value;
            for (auto i = static_cast<std::size_t>(0); i < indices_.size(); ++i) {
                getValueAt(i, value, valueLength);
                l += CalculateEncodedLength(value, valueLength);
            }

            return l;
        }
        else {
            return CalculateEncodedLength(name_) + CalculateEncodedLength(value_) + static_cast<std::size_t>(1);
        }
    }

    template <bool Renamable>
    inline void QueryField<Renamable>::clear() noexcept {
        if constexpr (Renamable)
            name_.clear();

        clearValues();
    }

    // Conversion.
    template <bool Renamable>
    inline std::string QueryField<Renamable>::stringify() const noexcept {
        std::string str;
        [[maybe_unused]] const bool _ = stringify(str, static_cast<std::size_t>(0));
        return str;
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::stringify(std::string &str) const noexcept {
        return stringify(str, static_cast<std::size_t>(0));
    }

    template <bool Renamable>
    inline bool QueryField<Renamable>::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (const std::size_t len = offset + length(); str.length() < len) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        if (isArray()) {
            std::string encodedName;
            if (!Encode(name_.c_str(), name_.length(), encodedName))
                return false;

            try {
                encodedName.append("[]");
            }
            catch (...) {
                return false;
            }

            std::size_t o = offset;
            for (auto i = static_cast<std::size_t>(0); i < indices_.size(); ++i) {
                if (static_cast<std::size_t>(0) != i)
                    str[o++] = '&';

                memcpy(&str[o], encodedName.c_str(), encodedName.length());
                o += encodedName.length();
                str[o++] = '=';

                const char *value;
                std::size_t valueLength;
                getValueAt(i, value, valueLength);

                o += Encode(value, valueLength, &str[o]);
            }
        }
        else {
            std::size_t o = offset;
            o += Encode(name_.c_str(), name_.length(), &str[o]);
            str[o++] = '=';
            o += Encode(value_.c_str(), value_.length(), &str[o]);
        }

        return true;
    }

    // Destructors.
    template <bool Renamable>
    inline QueryField<Renamable>::~QueryField() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_QUERY_IMPL_FIELD_IPP
