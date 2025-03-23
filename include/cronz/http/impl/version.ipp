/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_IMPL_VERSION_IPP
#define CRONZ_HTTP_IMPL_VERSION_IPP 1

#include "cronz/http/version.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Constructors.
    inline Version::Version() noexcept : value(Invalid) {
    }

    inline Version::Version(const Enum version) noexcept : value(version) {
    }

    // Instance-based utility functions.
    inline Version::Enum Version::_parse(const std::string_view str) noexcept {
        if ((static_cast<std::size_t>(6) != str.length() && static_cast<std::size_t>(8) != str.length()) ||
            'H' != str[0] || 'T' != str[1] || 'T' != str[2] || 'P' != str[3] || '/' != str[4])
            return Invalid;

        if (static_cast<std::size_t>(8) == str.length()) {
            if ('.' != str[6])
                return Invalid;

            if ('0' == str[5] && '9' == str[7])
                return HTTP_0_9;

            if ('1' == str[5]) {
                if ('0' == str[7])
                    return HTTP_1_0;

                if ('1' == str[7])
                    return HTTP_1_1;
            }

            return Invalid;
        }

        if ('2' == str[5])
            return HTTP_2;

        if ('3' == str[5])
            return HTTP_3;

        return Invalid;
    }

    inline bool Version::parse(const std::string_view version) noexcept {
        value = _parse(version);
        return Invalid != value;
    }

    inline std::string Version::stringify() const noexcept {
        std::string str;
        return stringify(str, static_cast<std::size_t>(0)) ? str : std::string();
    }

    inline bool Version::stringify(std::string &str, const std::size_t offset) const noexcept {
        if (Invalid == value)
            return false;

        const std::string_view &s = _strings.at(value);

        if (const std::size_t len = (s.length() + offset);
            len > str.length()) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        memcpy(str.data() + offset, s.data(), s.length());
        return true;
    }

    inline std::size_t Version::length() const noexcept {
        return Invalid != value ? _strings.at(value).length() : static_cast<std::size_t>(0);
    }

    // Operators.
    inline Version::operator bool() const noexcept {
        return Invalid != value;
    }

    inline Version &Version::operator=(const Enum version) noexcept {
        value = version;
        return *this;
    }

    inline bool Version::operator==(const Enum version) const noexcept {
        return value == version;
    }

    inline bool Version::operator==(const Version version) const noexcept {
        return value == version.value;
    }

    inline bool Version::operator!=(const Enum version) const noexcept {
        return value != version;
    }

    inline bool Version::operator!=(const Version version) const noexcept {
        return value != version.value;
    }

    // Static properties.
    inline const std::unordered_map<Version::Enum, std::string_view> Version::_strings = {
        {HTTP_0_9, "HTTP/0.9"},
        {HTTP_1_0, "HTTP/1.0"},
        {HTTP_1_1, "HTTP/1.1"},
        {HTTP_2, "HTTP/2"},
        {HTTP_3, "HTTP/3"}
    };

    inline const std::array<Version, static_cast<std::size_t>(5)> Version::Versions = {
        Version(HTTP_0_9),
        Version(HTTP_1_0),
        Version(HTTP_1_1),
        Version(HTTP_2),
        Version(HTTP_3)
    };

    inline const Version::Enum Version::HighestSupportedVersion = Version::Enum::HTTP_1_1;

    // Friends.
    inline bool operator==(const Version::Enum version, const Version instance) noexcept {
        return version == instance.value;
    }

    inline bool operator!=(const Version::Enum version, const Version instance) noexcept {
        return version != instance.value;
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_IMPL_VERSION_IPP
