/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_PATH_HPP
#define CRONZ_URI_PATH_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief Path class.
     * @class Path
     */
    class Path final {
    public:
        /**
         * @name Static types.
         */
        /** @{ */
        /**
         * @brief Path array type.
         * @typedef std::vector<std::string> ArrayType
         */
        using ArrayType = std::vector<std::string>;

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
        ArrayType _segments{};

        bool _root = false;

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 bool _insert(ArrayType::const_iterator position, std::string_view path, bool raw) noexcept;

        // Static utility functions.
        CRONZ_NODISCARD_L1 static bool _segmentize(std::string_view path, ArrayType &segments) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Path() noexcept = default;

        /**
         * @brief Constructor with a path.
         * @param[in] path The path to parse.
         */
        explicit(true) Path(std::string_view path) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Tells whether the path starts with a root segment or not.
         * @return `true` if the path starts with a root segment.
         * @return `false` if the path does not start with a root segment.
         */
        CRONZ_NODISCARD_L1 bool isRoot() const noexcept;

        /**
         * @brief Sets the path to start with a root segment.
         * @param[in] root `true` if the path starts with a root segment.
         * @param[in] root `false` if the path does not start with a root segment.
         */
        void setRoot(bool root) noexcept;

        /**
         * @brief Returns the number of segments in the path.
         * @return The number of segments in the path.
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Tells whether the path is empty or not.
         * @return `true` if the path is empty.
         * @return `false` if the path is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Returns the length of the path.
         * @return The length of the path.
         * @remark The length is calculated by encoding the segments using URI encoding.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Appends a segment to the path.
         * @param[in] segment The segment to append.
         * @param[in] raw Whether to append the segment as raw or not.
         * @return `true` if the segment is appended successfully.
         * @return `false` if the segment is not appended successfully.
         * @remark Upon failure, the existing contents of the path are kept intact.
         * @remark If `raw` is `true`, the segment is appended as is, without URI encoding.
         * @remark If `raw` is `false`, the segment is appended with URI encoding. It can be multiple segments
         * separated by '/'.
         */
        CRONZ_NODISCARD_L1 bool append(std::string_view segment, bool raw = false) noexcept;

        /**
         * @brief Prepends a segment to the path.
         * @param[in] segment The segment to prepend.
         * @param[in] raw Whether to prepend the segment as raw or not.
         * @return `true` if the segment is prepended successfully.
         * @return `false` if the segment is not prepended successfully.
         * @remark Upon failure, the existing contents of the path are kept intact.
         * @remark If `raw` is `true`, the segment is prepended as is, without URI encoding.
         * @remark If `raw` is `false`, the segment is prepended with URI encoding. It can be multiple segments
         * separated by '/'.
         */
        CRONZ_NODISCARD_L1 bool prepend(std::string_view segment, bool raw = false) noexcept;

        /**
         * @brief Parses a path and sets the segments.
         * @param[in] path The path to parse.
         * @return `true` if the path is parsed successfully.
         * @return `false` if the path is not parsed successfully.
         * @remark Upon failure, the existing contents of the path are kept intact.
         */
        CRONZ_NODISCARD_L1 bool parse(std::string_view path) noexcept;

        /**
         * @brief Stringifies the path.
         * @return The stringified path.
         * @remark Upon failure, the returned string is empty.
         * @remark The segments are encoded using URI encoding.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the path.
         * @param[out] str The string to store the stringified path.
         * @return `true` if the path is stringified successfully.
         * @return `false` if the path is not stringified successfully.
         * @remark Upon failure, the contents of the string are cleared.
         * @remark The segments are encoded using URI encoding.
         */
        CRONZ_NODISCARD_L1 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the path.
         * @param[out] str The string to store the stringified path.
         * @param[in] offset The offset to start writing to the string.
         * @return `true` if the path is stringified successfully.
         * @return `false` if the path is not stringified successfully.
         * @remark The segments are encoded using URI encoding.
         */
        CRONZ_NODISCARD_L1 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /**
         * @brief Clears the path.
         * @remark The segments are cleared.
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
         * @name Segments.
         */
        /** @{ */
        /**
         * @brief Returns the segment at the given position.
         * @param[in] position The position of the segment to return.
         * @return The segment at the given position.
         * @remark The position is zero-based.
         */
        CRONZ_NODISCARD_L1 constexpr std::string &at(std::size_t position);

        /**
         * @brief Returns the segment at the given position.
         * @param[in] position The position of the segment to return.
         * @return The segment at the given position.
         * @remark The position is zero-based.
         */
        CRONZ_NODISCARD_L1 constexpr const std::string &at(std::size_t position) const;

        /**
         * @brief Removes the segment at the given position.
         * @param[in] position The position of the segment to remove.
         * @return Iterator to the segment at the given position after removal.
         * @remark The position is zero-based.
         * @remark If the position is out of range, the end iterator is returned.
         */
        CRONZ_NODISCARD_L1 constexpr Iterator removeAt(std::size_t position) noexcept;

        /**
         * @brief Removes the segment at the given position.
         * @param[in] position The position of the segment to remove.
         * @return Iterator to the segment at the given position after removal.
         * @remark If the position is out of range, the end iterator is returned.
         */
        template<typename IteratorType>
            requires (std::is_same_v<IteratorType, Iterator> ||
                      std::is_same_v<IteratorType, ConstIterator>)
        CRONZ_NODISCARD_L1 constexpr IteratorType removeAt(IteratorType position) noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Implicit conversion operator to `bool`.
         * @return `true` if the path is empty.
         * @return `false` if the path is not empty.
         */
        CRONZ_NODISCARD_L1 explicit(true) operator bool() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] path The path to assign.
         * @return A reference to the current object.
         */
        Path &operator=(std::string_view path) noexcept;

        /**
         * @brief Returns the segment at the given position.
         * @param[in] position The position of the segment to return.
         * @return The segment at the given position.
         * @remark The position is zero-based.
         */
        CRONZ_NODISCARD_L1 constexpr std::string &operator[](std::size_t position);

        /**
         * @brief Returns the segment at the given position.
         * @param[in] position The position of the segment to return.
         * @return The segment at the given position.
         * @remark The position is zero-based.
         */
        CRONZ_NODISCARD_L1 constexpr const std::string &operator[](std::size_t position) const;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~Path() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/impl/path.ipp"

#endif //CRONZ_URI_PATH_HPP
