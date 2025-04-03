/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_URI_HPP
#define CRONZ_URI_URI_HPP 1

#include "cronz/uri/authority.hpp"
#include "cronz/uri/fragment.hpp"
#include "cronz/uri/path.hpp"
#include "cronz/uri/query.hpp"
#include "cronz/uri/scheme.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief URI parsing and stringification class.
     * @class URI
     */
    class URI final {
        // Parsing & Stringification.
        CRONZ_NODISCARD_L1 bool _scheme(const char *&pos, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool _authority(const char *&pos, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool _path(const char *&pos, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool _query(const char *&pos, const char *end) noexcept;

        CRONZ_NODISCARD_L1 bool _fragment(const char *&pos, const char *end) noexcept;

    public:
        /**
         * @name Components.
         */
        /** @{ */
        /**
         * @brief URI scheme component.
         */
        Scheme scheme;

        /**
         * @brief URI authority component.
         */
        Authority authority;

        /**
         * @brief URI path component.
         */
        Path path;

        /**
         * @brief URI query component.
         */
        QueryManager query;

        /**
         * @brief URI fragment component.
         */
        Fragment fragment;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        URI() noexcept = default;

        /** @{ */

        /**
         * @name Properties.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses a URI from a string.
         * @param[in] str String to parse.
         * @return `true` if the URI is successfully parsed.
         * @return `false` if the URI is not successfully parsed.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view str) noexcept;

        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Tells whether all the components of the URI are empty.
         * @return `true` if all the components of the URI are empty.
         * @return `false` if any of the components of the URI are not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears all the components of the URI.
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
        ~URI() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/impl/uri.ipp"

#endif // CRONZ_URI_URI_HPP
