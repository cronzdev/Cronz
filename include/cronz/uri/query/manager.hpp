/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_QUERY_MANAGER_HPP
#define CRONZ_URI_QUERY_MANAGER_HPP 1

#include "cronz/uri/query/field.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief URI query manager class.
     * @class QueryManager
     */
    class QueryManager final {
    public:
        /**
         * @name Static types.
         */
        /** @{ */
        /**
         * @brief Field array type.
         * @typedef std::vector<ImmutableQueryField> ArrayType
         */
        using ArrayType = std::vector<ImmutableQueryField *>;

        /**
         * @brief Iterator type.
         * @typedef ArrayType::iterator Iterator
         */
        typedef ArrayType::iterator Iterator;

        /**
         * @brief Constant iterator type.
         * @typedef ArrayType::const_iterator Iterator
         */
        typedef ArrayType::const_iterator ConstIterator;

        /**
         * @brief Reverse iterator type.
         * @typedef ArrayType::reverse_iterator Iterator
         */
        typedef ArrayType::reverse_iterator ReverseIterator;

        /**
         * @brief Constant reverse iterator type.
         * @typedef ArrayType::const_reverse_iterator Iterator
         */
        typedef ArrayType::const_reverse_iterator ConstReverseIterator;

        /** @} */

    private:
        // Properties.
        ArrayType _fields{};

        // Static utility functions.
        CRONZ_NODISCARD_L1 static bool _split(const char *beg, const char *end, std::string &name,
                                              std::string &value) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        QueryManager() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the number of fields in the current manager.
         * @param[in] unique Whether to include array elements in the count.
         * @return Number of fields in the current manager.
         */
        CRONZ_NODISCARD_L1 std::size_t count(bool unique = true) const noexcept;

        /**
         * @brief Returns the length of the stringified version of the query string.
         * @return Length of the query string.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells whether the current manager contains any fields.
         * @return `true` if the current manager contains any fields.
         * @return `false` if the current manager does not contain any fields.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /** @} */

        /**
         * @name Fields.
         */
        /** @{ */
        /**
         * @brief Tells whether a field with the given name exists.
         * @param[in] name Field name.
         * @return `true` if a field with the given name exists.
         * @return `false` if a field with the given name does not exist.
         * @remark This function is case-sensitive.
         */
        CRONZ_NODISCARD_L1 bool contains(std::string_view name) const;

        /**
         * @brief Returns a field with the given name.
         * @param[in] name Field name.
         * @return Pointer to the field if it exists.
         * @return `nullptr` if the field does not exist.
         * @remark This function is case-sensitive.
         */
        CRONZ_NODISCARD_L1 ImmutableQueryField *get(std::string_view name) const noexcept;

        /**
         * @brief Creates a field with the given name.
         * @param[in] name Field name.
         * @return Pointer to the field if it is created successfully.
         * @return `nullptr` if the field could not be created.
         * @remark This function is case-sensitive.
         * @remark This function will not create a field if a field with the same name already exists. Instead, it will
         * return a pointer to the existing field.
         */
        CRONZ_NODISCARD_L1 ImmutableQueryField *create(std::string_view name) noexcept;

        /**
         * @brief Creates a field with the given name.
         * @param[in] field Field to create.
         * @return Pointer to the field if it is created successfully.
         * @return `nullptr` if the field could not be created.
         * @remark This function will not create a field if a field with the same name already exists. Instead, it will
         * return a pointer to the existing field. The existing field will be updated with the new value.
         */
        template<bool Renamable>
        CRONZ_NODISCARD_L2 ImmutableQueryField *create(const QueryField<Renamable> &field) noexcept;

        /**
         * @brief Removes a field with the given name.
         * @param[in] name Field name.
         * @return `true` if the field is removed successfully.
         * @return `false` if the field could not be removed.
         * @remark This function is case-sensitive.
         */
        CRONZ_NODISCARD_L2 bool remove(std::string_view name) noexcept;

        /**
         * @brief Removes a field.
         * @param[in] field Field to remove.
         * @return `true` if the field is removed successfully.
         * @return `false` if the field could not be removed.
         * @remark The field must be created by this manager. Otherwise, it will not be removed.
         */
        CRONZ_NODISCARD_L2 bool remove(const ImmutableQueryField *field) noexcept;

        /**
         * @brief Removes the field at the given position.
         * @param[in] position The position of the field to remove.
         * @return Iterator to the field at the given position after removal.
         * @remark If the position is out of range, the end iterator is returned.
         */
        template<typename IteratorType>
            requires (std::is_same_v<IteratorType, Iterator> ||
                      std::is_same_v<IteratorType, ConstIterator>)
        CRONZ_NODISCARD_L1 constexpr IteratorType remove(IteratorType position) noexcept;

        /**
         * @brief Removes all fields in the current manager.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses a query string.
         * @param[in] str Query string to parse.
         * @return `true` if the query string is parsed successfully.
         * @return `false` if the query string could not be parsed.
         */
        CRONZ_NODISCARD_L1 bool parse(std::string_view str) noexcept;

        /**
         * @brief Stringifies the fields in the current manager.
         * @return Stringified version of the fields in the current manager.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the fields in the current manager.
         * @param[in] str String to append to.
         * @return `true` if the fields are successfully stringified.
         * @return `false` if the fields could not be stringified.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the fields in the current manager.
         * @param[in] str String to append to.
         * @param[in] offset Offset to start appending to.
         * @return `true` if the fields are successfully stringified.
         * @return `false` if the fields could not be stringified.
         * @remark Field names and values are URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Iterators.
         */
        /** @{ */
        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 constexpr Iterator begin() noexcept;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstIterator begin() const noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 constexpr Iterator end() noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstIterator end() const noexcept;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstIterator cbegin() const noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstIterator cend() const noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 constexpr ReverseIterator rbegin() noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 constexpr ReverseIterator rend() noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstReverseIterator crbegin() const noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 constexpr ConstReverseIterator crend() const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells whether the current manager contains any fields.
         * @return `true` if the current manager contains any fields.
         * @return `false` if the current manager does not contain any fields.
         */
        CRONZ_NODISCARD_L1 explicit(true) operator bool() const noexcept;

        /**
         * @brief Returns a field with the given name.
         * @param[in] name Field name.
         * @return Pointer to the field if it exists.
         * @return `nullptr` if the field does not exist.
         * @remark This function is case-sensitive.
         */
        CRONZ_NODISCARD_L1 ImmutableQueryField *operator[](std::string_view name) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~QueryManager() noexcept;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/query/impl/manager.ipp"

#endif // CRONZ_URI_QUERY_MANAGER_HPP
