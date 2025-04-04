/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_HEADER_FIELD_HPP
#define CRONZ_HTTP_HEADER_FIELD_HPP 1

#include "cronz/http/types.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class HeaderManager;

    /**
     * @ingroup cronz_http
     * @brief Header field class.
     * @class HeaderField
     * @tparam Renamable If the field is renamable or not.
     */
    class HeaderField final {
        // Properties.
        std::string _name{};
        std::string _value{};

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 bool _cn(std::string_view name) const noexcept;

        // Static utility functions.
        static void _normalize(std::string &str) noexcept;

        // Friends.
        friend class HeaderManager;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        HeaderField() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the name of the field.
         * @return The name of the field.
         */
        CRONZ_NODISCARD_L1 const std::string &name() const noexcept;

        /**
         * @brief Sets the name of the field.
         * @param[in] name The name of the field.
         * @return `true` if the name is valid.
         * @return `false` if the name is invalid.
         */
        CRONZ_NODISCARD_L2 bool name(std::string_view name) noexcept;

        /**
         * @brief Returns the value of the field.
         * @return The value of the field.
         */
        CRONZ_NODISCARD_L1 const std::string &value() const noexcept;

        /**
         * @brief Sets the value of the field.
         * @param[in] value The value of the field.
         * @return `true` if the value is valid.
         * @return `false` if the value is invalid.
         */
        CRONZ_NODISCARD_L2 bool value(std::string_view value) noexcept;

        /**
         * @brief Returns the length of the field.
         * @return The length of the field.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Returns `true` if the field is empty.
         * @return `true` if the field is empty.
         * @return `false` if the field is not empty.
         * @remark The field is empty if the name is empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses the header field.
         * @param[in] header The header field to parse.
         * @return `true` if the header field is valid.
         * @return `false` if the header field is invalid.
         */
        CRONZ_NODISCARD_L1 bool parse(std::string_view header) noexcept;

        /**
         * @brief Stringifies the header field.
         * @return The stringified header field.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the header field.
         * @param[out] str The string to store the header field.
         * @return `true` if the header field is valid.
         * @return `false` if the header field is invalid.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the header field.
         * @param[out] str The string to store the header field.
         * @param[inout] offset The offset to start writing to.
         * @return `true` if the header field is valid.
         * @return `false` if the header field is invalid.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Converts the field to the specified type.
         * @tparam ConvertibleType The type to convert to.
         * @param[out] val The value to assign the converted value.
         * @return `true` if the conversion is valid.
         * @return `false` if the conversion is invalid.
         */
        template<typename ConvertibleType>
            requires (std::is_integral_v<ConvertibleType> || std::is_floating_point_v<ConvertibleType> ||
                      std::is_same_v<ConvertibleType, std::string> ||
                      std::is_same_v<ConvertibleType, std::vector<char> >)
        CRONZ_NODISCARD_L2 bool as(ConvertibleType &val) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~HeaderField() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/header/impl/field.ipp"

#endif // CRONZ_HTTP_HEADER_FIELD_HPP
