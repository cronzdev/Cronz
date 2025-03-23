/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_AUTHORITY_AUTHORITY_HPP
#define CRONZ_URI_AUTHORITY_AUTHORITY_HPP 1

#include "cronz/uri/authority/host.hpp"
#include "cronz/uri/authority/port.hpp"
#include "cronz/uri/authority/user.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief The `Authority` class represents the authority component of a URI.
     * @class Authority
     */
    class Authority final {
    public:
        /**
         * @name Components.
         */
        /** @{ */
        /**
         * @brief User information component.
         */
        UserInformation userInformation;

        /**
         * @brief Host component.
         */
        Host host;

        /**
         * @brief Port component.
         */
        Port port = InvalidPort;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Authority() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the length of the authority.
         * @param[in] includePassword Whether to include the password in the user information.
         * @return Length of the authority.
         */
        CRONZ_NODISCARD_L1 std::size_t length(bool includePassword = false) const noexcept;

        /**
         * @brief Tells whether the authority is empty.
         * @return `true` if the authority is empty.
         * @return `false` if the authority is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the authority.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses the authority from a string.
         * @param[in] authority Authority string.
         * @return `true` if the authority is parsed successfully.
         * @return `false` if the authority is not parsed successfully.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view authority) noexcept;

        /**
         * @brief Returns the authority as a string.
         * @param[in] includePassword Whether to include the password in the user information.
         * @return Authority as a string.
         */
        CRONZ_NODISCARD_L1 std::string stringify(bool includePassword = false) const noexcept;

        /**
         * @brief Returns the authority as a string.
         * @param[out] str Output string.
         * @param[in] includePassword Whether to include the password in the user information.
         * @return `true` if the authority is stringified successfully.
         * @return `false` if the authority is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, bool includePassword = false) const noexcept;

        /**
         * @brief Returns the authority as a string.
         * @param[out] str Output string.
         * @param[in, out] offset Offset.
         * @param[in] includePassword Whether to include the password in the user information.
         * @return `true` if the authority is stringified successfully.
         * @return `false` if the authority is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset,
                                          bool includePassword = false) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Conversion operator to `bool`.
         * @return `true` if the authority is not empty.
         * @return `false` if the authority is empty.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~Authority() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/authority/impl/authority.ipp"

#endif // CRONZ_URI_AUTHORITY_AUTHORITY_HPP
