/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_PATH_MANAGER_HPP
#define CRONZ_URL_PATH_MANAGER_HPP 1

#include "cronz/url/types.hpp"

#include <vector>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_path
     * @brief Path manager.
     * @class PathManager
     */
    class PathManager {
        // Properties.
        using ArrayType = std::vector<std::string>;

        ArrayType paths_;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        PathManager() noexcept;

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
         * @name Path management.
         */
        /** @{ */
        /**
         * @brief Adds path to the end of the path list.
         * @param[in] path Path to be added.
         * @return `true` if operation is successful, otherwise, `false`.
         * @remark `path` is expected to be decoded.
         * @sa addEncodedPath
         */
        CRONZ_NODISCARD_L2 bool addPath(const std::string &path) noexcept;

        /**
         * @brief Decodes and adds an encoded path to the end of the path list.
         * @param[in] path Path to be added.
         * @return `true` if operation is successful, otherwise, `false`.
         * @remark `path` is expected to be encoded.
         * @sa addPath
         */
        CRONZ_NODISCARD_L2 bool addEncodedPath(const std::string &path) noexcept;

        /**
         * @brief Returns mutable reference to the path at the given position.
         * @param[in] position Position of the path entry.
         * @return Mutable reference to the path at the given position.
         * @exception std::out_of_range Thrown if `position` is out of range.
         */
        CRONZ_NODISCARD_L1 std::string& at(const std::size_t &position) noexcept;

        /**
         * @brief Returns mutable reference to the path at the given position.
         * @param[in] position Position of the path entry.
         * @return Mutable reference to the path at the given position.
         * @exception std::out_of_range Thrown if `position` is out of range.
         */
        CRONZ_NODISCARD_L1 const std::string& at(const std::size_t &position) const noexcept;

        /**
         * @brief Removes the path entry at the given position.
         * @param[in] position Position of the path entry to be removed.
         * @remark If `position` is out of range, nothing happens.
         */
        void removeAt(const std::size_t &position) noexcept;

        /**
         * @brief Removes the path entry at the given position.
         * @param[in] position Position of the path entry to be removed.
         * @return Iterator following the last removed element.
         * @remark If `position` is out of range, nothing happens.
         */
        CRONZ_NODISCARD_L2 Iterator removeAt(const Iterator &position) noexcept;

        /**
         * @brief Removes the path entry at the given position.
         * @param[in] position Position of the path entry to be removed.
         * @return Iterator following the last removed element.
         * @remark If `position` is out of range, nothing happens.
         */
        CRONZ_NODISCARD_L2 ConstIterator removeAt(const ConstIterator &position) noexcept;

        /**
         * @brief Parses the path section of a URL.
         * @param[in] str Path string to be parsed.
         * @return `true` if `str` is successfully parsed, otherwise, `false`.
         * @remark Upon failure, existing data is not altered. The only failure reason is failing to allocate memory.
         * @remark All the path entries found while parsing is assumed to be encoded.
         * @remark This function does not remove the existing paths.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /**
         * @brief Parses the path section of a URL.
         * @param[in] str Path string to be parsed.
         * @param[in] length Length of the path string to be parsed.
         * @return `true` if `str` is successfully parsed, otherwise, `false`.
         * @remark Upon failure, existing data is not altered. The only failure reason is failing to allocate memory.
         * @remark All the path entries found while parsing is assumed to be encoded.
         * @remark This function does not remove the existing paths.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Removes all paths in the container.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the number of paths in the container.
         * @return Number of paths in the container.
         * @sa size
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Returns the number of paths in the container.
         * @return Number of paths in the container.
         * @sa count
         */
        CRONZ_NODISCARD_L1 std::size_t size() const noexcept;

        /**
         * @brief Calculates the output length if the field is stringified.
         * @return The output length if the field is stringified.
         * @remark Returned number indicates the length of the encoded output.
         * @sa stringify
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells if the container is empty.
         * @return `true` if the container has no paths stored, otherwise, `false`.
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
         * @brief Tells if the container is not empty.
         * @return `true` if the container is not empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /**
         * @brief Returns mutable reference to the path at the given position.
         * @param[in] position Position of the path entry.
         * @return Mutable reference to the path at the given position.
         * @exception std::out_of_range Thrown if `position` is out of range.
         * @sa at
         */
        CRONZ_NODISCARD_L1 std::string& operator[](const std::size_t &position) noexcept;

        /**
         * @brief Returns mutable reference to the path at the given position.
         * @param[in] position Position of the path entry.
         * @return Mutable reference to the path at the given position.
         * @exception std::out_of_range Thrown if `position` is out of range.
         * @sa at
         */
        CRONZ_NODISCARD_L1 const std::string& operator[](const std::size_t &position) const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~PathManager() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/path/impl/manager.ipp"

#endif // CRONZ_URL_PATH_MANAGER_HPP
