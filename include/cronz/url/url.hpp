/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_URL_HPP
#define CRONZ_URL_URL_HPP 1

#include "cronz/url/authority.hpp"
#include "cronz/url/fragment.hpp"
#include "cronz/url/path.hpp"
#include "cronz/url/query.hpp"
#include "cronz/url/scheme.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url
     * @brief URL parser/builder.
     * @class URL
     * @remark Follows the standards defined by [RFC3986](https://www.rfc-editor.org/rfc/rfc3986).
     */
    class URL {
        // Properties.
        inline static constexpr auto SchemeSeparator = "://";
        inline static constexpr auto SchemeSeparatorLength = std::strlen(SchemeSeparator);

        // Parsing.
        CRONZ_NODISCARD_L1 bool parseScheme_(const char *&beg, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool parseAuthority_(const char *&beg, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool parsePath_(const char *&beg, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool parseQuery_(const char *&beg, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool parseFragment_(const char *&beg, const char *end) noexcept;

    public:
        /**
         * @name Components.
         */
        /** @{ */
        /**
         * @brief URL scheme.
         * @sa Scheme
         */
        Scheme scheme;

        /**
         * @brief URL authority (user info, host, port).
         * @sa Authority
         */
        Authority authority;

        /**
         * @brief URL path.
         * @sa Path
         * @sa PathManager
         */
        PathManager path;

        /**
         * @brief URL query (search part).
         * @sa QueryField
         * @sa QueryManager
         */
        QueryManager query;

        /**
         * @brief URL fragment.
         * @sa Fragment
         */
        Fragment fragment;
        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        URL() noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str String to be parsed.
         * @remark This function internally calls `parse`.
         * @sa parse
         */
        URL(const char *str) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @remark This function internally calls `parse`.
         * @sa parse
         */
        URL(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str String to be parsed.
         * @remark This function internally calls `parse`.
         * @sa parse
         */
        URL(const std::string &str) noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses a URL.
         * @param[in] str URL string.
         * @return `true` if `url` is successfully parsed, otherwise, `false`.
         * @remark This function does not require `str` to have all the URL components (i.e., scheme, authority, path,
         * query, fragment). Parsing can start/continue from any component.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str) noexcept;

        /**
         * @brief Parses a URL.
         * @param[in] str URL string.
         * @param[in] length Length of the URL string.
         * @return `true` if `url` is successfully parsed, otherwise, `false`.
         * @remark This function does not require `str` to have all the URL components (i.e., scheme, authority, path,
         * query, fragment). Parsing can start/continue from any component.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses a URL.
         * @param[in] str URL string.
         * @return `true` if `url` is successfully parsed, otherwise, `false`.
         * @remark This function does not require `str` to have all the URL components (i.e., scheme, authority, path,
         * query, fragment). Parsing can start/continue from any component.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /**
         * @brief Stringifies the URL.
         * @return Stringification result. Upon failure, this will be an empty string.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the URL.
         * @param[out] str Stringification result.
         * @return `true` if stringification is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the URL.
         * @param[out] str Stringification result.
         * @param[in] offset Where to start writing in `str`.
         * @return `true` if stringification is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Calculates the output length of the stringified URL.
         * @return The output length of the stringified URL.
         * @remark Returned number indicates the length of the encoded output.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells whether all the components of the URL are empty.
         * @return `true` if all the components of the URL are empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears all the components of the URL.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        ~URL() noexcept;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 static URL Parse(const char *str) noexcept;

        CRONZ_NODISCARD_L1 static URL Parse(const char *str, const std::size_t &length) noexcept;

        CRONZ_NODISCARD_L1 static URL Parse(const std::string &str) noexcept;

        CRONZ_NODISCARD_L2 static bool Parse(const char *str, URL &url) noexcept;

        CRONZ_NODISCARD_L2 static bool Parse(const char *str, const std::size_t &length, URL &url) noexcept;

        CRONZ_NODISCARD_L2 static bool Parse(const std::string &str, URL &url) noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/impl/url.ipp"

#endif // CRONZ_URL_URL_HPP
