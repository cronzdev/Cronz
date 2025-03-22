/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_SCHEME_HPP
#define CRONZ_URL_SCHEME_HPP 1

#include "cronz/url/types.hpp"

CRONZ_BEGIN_URL_NAMESPACE
    class URLScheme {
        // Properties.
        std::string _value{};

        // Static utility functions.
        CRONZ_NODISCARD_L1 bool _compare(std::string_view scheme) const noexcept;

    public:
        /**
         * @name Static constants.
         */
        /** @{ */
        /**
         * @brief `file`.
         */
        inline static constexpr std::string_view FILE = "file";
        /**
         * @brief `ftp`.
         */
        inline static constexpr std::string_view FTP = "ftp";
        /**
         * @brief `sftp`.
         */
        inline static constexpr std::string_view SFTP = "sftp";
        /**
         * @brief `http`.
         */
        inline static constexpr std::string_view HTTP = "http";
        /**
         * @brief `https`.
         */
        inline static constexpr std::string_view HTTPS = "https";
        /**
         * @brief `mailto`.
         */
        inline static constexpr std::string_view MAILTO = "mailto";
        /**
         * @brief `tel`.
         */
        inline static constexpr std::string_view TEL = "tel";

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        URLScheme() noexcept = default;

        /**
         * @brief Constructor with a scheme.
         * @param[in] scheme Scheme.
         */
        explicit(false) URLScheme(std::string_view scheme) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Get the scheme.
         * @return Scheme.
         */
        CRONZ_NODISCARD_L1 std::string_view get() const noexcept;

        /**
         * @brief Set the scheme.
         * @param[in] scheme Scheme.
         * @return `true` if the scheme is set successfully.
         * @return `false` if the scheme is not set successfully.
         * @remark The scheme is converted to lowercase if it contains uppercase characters.
         * @remark Upon failure, the existing scheme is not modified.
         */
        CRONZ_NODISCARD_L2 bool set(std::string_view scheme) noexcept;

        /**
         * @brief Get the length of the scheme.
         * @return Length of the scheme.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Check if the scheme is empty.
         * @return `true` if the scheme is empty.
         * @return `false` if the scheme is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clear the scheme.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Stringification.
         */
        /** @{ */
        /**
         * @brief Stringify the scheme.
         * @return Scheme.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringify the scheme.
         * @param[out] scheme Scheme.
         * @return `true` if the scheme is stringified successfully.
         * @return `false` if the scheme is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &scheme) const noexcept;

        /**
         * @brief Stringify the scheme.
         * @param[out] scheme Scheme.
         * @param[out] offset Offset. The offset is incremented by the length of the scheme.
         * @return `true` if the scheme is stringified successfully.
         * @return `false` if the scheme is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &scheme, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Conversion to `bool`.
         * @return `true` if the scheme is not empty.
         * @return `false` if the scheme is empty.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Conversion to `std::string_view`.
         * @return Scheme.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::string_view() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] scheme Scheme.
         * @return Reference to the scheme.
         */
        URLScheme &operator=(std::string_view scheme) noexcept;

        /**
         * @brief Equality operator.
         * @param[in] scheme Scheme.
         * @return `true` if the schemes are equal.
         * @return `false` if the schemes are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(std::string_view scheme) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] scheme Scheme.
         * @return `true` if the schemes are equal.
         * @return `false` if the schemes are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(const URLScheme &scheme) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] scheme Scheme.
         * @return `true` if the schemes are not equal.
         * @return `false` if the schemes are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(std::string_view scheme) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] scheme Scheme.
         * @return `true` if the schemes are not equal.
         * @return `false` if the schemes are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const URLScheme &scheme) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~URLScheme() noexcept = default;

        /** @} */

        /**
         * @name Friends.
         */
        /** @{ */
        /**
         * @brief Equality operator.
         * @param[in] scheme Scheme.
         * @param[in] instance Instance.
         * @return `true` if the schemes are equal.
         * @return `false` if the schemes are not equal.
         */
        friend bool operator==(std::string_view scheme, const URLScheme &instance) noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] scheme Scheme.
         * @param[in] instance Instance.
         * @return `true` if the schemes are not equal.
         * @return `false` if the schemes are equal.
         */
        friend bool operator!=(std::string_view scheme, const URLScheme &instance) noexcept;

        /** @} */
    };

CRONZ_END_URL_NAMESPACE

#include "cronz/url/impl/scheme.ipp"

#endif // CRONZ_URL_SCHEME_HPP
