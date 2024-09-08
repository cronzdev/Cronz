/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_SCHEME_HPP
#define CRONZ_URL_SCHEME_HPP 1

/**
 * @defgroup cronz_url_scheme Scheme
 * @ingroup cronz_url
 */

#include "cronz/url/types.hpp"

#include <string>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_scheme
     * @brief Scheme container.
     * @class Scheme
     * @remark This class follows the specifications from
     * [RFC3986 - Section 3.1](https://www.rfc-editor.org/rfc/rfc3986#section-3.1).
     */
    class Scheme {
        // Properties.
        std::string value_{};

    public:
        /**
         * @name Predefined scheme values.
         */
        /** @{ */
        /**
         * @brief `file`.
         */
        inline static constexpr std::string FILE = "file";
        /**
         * @brief `ftp`.
         */
        inline static constexpr std::string FTP = "ftp";
        /**
         * @brief `sftp`.
         */
        inline static constexpr std::string SFTP = "sftp";
        /**
         * @brief `http`.
         */
        inline static constexpr std::string HTTP = "http";
        /**
         * @brief `https`.
         */
        inline static constexpr std::string HTTPS = "https";
        /**
         * @brief `mailto`.
         */
        inline static constexpr std::string MAILTO = "mailto";
        /**
         * @brief `tel`.
         */
        inline static constexpr std::string TEL = "tel";
        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        Scheme() noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] value Scheme value.
         * @remark This internally calls `setValue` and ignores the output. There is no guarantee that the value will be
         * assigned as the scheme.
         */
        Scheme(const std::string &value) noexcept;

        /** @} */

        /**
         * @name Getters & Setters.
         */
        /** @{ */
        /**
         * @brief Returns a read-only reference to the value.
         * @return Read-only reference to the value.
         */
        CRONZ_NODISCARD_L1 const std::string& getValue() const noexcept;

        /**
         * @brief Sets the scheme value.
         * @param[in] value Scheme value.
         * @return `true` if `value` is successfully assigned, otherwise, `false`.
         * @remark This function validates the scheme format. If invalid, returns `false`.
         * @remark If `value` is empty, this function internally calls `clear`.
         */
        CRONZ_NODISCARD_L2 bool setValue(const char *value) noexcept;

        /**
         * @brief Sets the scheme value.
         * @param[in] value Scheme value.
         * @param[in] length Length of the scheme value.
         * @return `true` if `value` is successfully assigned, otherwise, `false`.
         * @remark This function validates the scheme format. If invalid, returns `false`.
         * @remark If `value` is empty, this function internally calls `clear`.
         */
        CRONZ_NODISCARD_L2 bool setValue(const char *value, const std::size_t &length) noexcept;

        /**
         * @brief Sets the scheme value.
         * @param[in] value Scheme value.
         * @return `true` if `value` is successfully assigned, otherwise, `false`.
         * @remark This function validates the scheme format. If invalid, returns `false`.
         * @remark If `value` is empty, this function internally calls `clear`.
         */
        CRONZ_NODISCARD_L2 bool setValue(const std::string &value) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the length of the scheme value.
         * @return Length of the scheme value.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells if the scheme value is empty.
         * @return `true` if the scheme value is empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the scheme value.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Stringification.
         */
        /** @{ */
        /**
         * @brief Returns string representation of the scheme.
         * @return String representation of the scheme.
         * @remark Since scheme does not require encoding or formatting, this is identical to calling `getValue`.
         * @sa getValue
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the scheme value.
         * @param[out] str Stringification output.
         * @return `true` if the value is successfully assigned to `str`, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the scheme value.
         * @param[out] str Stringification output.
         * @param[in] offset Position where the scheme will start.
         * @return `true` if the value is successfully assigned to `str`, otherwise, `false`.
         * @remark `str` is resized if total length (`offset + length`) is greater than its size.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells if the scheme value is empty.
         * @return `true` if the scheme value is empty, otherwise, `false`.
         * @remark This function internally calls `empty`.
         * @sa empty
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /**
         * @brief Returns a read-only reference to the value.
         * @return Read-only reference to the value.
         * @remark This function internally calls `getValue`.
         * @sa getValue
         */
        CRONZ_NODISCARD_L1 operator const std::string&() const noexcept;

        /**
         * @brief Sets the scheme value.
         * @param[in] value Scheme value.
         * @return Reference to the scheme container.
         * @remark This internally calls `setValue` and ignores the output. There is no guarantee that the value will be
         * assigned as the scheme.
         * @remark This function validates the scheme format. If invalid, returns `false`.
         * @remark If `value` is empty, this function internally calls `clear`.
         * @sa setValue
         */
        Scheme& operator=(const std::string &value) noexcept;

        /**
         * @brief Tells whether the current scheme's value equals to another scheme's.
         * @param[in] scheme Other scheme.
         * @return `true` if the two schemes' values match, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool operator==(const Scheme &scheme) const noexcept;

        /**
         * @brief Tells whether the current scheme's value equals to the passed string.
         * @param[in] scheme Scheme value.
         * @return `true`if the two values match, otherwise, `false`.
         * @remark This function is case-insensitive.
         */
        CRONZ_NODISCARD_L1 bool operator==(const std::string &scheme) const noexcept;

        /**
         * @brief Tells whether the current scheme's value is different from another scheme's.
         * @param[in] scheme Other scheme.
         * @return `true` if the two schemes' values differ, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const Scheme &scheme) const noexcept;

        /**
         * @brief Tells whether the current scheme's value differs from the passed string.
         * @param[in] scheme Scheme value.
         * @return `true`if the two values differ, otherwise, `false`.
         * @remark This function is case-insensitive.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const std::string &scheme) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        ~Scheme() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/impl/scheme.ipp"

#endif // CRONZ_URL_SCHEME_HPP
