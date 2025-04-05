/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_METHOD_METHOD_HPP
#define CRONZ_HTTP_METHOD_METHOD_HPP 1

#include "cronz/http/types.hpp"

#ifdef DELETE
#define CRONZ_HTTP_METHOD_DELETE DELETE
#undef DELETE
#endif // DELETE

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief HTTP method.
     * @class Method
     * @see [RFC9110 - Section 9.1](https://datatracker.ietf.org/doc/html/rfc9110#section-9.1-4).
     */
    class Method {
        // Properties.
    public:
        /**
         * @name Static properties.
         */
        /** @{ */
        /**
         * @brief GET method.
         */
        static constexpr std::string_view GET = "GET";

        /**
         * @brief HEAD method.
         */
        static constexpr std::string_view HEAD = "HEAD";

        /**
         * @brief POST method.
         */
        static constexpr std::string_view POST = "POST";

        /**
         * @brief PUT method.
         */
        static constexpr std::string_view PUT = "PUT";

        /**
         * @brief DELETE method.
         */
        static constexpr std::string_view DELETE = "DELETE";

        /**
         * @brief CONNECT method.
         */
        static constexpr std::string_view CONNECT = "CONNECT";

        /**
         * @brief OPTIONS method.
         */
        static constexpr std::string_view OPTIONS = "OPTIONS";

        /**
         * @brief TRACE method.
         */
        static constexpr std::string_view TRACE = "TRACE";

        static const std::array<Method, static_cast<std::size_t>(8)> PredefinedMethods;

        /** @} */

        /***/

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Method value.
         * @note The method value is case-sensitive.
         */
        std::string value;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @details Initializes the method to an empty string.
         */
        Method() noexcept = default;

        /**
         * @brief Constructor with a method value.
         * @param[in] method Method value.
         * @details Initializes the method to the given value.
         */
        explicit Method(std::string_view method) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Check if the method is valid.
         * @return `true` if the method is valid.
         * @return `false` if the method is not valid.
         */
        CRONZ_NODISCARD_L1 bool isValid() const noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are equal.
         * @return `false` if the methods are not equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool compare(std::string_view method) const noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are equal.
         * @return `false` if the methods are not equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool compare(const Method &method) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Convert the method to a boolean value.
         * @return `true` if the method is valid.
         * @return `false` if the method is not valid.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Convert the method to a string.
         * @return Method as a string.
         */
        CRONZ_NODISCARD_L1 operator std::string_view() const noexcept;

        /**
         * @brief Assign a method to the method.
         * @param[in] method Method to assign.
         * @return Reference to the method.
         */
        Method &operator=(std::string_view method) noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are equal.
         * @return `false` if the methods are not equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool operator==(std::string_view method) const noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are equal.
         * @return `false` if the methods are not equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool operator==(const Method &method) const noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are not equal.
         * @return `false` if the methods are equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool operator!=(std::string_view method) const noexcept;

        /**
         * @brief Compare the current method with another method.
         * @param[in] method Method to compare.
         * @return `true` if the methods are not equal.
         * @return `false` if the methods are equal.
         * @note The comparison is case-insensitive.
         * @note Both the current method and the method to compare must be valid.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const Method &method) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        ~Method() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Check if the method is valid.
         * @param[in] method Method to check.
         * @return `true` if the method is valid.
         * @return `false` if the method is not valid.
         */
        CRONZ_NODISCARD_L1 static bool IsValid(std::string_view method) noexcept;

        /** @} */

        /**
         * @name Friends.
         */
        /** @{ */
        friend bool operator==(std::string_view method, const Method &instance) noexcept;

        friend bool operator!=(std::string_view method, const Method &instance) noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/method/impl/method.ipp"

#ifdef CRONZ_HTTP_METHOD_DELETE
#define DELETE CRONZ_HTTP_METHOD_DELETE
#undef CRONZ_HTTP_METHOD_DELETE
#endif // CRONZ_HTTP_METHOD_DELETE

#endif // CRONZ_HTTP_METHOD_METHOD_HPP
