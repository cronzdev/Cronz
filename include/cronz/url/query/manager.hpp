/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_QUERY_MANAGER_HPP
#define CRONZ_URL_QUERY_MANAGER_HPP 1

#include "cronz/url/query/field.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @brief Query field manager.
     * @class QueryManager
     * @ingroup cronz_url_query
     */
    class QueryManager {
        // Properties.
        using QueryFieldType = QueryField<false>;

        using ArrayType = std::vector<QueryFieldType>;
        ArrayType fields_;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @remark Does nothing.
         */
        QueryManager() noexcept;

        /** @} */

        /**
         * @name Query fields.
         */
        /** @{ */
        /**
         * @brief Tells whether a query field with the given name exists.
         * @param[in] name Field name.
         * @return `true` if a field with the given name exists, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool contains(const std::string &name) const noexcept;

        /**
         * @brief Returns reference to the field with the given name.
         * @param[in] name Name of the field.
         * @return If found, reference to the field with the given name, and if not, `nullptr`.
         * @sa create
         * @sa remove
         * @sa parse
         * @sa clear
         */
        CRONZ_NODISCARD_L1 QueryFieldType* get(const std::string &name) noexcept;

        /**
         * @brief Creates a field with the given name and returns reference to it.
         * @param[in] name Name of the field.
         * @return If created or found, reference to the field with the given name, and if not, `nullptr`.
         * @remark If a field with the given name already exists, this function works identical to `get`.
         * @sa get
         * @sa remove
         * @sa parse
         * @sa clear
         */
        CRONZ_NODISCARD_L1 QueryFieldType* create(const std::string &name) noexcept;

        /**
         * @brief Removes the field with the given name.
         * @param[in] name Name of the field to be removed.
         * @return `true` if a field with the given name was found and removed, otherwise, `false`.
         * @sa get
         * @sa create
         * @sa parse
         * @sa clear
         */
        CRONZ_NODISCARD_L2 bool remove(const std::string &name) noexcept;

        /**
         * @brief Parses a query string.
         * @param[in] str Query string to be parsed.
         * @return `true` if `str` is successfully parsed, otherwise, `false`.
         * @remark Upon failure, existing data is not altered. The only failure reason is failing to allocate memory.
         * @remark A field cannot be assigned with a single value and an array value at the same time. The rules are as
         * follows:
         * - Array fields must have `[]` appended in their names.
         * - If a field is not interpreted as an array, but exists and `isArray` returns `true`, the field is converted
         * to a single-value field.
         * - If a field is interpreted as an array, independently of its pre-existence status:
         *  - If it is encountered for the first time, it is marked as an array and the value is appended to the field,
         *  converting it into an array field if it was not before.
         *  - If it was encountered before but was interpreted as a non-array value, the field is cleared first,
         *  converted to an array field, and the value is assigned as the first element of the array.
         * @remark All the field names and values are assumed to be encoded.
         * @remark This function does not remove the existing fields.
         * @sa get
         * @sa create
         * @sa remove
         * @sa clear
         */
        CRONZ_NODISCARD_L1 bool parse(const std::string &str) noexcept;

        /**
         * @brief Parses a query string.
         * @param[in] str Query string to be parsed.
         * @param[in] length Length of the query string to be parsed.
         * @return `true` if `str` is successfully parsed, otherwise, `false`.
         * @remark Upon failure, existing data is not altered. The only failure reason is failing to allocate memory.
         * @remark A field cannot be assigned with a single value and an array value at the same time. The rules are as
         * follows:
         * - Array fields must have `[]` appended in their names.
         * - If a field is not interpreted as an array, but exists and `isArray` returns `true`, the field is converted
         * to a single-value field.
         * - If a field is interpreted as an array, independently of its pre-existence status:
         *  - If it is encountered for the first time, it is marked as an array and the value is appended to the field,
         *  converting it into an array field if it was not before.
         *  - If it was encountered before but was interpreted as a non-array value, the field is cleared first,
         *  converted to an array field, and the value is assigned as the first element of the array.
         * @remark All the field names and values are assumed to be encoded.
         * @remark This function does not remove the existing fields.
         * @sa get
         * @sa create
         * @sa remove
         * @sa clear
         */
        CRONZ_NODISCARD_L1 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Removes all fields.
         * @sa get
         * @sa create
         * @sa remove
         * @sa parse
         */
        void clear() noexcept;

        /** @} */
        /**
         * @brief Returns the number of fields in the container.
         * @return Number of fields in the container.
         * @sa size
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Returns the number of fields in the container.
         * @return Number of fields in the container.
         * @sa count
         */
        CRONZ_NODISCARD_L1 std::size_t size() const noexcept;

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Calculates the output length if the field is stringified.
         * @return The output length if the field is stringified.
         * @remark Returned number indicates the length of the encoded output.
         * @sa stringify
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells if there are any fields registered or not.
         * @return `true` if there are any fields registered, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /** @} */

        /**
         * @name Conversion.
         */
        /** @{ */
        /**
         * @brief Encodes and converts field to a string.
         * @return Stringification result. Upon failure, this will be an empty string.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @param[out] str Stringification result.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @param[out] str Stringification result.
         * @param[in] offset Where to start writing in `str`.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells if there are any fields registered or not.
         * @return `true` if there are any fields registered, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /** @} */

        /**
         * @name Iterators.
         */
        /** @{ */
        /**
         * @brief Iterator type.
         * @typedef ArrayType::iterator Iterator
         */
        typedef ArrayType::iterator Iterator;

        /**
         * @brief Constant iterator type.
         * @typedef ArrayType::iterator Iterator
         */
        typedef ArrayType::const_iterator ConstIterator;

        /**
         * @brief Reverse iterator type.
         * @typedef ArrayType::iterator Iterator
         */
        typedef ArrayType::reverse_iterator ReverseIterator;

        /**
         * @brief Constant reverse iterator type.
         * @typedef ArrayType::iterator Iterator
         */
        typedef ArrayType::const_reverse_iterator ConstReverseIterator;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 Iterator begin() noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 Iterator end() noexcept;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstIterator cbegin() const noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstIterator cend() const noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ReverseIterator rbegin() noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ReverseIterator rend() noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator crbegin() const noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator crend() const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         * @remark Does nothing.
         */
        ~QueryManager() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/query/impl/manager.ipp"

#endif // CRONZ_URL_QUERY_MANAGER_HPP
