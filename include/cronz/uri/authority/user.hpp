/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_USER_USER_HPP
#define CRONZ_URI_USER_USER_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief User information component.
     * @class UserInformation
     */
    class UserInformation final {
        // Properties.
        std::string _user;
        std::string _password;

        CRONZ_NODISCARD_L1 static bool _assign(std::string_view value, std::string &component) noexcept;

        // Static utility functions.
        CRONZ_NODISCARD_L1 static bool _test(std::string_view str) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        UserInformation() noexcept = default;

        /**
         * @brief Constructor with user and password.
         * @param[in] user User.
         * @param[in] password Password.
         * @remark If user or password is not successfully assigned, the user information will be empty.
         */
        UserInformation(std::string_view user, std::string_view password) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Get user.
         * @return User.
         */
        CRONZ_NODISCARD_L1 std::string_view user() const noexcept;

        /**
         * @brief Set user.
         * @param[in] user User.
         * @return `true` if user is successfully assigned.
         * @return `false` if user is not successfully assigned.
         */
        CRONZ_NODISCARD_L2 bool user(std::string_view user) noexcept;

        /**
         * @brief Get user.
         * @return User.
         */
        CRONZ_NODISCARD_L1 std::string_view getUser() const noexcept;

        /**
         * @brief Set user.
         * @param[in] user User.
         * @return `true` if user is successfully assigned.
         * @return `false` if user is not successfully assigned.
         */
        CRONZ_NODISCARD_L2 bool setUser(std::string_view user) noexcept;

        /**
         * @brief Get password.
         * @return Password.
         */
        CRONZ_NODISCARD_L1 std::string_view password() const noexcept;

        /**
         * @brief Set password.
         * @param[in] password Password.
         * @return `true` if password is successfully assigned.
         * @return `false` if password is not successfully assigned.
         */
        CRONZ_NODISCARD_L2 bool password(std::string_view password) noexcept;

        /**
         * @brief Get password.
         * @return Password.
         */
        CRONZ_NODISCARD_L1 std::string_view getPassword() const noexcept;

        /**
         * @brief Set password.
         * @param[in] password Password.
         * @return `true` if password is successfully assigned.
         * @return `false` if password is not successfully assigned.
         */
        CRONZ_NODISCARD_L2 bool setPassword(std::string_view password) noexcept;

        /**
         * @brief Get the length of the user information.
         * @return Length of the user information.
         * @remark Both user and password will be URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::size_t length(bool includePassword = false) const noexcept;

        /**
         * @brief Tells whether the user information is empty.
         * @return `true` if the user information is empty.
         * @return `false` if the user information is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the user information.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses user information from a string.
         * @param[in] str String to parse.
         * @return `true` if the user information is successfully parsed.
         * @return `false` if the user information is not successfully parsed.
         * @remark Both user and password will be URI-decoded.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view str) noexcept;

        /**
         * @brief Stringifies the user information.
         * @param[in] includePassword Whether to include the password.
         * @return Stringified user information.
         * @remark Both user and password will be URI-encoded.
         */
        CRONZ_NODISCARD_L1 std::string stringify(bool includePassword = false) const noexcept;

        /**
         * @brief Stringifies the user information.
         * @param[out] str Stringified user information.
         * @param[in] includePassword Whether to include the password.
         * @return `true` if the user information is successfully stringified.
         * @return `false` if the user information is not successfully stringified.
         * @remark Both user and password will be URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, bool includePassword = false) const noexcept;

        /**
         * @brief Stringifies the user information.
         * @param[out] str Stringified user information.
         * @param[in, out] offset Offset to start from.
         * @param[in] includePassword Whether to include the password.
         * @return `true` if the user information is successfully stringified.
         * @return `false` if the user information is not successfully stringified.
         * @remark The offset will be updated to the next position after the stringified user information.
         * @remark Both user and password will be URI-encoded.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset, bool includePassword) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Conversion operator to `bool`.
         * @return `true` if the user information is not empty.
         * @return `false` if the user information is empty.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~UserInformation() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/authority/impl/user.ipp"

#endif // CRONZ_URI_USER_USER_HPP
