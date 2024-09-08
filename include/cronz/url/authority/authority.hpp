/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_AUTHORITY_HPP
#define CRONZ_URL_AUTHORITY_AUTHORITY_HPP 1

#include "cronz/url/authority/host.hpp"
#include "cronz/url/authority/port.hpp"
#include "cronz/url/authority/user.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_authority
     * @brief Authority container (user information, host, port).
     * @class Authority
     */
    class Authority {
    public:
        /**
         * @name Components.
         */
        /** @{ */
        /**
         * @brief User information component.
         */
        UserInformation userInformation{};

        /**
         * @brief Host component.
         */
        Host host{};

        /**
         * @brief Port component.
         */
        Port port = static_cast<Port>(0);
        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @name Default constructor. Does nothing.
         */
        Authority() noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Tells the length of the string representation.
         * @return Length of the string representation.
         * @warning If host is empty, this returns `0`.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses the authority component.
         * @param[in] str String to be parsed.
         * @return `true` if successfully parsed, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool parse(const char *str) noexcept;

        /**
         * @brief Parses the authority component.
         * @param[in] str String to be parsed.
         * @param[in] length Length of `str`.
         * @return `true` if successfully parsed, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses the authority component.
         * @param[in] str String to be parsed.
         * @return `true` if successfully parsed, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool parse(const std::string &str) noexcept;

        /**
         * @brief Returns the string representation of authority components.
         * @return String representation of authority components.
         * @remark Upon failure, the returned string will be empty.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Overwrites the string representation to the passed string container.
         * @param[out] str Output.
         * @return `true` if stringification is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Overwrites the string representation to the passed string container starting from the given position.
         * @param[out] str Output.
         * @param[out] offset Output position.
         * @return `true` if stringification is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Tells whether all the components are empty.
         * @return `true` if all the components are empty, otherwise, `false`.
         * @warning If host is empty, this returns `true`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears all the components.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells whether all the components are empty.
         * @return `true` if all the components are empty, otherwise, `false`.
         * @warning If host is empty, this returns `true`.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /** @{ */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~Authority() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/authority/impl/authority.ipp"

#endif // CRONZ_URL_AUTHORITY_AUTHORITY_HPP
