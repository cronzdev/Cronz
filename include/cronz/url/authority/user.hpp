/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_USER_HPP
#define CRONZ_URL_AUTHORITY_USER_HPP 1

#include "cronz/crypto/hex.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    class UserInformation {
        // Properties.
        std::string user_;
        std::string password_;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        UserInformation() noexcept;

        /** @} */

        /**
         * @name Name.
         */
        /** @{ */
        /**
         * @brief Returns mutable reference to the user.
         * @return Mutable reference to the user.
         */
        CRONZ_NODISCARD_L1 std::string& getUser() noexcept;

        /**
         * @brief Returns read-only reference to the user.
         * @return Read-only reference to the user.
         */
        CRONZ_NODISCARD_L1 const std::string& getUser() const noexcept;

        /**
         * @brief Sets the user field.
         * @param[in] user New user value.
         * @return `true` if assignment is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool setUser(const std::string &user) noexcept;

        /**
         * @brief Sets the user field.
         * @param[in] user New user value.
         * @param[in] length Length of the user value.
         * @return `true` if assignment is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool setUser(const char *user, const std::size_t &length) noexcept;

        /**
         * @brief Clears the user field.
         */
        void clearUser() noexcept;

        /** @} */

        /**
         * @name Password.
         */
        /** @{ */
        /**
         * @brief Returns mutable reference to the password.
         * @return Mutable reference to the password.
         */
        CRONZ_NODISCARD_L1 std::string& getPassword() noexcept;

        /**
         * @brief Returns read-only reference to the password.
         * @return Read-only reference to the password.
         */
        CRONZ_NODISCARD_L1 const std::string& getPassword() const noexcept;

        /**
         * @brief Sets the password field.
         * @param[in] password New password value.
         * @return `true` if assignment is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool setPassword(const std::string &password) noexcept;

        /**
         * @brief Sets the password field.
         * @param[in] password New password value.
         * @param[in] length Length of the password value.
         * @return `true` if assignment is successfully done, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool setPassword(const char *password, const std::size_t &length) noexcept;

        /**
         * @brief Clears the password field.
         */
        void clearPassword() noexcept;

        /** @} */

        /**
         * @name Parsing.
         */
        /** @{ */
        /**
         * @brief Parses user info string.
         * @param[in] str String to be parsed.
         * @return `true` if operation was successful, otherwise, `false`.
         * @remark Upon failure, existing values are not altered.
         * @remark This function overwrites the existing values.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /**
         * @brief Parses user info string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @return `true` if operation was successful, otherwise, `false`.
         * @remark Upon failure, existing values are not altered.
         * @remark This function overwrites the existing values.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Calculates the length of the encoded value.
         * @param[in] includePassword Whether to include password.
         * @return The length of the encoded value.
         */
        CRONZ_NODISCARD_L1 std::size_t length(const bool &includePassword) const noexcept;

        /**
         * @brief Calculates the length of the encoded value.
         * @tparam IncludePassword Whether to include password.
         * @return The length of the encoded value.
         */
        template <bool IncludePassword = false>
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells whether both the user and the password fields are empty.
         * @return Whether both the user and the password fields are empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears both the user and the password fields.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Conversion.
         */
        /** @{ */
        /**
         * @brief Encodes and converts field to a string.
         * @param[in] includePassword Whether to include password.
         * @return Stringification result. Upon failure, this will be an empty string.
         */
        CRONZ_NODISCARD_L1 std::string stringify(const bool &includePassword = false) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @tparam IncludePassword Whether to include password.
         * @return Stringification result. Upon failure, this will be an empty string.
         */
        template <bool IncludePassword>
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @tparam IncludePassword Whether to include password.
         * @param[out] str Stringification result.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        template <bool IncludePassword>
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @param[out] str Stringification result.
         * @param[in] includePassword Whether to include password.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const bool &includePassword) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @tparam IncludePassword Whether to include password.
         * @param[out] str Stringification result.
         * @param[in] offset Where to start writing in `str`.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        template <bool IncludePassword>
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @param[out] str Stringification result.
         * @param[in] offset Where to start writing in `str`.
         * @param[in] includePassword Whether to include password.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset,
                                          const bool &includePassword) const noexcept;

        /**
         * @brief Encodes and converts field to a string.
         * @param[out] str Stringification result.
         * @param[in] includePassword Whether to include password.
         * @param[in] offset Where to start writing in `str`.
         * @return `true` if stringification was successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const bool &includePassword,
                                          const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells whether the container is empty.
         * @return `true` if the container is empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~UserInformation() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/authority/impl/user.ipp"

#endif // CRONZ_URL_AUTHORITY_USER_HPP
