/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_QUERY_FIELD_HPP
#define CRONZ_URL_QUERY_FIELD_HPP 1

#include "cronz/url/types.hpp"

#include <string>
#include <vector>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @brief Query field.
     * @class QueryField
     * @tparam Renamable Whether the field is renamable.
     * @ingroup cronz_url_query
     * @remark This supports both single-value and array fields.
     * @remark Values in this container are not encoded.
     */
    template <bool Renamable = true>
    class QueryField {
        // Properties.
        std::string name_;
        std::string value_;
        std::vector<std::size_t> indices_{static_cast<std::size_t>(0)};

        template <typename StringifiableType>
        [[nodiscard]] static bool stringify_(const StringifiableType &value, std::string &str) noexcept;

        // Friends.
        friend class QueryManager;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @remark Does nothing.
         * @remark Requires the field to be renamable.
         */
        QueryField() noexcept requires Renamable;

        /**
         * @brief Constructor with a name initializer.
         * @param[in] name Field name.
         * @remark Upon failure, this might throw an exception.
         */
        explicit QueryField(std::string name);

        /** @} */

        /**
         * @name Name.
         */
        /** @{ */
        /**
         * @brief Returns a mutable reference to the field name.
         * @return Mutable reference to the field name.
         * @remark Query fields cannot change their names if they are part of a `QueryManager`.
         * @remark This function requires the `Renamable` to be `true`.
         * @remark This function is an alias to `setName`.
         * @sa getName
         * @sa setName
         */
        CRONZ_NODISCARD_L1 std::string& name() noexcept requires Renamable;

        /**
         * @brief Returns a read-only reference to the field name.
         * @return Read-only reference to the field name.
         * @remark Query fields cannot change their names if they are part of a `QueryManager`.
         * @remark This function is an alias to `getName`.
         * @sa getName
         * @sa setName
         */
        CRONZ_NODISCARD_L1 const std::string& name() const noexcept;

        /**
         * @brief Returns a read-only reference to the field name.
         * @return Read-only reference to the field name.
         * @sa name
         * @sa setName
         */
        CRONZ_NODISCARD_L1 const std::string& getName() const noexcept;

        /**
         * @brief Updates the field's name.
         * @param[in] name New name.
         * @return `true` if name is successfully assigned, otherwise, `false`.
         * @remark This function requires the `Renamable` to be `true`.
         * @sa name
         * @sa getName
         */
        CRONZ_NODISCARD_L2 bool setName(const std::string &name) noexcept requires Renamable;

        /** @} */

        /**
         * @name Value.
         */
        /** @{ */
        /**
         * @brief Returns a read-only reference to the field value.
         * @return Read-only reference to the field value.
         * @remark This will return a single, decoded value. In case of an array field, separations might not be
         * determinate. Use `getValueAt` instead to get value at a specific position.
         * @remark This function is an alias to `getValue`.
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L1 const std::string& value() const noexcept;

        /**
         * @brief Returns a read-only reference to the field value.
         * @return Read-only reference to the field value.
         * @remark This will return a single, decoded value. In case of an array field, separations might not be
         * determinate. Use `getValueAt` instead to get value at a specific position.
         * @sa value
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L1 const std::string& getValue() const noexcept;

        /**
         * @brief Retrieves the value at the given position.
         * @param[in] position Position of the value.
         * @param[out] value Output.
         * @return `true` if a value at the given position is found and could be successfully assigned to `value`,
         * otherwise, `false`.
         * @sa value
         * @sa getValue
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L2 bool getValueAt(const std::size_t &position, std::string &value) const noexcept;

        /**
         * @brief Retrieves the value at the given position.
         * @param[in] position Position of the value.
         * @return Value at the given position.
         * @remark If `position` is out of range or memory allocation error occurs, the returned string will be empty.
         * @sa value
         * @sa getValue
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L1 std::string getValueAt(const std::size_t &position) const noexcept;

        /**
         * @brief Retrieves the value at the given position.
         * @param[in] position Position of the value.
         * @param[out] value Output.
         * @param[out] length Length of the value.
         * @remark If `position` is out of range or memory allocation error occurs, `nullptr` will be assigned to
         * `value`.
         * @sa value
         * @sa getValue
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        void getValueAt(const std::size_t &position, const char *&value, std::size_t &length) const noexcept;

        /**
         * @brief Splits field values and puts them into a vector of string.
         * @param[out] values Vector to be filled with field values.
         * @return `true` if operation was successful, otherwise, `false`.
         * @remark Upon failure, `values` will be emptied.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L1 bool splitValues(std::vector<std::string> &values) const noexcept;

        /**
         * @brief Splits field values and puts them into a vector of string.
         * @return Vector filled with field values.
         * @remark Upon failure, the returned vector will be empty.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L1 std::vector<std::string> splitValues() const noexcept;

        /**
         * @brief Adds a value to the field.
         * @tparam StringifiableType Stringifiable type.
         * @param[in] value Value to be added to the field.
         * @return `true` if value is successfully added to the field, otherwise, `false`.
         * @remark `value` should be a string type or should be able to be converted to string via `std::to_string`. If
         * it is not, this function will return `false` or the program will not compile at all.
         * @remark If the field was not an array before, it will be converted to an array after this.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        template <typename StringifiableType>
        CRONZ_NODISCARD_L2 bool addValue(const StringifiableType &value) noexcept;

        /**
         * @brief Sets the current field value.
         * @tparam StringifiableType Stringifiable type.
         * @param[in] value Value to be assigned to the field.
         * @return `true` if value is successfully assigned, otherwise, `false`.
         * @remark `value` should be a string type or should be able to be converted to string via `std::to_string`. If
         * it is not, this function will return `false` or the program will not compile at all.
         * @warning This overwrites the current value(s). If the field was an array before, it will be converted to a
         * single-value field.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clearValues
         */
        template <typename StringifiableType>
        CRONZ_NODISCARD_L2 bool setValue(const StringifiableType &value) noexcept;

        /**
         * @brief Sets the value at the given position.
         * @tparam StringifiableType Stringifiable type.
         * @param[in] position Position (zero-based) of the value to be set.
         * @param[in] value Value to be assigned.
         * @return `true` if value is successfully assigned, otherwise, `false`.
         * @remark If `position` is out of range, value is appended via `addValue`.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa removeValueAt
         * @sa clearValues
         */
        template <typename StringifiableType>
        CRONZ_NODISCARD_L2 bool setValueAt(const std::size_t &position, const StringifiableType &value) noexcept;

        /**
         * @brief Removes value at the given position.
         * @param[in] position Value position (zero-based) to be removed.
         * @return `true` if an element is found and removed at the given position, otherwise, `false`.
         * @remark If position is out of range, nothing happens. However, the return value will still be `false`.
         * @remark If there is only one value in the field, this function is equal to `clearValues` in terms of output.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa clearValues
         */
        CRONZ_NODISCARD_L2 bool removeValueAt(const std::size_t &position) noexcept;

        /**
         * @brief Clears the field value(s).
         * @remark If the field is an array, the field will lose its array status.
         * @remark After calling this function, the field value will equal to empty string.
         * @sa value
         * @sa getValue
         * @sa getValueAt
         * @sa splitValues
         * @sa addValue
         * @sa setValue
         * @sa setValueAt
         * @sa removeValueAt
         * @sa clear
         */
        void clearValues() noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns value positions.
         * @return Reference to a read-only vector that contains value positions.
         * @remark This function is an alias to `getIndices`.
         * @sa getIndices
         */
        CRONZ_NODISCARD_L1 const std::vector<std::size_t>& indices() const noexcept;

        /**
         * @brief Returns value positions.
         * @return Reference to a read-only vector that contains value positions.
         * @sa indices
         */
        CRONZ_NODISCARD_L1 const std::vector<std::size_t>& getIndices() const noexcept;

        /**
         * @brief Tells whether the current field is an array.
         * @return `true` if the field holds multiple values, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool isArray() const noexcept;

        /**
         * @brief Tells the number of values in the field.
         * @return The number of values in the field.
         * @remark Values higher than `1` indicates that the field contains multiple values and therefore is an array.
         * @remark This function is guaranteed to return `non-zero` (`0`), as fields should contain at least one value.
         * @sa size
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Tells the number of values in the field.
         * @return The number of values in the field.
         * @remark Values higher than `1` indicates that the field contains multiple values and therefore is an array.
         * @remark This function is guaranteed to return `non-zero` (`0`), as fields should contain at least one value.
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
         * @brief Clears the field name and value(s).
         * @remark If the field is an array, the field will lose its array status.
         * @remark After calling this function, the field value will equal to empty string.
         * @remark If the field is renamable, this clears the field name. If not, the field name will not be affected.
         * @sa clearValues
         */
        void clear() noexcept;

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
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         * @remark Does nothing.
         */
        ~QueryField() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/query/impl/field.ipp"

#endif // CRONZ_URL_QUERY_FIELD_HPP
