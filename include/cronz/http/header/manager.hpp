/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_HEADER_MANAGER_HPP
#define CRONZ_HTTP_HEADER_MANAGER_HPP 1

#include "cronz/http/header/field.hpp"

#include <functional>
#include <type_traits>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Header manager class.
     * @class HeaderManager
     */
    class HeaderManager final {
    public:
        /**
         * @name Type definitions.
         */
        /** @{ */
        /**
         * @brief Array type.
         * @typedef std::vector<HeaderField *> ArrayType
         */
        using ArrayType = std::vector<HeaderField *>;

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

        // Fields.
        CRONZ_NODISCARD_L1 HeaderField *_get(std::string_view name, const HeaderField *after) const noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        HeaderManager() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the number of fields.
         * @return The number of fields.
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Returns `true` if the header manager is empty.
         * @return `true` if the header manager is empty.
         * @return `false` if the header manager is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Returns the length of the header manager.
         * @return The length of the header manager.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Fields.
         */
        /** @{ */
        /**
         * @brief Returns `true` if the header manager contains the field.
         * @param[in] name The name of the field.
         * @return `true` if the header manager contains the field.
         * @return `false` if the header manager does not contain the field.
         */
        CRONZ_NODISCARD_L1 bool contains(std::string_view name) const noexcept;

        /**
         * @brief Returns the number of fields with the given name.
         * @param[in] name The name of the field.
         * @return The number of fields with the given name.
         */
        CRONZ_NODISCARD_L1 std::size_t count(std::string_view name) const noexcept;

        /**
         * @brief Returns the field with the given name.
         * @param[in] name The name of the field.
         * @param[in] after The field to search after.
         * @return The field with the given name.
         */
        CRONZ_NODISCARD_L1 HeaderField *get(std::string_view name, const HeaderField *after = nullptr) noexcept;

        /**
         * @brief Returns the field with the given name.
         * @param[in] name The name of the field.
         * @param[in] after The field to search after.
         * @return The field with the given name.
         */
        CRONZ_NODISCARD_L1 const HeaderField *get(std::string_view name,
                                                  const HeaderField *after = nullptr) const noexcept;

        /**
         * @brief Adds a field with the given name.
         * @param[in] name The name of the field.
         * @return The field with the given name.
         */
        CRONZ_NODISCARD_L2 HeaderField *add(std::string_view name) noexcept;

        /**
         * @brief Adds a field with the given name and value.
         * @param[in] name The name of the field.
         * @param[in] value The value of the field.
         * @return The field with the given name and value.
         */
        CRONZ_NODISCARD_L2 HeaderField *add(std::string_view name, std::string_view value) noexcept;

        /**
         * @brief Adds a field with the given field.
         * @param[in] field The field to add.
         * @return The field with the given name and value.
         */
        CRONZ_NODISCARD_L2 HeaderField *add(const HeaderField &field) noexcept;

        /**
         * @brief Sets the field with the given name.
         * @param[in] name The name of the field.
         * @return The field with the given name.
         * @remark This will remove all the other fields with the same name.
         */
        CRONZ_NODISCARD_L2 HeaderField *set(std::string_view name) noexcept;

        /**
         * @brief Sets the field with the given name and value.
         * @param[in] name The name of the field.
         * @param[in] value The value of the field.
         * @return The field with the given name and value.
         * @remark This will remove all the other fields with the same name.
         */
        CRONZ_NODISCARD_L2 HeaderField *set(std::string_view name, std::string_view value) noexcept;

        /**
         * @brief Sets the field with the given field.
         * @param[in] field The field to set.
         * @return The field with the given name and value.
         * @remark This will remove all the other fields with the same name.
         */
        CRONZ_NODISCARD_L2 HeaderField *set(const HeaderField &field) noexcept;

        /**
         * @brief Removes the field with the given name.
         * @param[in] name The name of the field.
         * @return `true` if the field was removed.
         * @return `false` if the field was not removed.
         */
        CRONZ_NODISCARD_L2 bool remove(std::string_view name) noexcept;

        /**
         * @brief Removes the field with the given field.
         * @param[in] field The field to remove.
         * @return `true` if the field was removed.
         * @return `false` if the field was not removed.
         */
        CRONZ_NODISCARD_L2 bool remove(const HeaderField *field) noexcept;

        /**
         * @brief Removes the field with the given function.
         * @param[in] fun The function to remove the field.
         */
        void remove(const std::function<bool(HeaderField *field)> &fun) noexcept;

        /**
         * @brief Removes the field with the given iterator.
         * @param[in] iterator The iterator to remove the field.
         * @return The iterator to the next field.
         */
        template<typename IteratorType>
            requires (std::is_same_v<IteratorType, Iterator> || std::is_same_v<IteratorType, ConstIterator>)
        CRONZ_NODISCARD_L2 IteratorType remove(IteratorType iterator) noexcept;

        /**
         * @brief Iterates over the fields and calls the function.
         * @tparam ReturnType The return type of the function.
         * @param[in] fun The function to call.
         * @remark The function should return `true` to continue iterating, or `false` to stop iterating.
         */
        template<typename ReturnType>
            requires (std::is_same_v<ReturnType, void> || std::is_convertible_v<ReturnType, bool>)
        void forEach(const std::function<ReturnType(HeaderField *field)> &fun) const noexcept;

        /**
         * @brief Iterates over the fields with the given name and calls the function.
         * @tparam ReturnType The return type of the function.
         * @param[in] name The name of the field.
         * @param[in] fun The function to call.
         * @remark The function should return `true` to continue iterating, or `false` to stop iterating.
         */
        template<typename ReturnType>
            requires (std::is_same_v<ReturnType, void> || std::is_convertible_v<ReturnType, bool>)
        void forEach(std::string_view name, const std::function<ReturnType(HeaderField *field)> &fun) const noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses the headers from the given string.
         * @param[in] headers The headers to parse.
         * @return `true` if the headers were parsed successfully.
         * @return `false` if the headers were not parsed successfully.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view headers) noexcept;

        /**
         * @brief Stringifies the headers.
         * @return The headers as a string.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the headers to the given string.
         * @param[in] str The string to stringify the headers to.
         * @return `true` if the headers were stringified successfully.
         * @return `false` if the headers were not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the headers to the given string.
         * @param[in] str The string to stringify the headers to.
         * @param[inout] offset The offset to append to the string.
         * @return `true` if the headers were stringified successfully.
         * @return `false` if the headers were not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Clears the header manager.
         * @remark This will delete all fields in the header manager.
         */
        void clear() noexcept;

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
         * @brief Returns `true` if the header manager is empty.
         * @return `true` if the header manager is not empty.
         * @return `false` if the header manager is empty.
         */
        CRONZ_NODISCARD_L1 explicit(true) operator bool() const noexcept;

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~HeaderManager() noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/header/impl/manager.ipp"

#endif // CRONZ_HTTP_HEADER_MANAGER_HPP
