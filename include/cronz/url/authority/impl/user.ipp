/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_IMPL_USER_IPP
#define CRONZ_URL_AUTHORITY_IMPL_USER_IPP 1

#include <cronz/url/decode.hpp>
#include <cronz/url/encode.hpp>

#include "cronz/url/authority/user.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline UserInformation::UserInformation() noexcept = default;

    // Name.
    inline std::string& UserInformation::getUser() noexcept {
        return user_;
    }

    inline const std::string& UserInformation::getUser() const noexcept {
        return user_;
    }

    inline bool UserInformation::setUser(const std::string &user) noexcept {
        return setUser(user.c_str(), user.length());
    }

    inline bool UserInformation::setUser(const char *user, const std::size_t &length) noexcept {
        try {
            user_.assign(user, length);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    inline void UserInformation::clearUser() noexcept {
        user_.clear();
    }

    // Password.
    inline std::string& UserInformation::getPassword() noexcept {
        return password_;
    }

    inline const std::string& UserInformation::getPassword() const noexcept {
        return password_;
    }

    inline bool UserInformation::setPassword(const std::string &password) noexcept {
        return setPassword(password.c_str(), password.length());
    }

    inline bool UserInformation::setPassword(const char *password, const std::size_t &length) noexcept {
        try {
            password_.assign(password, length);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    inline void UserInformation::clearPassword() noexcept {
        password_.clear();
    }

    // Parsing.
    inline bool UserInformation::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline bool UserInformation::parse(const char *str, const std::size_t &length) noexcept {
        const char *const end = str + length;

        std::string user;
        std::string password;

        const char *separator = std::ranges::find(str, end, ':');

        if (!Decode(str, separator - str, user))
            return false;

        if (end != separator) {
            ++separator;

            if (!Decode(separator, end - separator, password))
                return false;
        }

        user_.swap(user);
        password_.swap(password);

        return true;
    }

    // Properties.
    inline std::size_t UserInformation::length(const bool &includePassword) const noexcept {
        return includePassword ? length<true>() : length<false>();
    }

    template <bool IncludePassword>
    inline std::size_t UserInformation::length() const noexcept {
        if constexpr (IncludePassword)
            return CalculateEncodedLength(user_) + CalculateEncodedLength(password_) + static_cast<std::size_t>(1);
        else
            return CalculateEncodedLength(user_);
    }

    inline bool UserInformation::empty() const noexcept {
        return user_.empty() && password_.empty();
    }

    inline void UserInformation::clear() noexcept {
        clearUser();
        clearPassword();
    }

    // Conversion.
    inline std::string UserInformation::stringify(const bool &includePassword) const noexcept {
        return includePassword ? stringify<true>() : stringify<false>();
    }

    template <bool IncludePassword>
    inline std::string UserInformation::stringify() const noexcept {
        std::string str;
        [[maybe_unused]] const bool _ = stringify<IncludePassword>(str);
        return str;
    }

    template <bool IncludePassword>
    inline bool UserInformation::stringify(std::string &str) const noexcept {
        return stringify<IncludePassword>(str, static_cast<std::size_t>(0));
    }

    inline bool UserInformation::stringify(std::string &str, const bool &includePassword) const noexcept {
        return includePassword ? stringify<true>(str) : stringify<false>(str);
    }

    template <bool IncludePassword>
    inline bool UserInformation::stringify(std::string &str, const std::size_t &offset) const noexcept {
        const std::size_t newLength = offset + length<IncludePassword>();

        try {
            str.resize(newLength);
        }
        catch (...) {
            return false;
        }

        std::size_t o = offset;
        o += Encode(user_, &str[o]);

        if constexpr (IncludePassword) {
            str[o++] = ':';
            [[maybe_unused]] const std::size_t _ = Encode(password_, &str[o]);
        }

        return true;
    }

    inline bool UserInformation::stringify(std::string &str, const std::size_t &offset,
                                           const bool &includePassword) const noexcept {
        return includePassword ? stringify<true>(str, offset) : stringify<false>(str, offset);
    }

    inline bool UserInformation::stringify(std::string &str, const bool &includePassword,
                                           const std::size_t &offset) const noexcept {
        return includePassword ? stringify<true>(str, offset) : stringify<false>(str, offset);
    }

    // Operators.
    inline UserInformation::operator bool() const noexcept {
        return !empty();
    }

    // Destructors.
    inline UserInformation::~UserInformation() = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_AUTHORITY_IMPL_USER_IPP
