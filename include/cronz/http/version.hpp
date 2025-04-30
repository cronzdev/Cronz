/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_VERSION_HPP
#define CRONZ_HTTP_VERSION_HPP 1

#include "cronz/http/types.hpp"

#include <string_view>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Represents the HTTP version.
     * @class Version
     */
    class Version final {
    public:
        /**
         * @name Static types.
         */
        /** @{ */
        /**
         * @brief Version value type.
         */
        using ValueType = std::int_fast8_t;

        /**
         * @brief Version enumeration.
         * @details Represents the HTTP version values.
         */
        enum Enum : ValueType {
            /**
             * @brief HTTP version 0.9.
             */
            HTTP_0_9 = static_cast<ValueType>(9),

            /**
             * @brief HTTP version 1.0.
             */
            HTTP_1_0 = static_cast<ValueType>(10),

            /**
             * @brief HTTP version 1.1.
             */
            HTTP_1_1 = static_cast<ValueType>(11),

            /**
             * @brief HTTP version 2.
             */
            HTTP_2 = static_cast<ValueType>(20),

            /**
             * @brief HTTP version 3.
             */
            HTTP_3 = static_cast<ValueType>(30),

            /**
             * @brief Invalid HTTP version.
             */
            Invalid = std::numeric_limits<ValueType>::max()
        };

        /** @{ */
    private:
        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 static Enum _parse(std::string_view str) noexcept;

        // Static properties.
        static const std::unordered_map<Enum, std::string_view> _strings;

    public:
        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Version value property.
         */
        Enum value;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @details Initializes the version to `Invalid`.
         */
        Version() noexcept;

        /**
         * @brief Constructor with a version value.
         * @param[in] version Version value.
         * @details Initializes the version to the given value.
         */
        explicit(false) Version(Enum version) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Parses the version string.
         * @param[in] version Version string.
         * @return `true` if the version is valid.
         * @return `false` if the version is invalid
         * @details Parses the version string and sets the version value.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view version) noexcept;

        /**
         * @brief Converts the version to a string.
         * @return Version string.
         * @details If the version is `Invalid`, an empty string is returned.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Converts the version to a string.
         * @param[out] str String to store the version.
         * @param[in] offset Offset to start writing the string.
         * @return `true` if the version is valid.
         * @return `false` if the version is invalid
         * @details If the version is `Invalid`, the string is not modified.
         * @details If the string is not large enough, it is resized.
         * @details The string is not cleared before writing.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str,
                                          std::size_t offset = static_cast<std::size_t>(0)) const noexcept;

        /**
         * @brief Gets the length of the version string.
         * @return Length of the version string.
         * @details If the version is `Invalid`, the length is `0`.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Boolean conversion operator. Checks if the version is valid.
         * @return `true` if the version is valid.
         * @return `false` if the version is invalid
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] version Version value.
         * @return Reference to the instance.
         */
        Version &operator=(Enum version) noexcept;

        /**
         * @brief Equality operator.
         * @param[in] version Version value.
         * @return `true` if the versions are equal.
         * @return `false` if the versions are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(Enum version) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] version Version value.
         * @return `true` if the versions are equal.
         * @return `false` if the versions are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(Version version) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] version Version value.
         * @return `true` if the versions are not equal.
         * @return `false` if the versions are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(Enum version) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] version Version value.
         * @return `true` if the versions are not equal.
         * @return `false` if the versions are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(Version version) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~Version() noexcept = default;

        /** @} */

        /**
         * @name Static properties.
         */
        /** @{ */
        /**
         * @brief Version values.
         * @details Contains all the version values.
         */
        static const std::array<Version, static_cast<std::size_t>(5)> Versions;

        /**
         * @brief Highest supported version.
         * @details The highest supported version.
         */
        static const Version::Enum HighestSupportedVersion;

        /** @} */

        /**
         * @name Friends.
         */
        /** @{ */
        friend bool operator==(Enum version, Version instance) noexcept;

        friend bool operator!=(Enum version, Version instance) noexcept;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/impl/version.ipp"

#endif // CRONZ_HTTP_VERSION_HPP
