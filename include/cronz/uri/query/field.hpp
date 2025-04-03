/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_QUERY_FIELD_HPP
#define CRONZ_URI_QUERY_FIELD_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief Query field.
     * @class QueryField
     * @tparam Renamable Whether the field name is renamable or not.
     * @remark This class is used to represent a query field in a URI. It can be used to parse and stringify
     * query strings.
     */
    template<bool Renamable = true>
    class QueryField final {
        // Properties.
        std::string _name{};
        std::vector<std::string> _values{};

        template<typename StringifiableType>
        CRONZ_NODISCARD_L1 static bool _stringify(StringifiableType value, std::string &str) noexcept;

        CRONZ_NODISCARD_L1 bool _cn(std::string_view name) const noexcept;

        // Friends.
        friend class QueryManager;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        QueryField() noexcept = default;

        /**
         * @brief Constructor with name.
         * @param[in] name Field name.
         * @remark Name will be directly assigned to the field. No URI-decoding will be performed.
         */
        explicit(true) QueryField(std::string_view name) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Get field name.
         * @return Field name.
         * @remark Returned name is not URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::string_view name() const noexcept;

        /**
         * @brief Returns a read-only reference to the field name.
         * @return Read-only reference to the field name.
         * @remark This function is only available if `Renamable` is `true`.
         * @remark Name can be directly modified.
         */
        CRONZ_NODISCARD_L1 std::string &name() noexcept requires Renamable;

        /**
         * @brief Updates the field's name.
         * @param[in] name New name.
         * @return `true` if name is successfully assigned.
         * @return `false` if name is not successfully assigned.
         * @remark This function is only available if `Renamable` is `true`.
         */
        CRONZ_NODISCARD_L2 bool name(std::string_view name) noexcept requires Renamable;

        /**
         * @brief Returns a read-only reference to the field value.
         * @return Read-only reference to the field value.
         * @remark This will return a single, decoded value. In case of an array field, separations might not be
         * determinate. Use `getValueAt` instead to get value at a specific position.
         */
        CRONZ_NODISCARD_L1 const std::string &value() const noexcept;

        /**
         * @brief Returns a reference to the field values.
         * @return Reference to the field values.
         */
        CRONZ_NODISCARD_L1 std::vector<std::string> &values() noexcept;

        /**
         * @brief Returns a read-only reference to the field values.
         * @return Read-only reference to the field values.
         */
        CRONZ_NODISCARD_L1 const std::vector<std::string> &values() const noexcept;

        /**
         * @brief Returns a reference to the field value at the given position.
         * @param[in] position Position of the value.
         * @return Reference to the field value at the given position.
         */
        CRONZ_NODISCARD_L1 constexpr std::string &at(std::size_t position) noexcept;

        /**
         * @brief Returns a read-only reference to the field value at the given position.
         * @param[in] position Position of the value.
         * @return Read-only reference to the field value at the given position.
         */
        CRONZ_NODISCARD_L1 constexpr const std::string &at(std::size_t position) const noexcept;

        /**
         * @brief Tells whether the current field is an array.
         * @return `true` if the current field is an array.
         * @return `false` if the current field is not an array.
         */
        CRONZ_NODISCARD_L1 bool isArray() const noexcept;

        /**
         * @brief Returns the number of values in the field.
         * @return Number of values in the field.
         */
        CRONZ_NODISCARD_L1 std::size_t size() const noexcept;

        /**
         * @brief Tells whether the current field is empty.
         * @return `true` if the current field is empty.
         * @return `false` if the current field is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Returns the length of the field when stringified.
         * @return Length of the field when stringified.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Stringification.
         */
        /** @{ */
        /**
         * @brief Stringifies the current field.
         * @return Stringified version of the current field.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the current field.
         * @param[in] str String to append to.
         * @return `true` if the field is successfully stringified.
         * @return `false` if the field could not be stringified.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the current field.
         * @param[in] str String to append to.
         * @param[in] offset Offset to start appending to.
         * @return `true` if the field is successfully stringified.
         * @return `false` if the field could not be stringified.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Returns a reference to the field value at the given position.
         * @param[in] position Position of the value.
         * @return Reference to the field value at the given position.
         */
        CRONZ_NODISCARD_L1 constexpr std::string &operator[](std::size_t position) noexcept;

        /**
         * @brief Returns a read-only reference to the field value at the given position.
         * @param[in] position Position of the value.
         * @return Read-only reference to the field value at the given position.
         */
        CRONZ_NODISCARD_L1 constexpr const std::string &operator[](std::size_t position) const noexcept;

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~QueryField() noexcept = default;

        /** @} */
    };

    /**
     * @name Type Aliases.
     */
    /** @{ */
    /**
     * @ingroup cronz_uri
     * @brief Immutable query field.
     * @remark This type is used to represent a query field that cannot be modified.
     */
    using ImmutableQueryField = QueryField<false>;

    /**
     * @ingroup cronz_uri
     * @brief Mutable query field.
     * @remark This type is used to represent a query field that can be modified.
     */
    using MutableQueryField = QueryField<true>;

    /** @} */

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/query/impl/field.ipp"

#endif // CRONZ_URI_QUERY_FIELD_HPP
