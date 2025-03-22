/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_URL_HPP
#define CRONZ_URI_URL_HPP 1

#include "cronz/uri/scheme.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    class URL {
        // Static constants.
        inline static constexpr std::string_view SchemeSeparator = "://";

        // Parsing & Stringification.
        CRONZ_NODISCARD_L1 bool _schema(const char *&pos, const char * end) noexcept;

    public:
        /**
         * @name Components.
         */
        /** @{ */
        /**
         * @brief URL scheme.
         */
        Scheme scheme;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        URL() noexcept = default;

        /** @{ */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses a URL from a string.
         * @param[in] str String to parse.
         * @return `true` if the URL is successfully parsed.
         * @return `false` if the URL is not successfully parsed.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view str) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Tells whether all the components of the URL are empty.
         * @return `true` if all the components of the URL are empty.
         * @return `false` if any of the components of the URL are not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears all the components of the URL.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~URL() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/impl/url.ipp"

#endif // CRONZ_URI_URL_HPP
