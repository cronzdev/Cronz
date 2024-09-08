/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_IMPL_HOST_IPP
#define CRONZ_URL_AUTHORITY_IMPL_HOST_IPP 1

#include "cronz/url/authority/host.hpp"
#include "cronz/ip/address/v4.hpp"
#include "cronz/ip/address/v6.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    // Constructors.
    inline Host::Host() noexcept = default;

    inline Host::Host(const IP::IPv4Address &address) noexcept {
        [[maybe_unused]] const bool _ = assign(address);
    }

    inline Host::Host(const IP::IPv6Address &address) noexcept {
        [[maybe_unused]] const bool _ = assign(address);
    }

    inline Host::Host(const char *str) noexcept {
        [[maybe_unused]] const bool _ = assign(str);
    }

    inline Host::Host(const char *str, const std::size_t &length) noexcept {
        [[maybe_unused]] const bool _ = assign(str, length);
    }

    inline Host::Host(const std::string &str) noexcept {
        [[maybe_unused]] const bool _ = assign(str);
    }

    // Properties.
    inline bool Host::isIPv4() const noexcept {
        return IPv4 == type_;
    }

    inline bool Host::isIPv6() const noexcept {
        return IPv6 == type_;
    }

    inline bool Host::isRegisteredName() const noexcept {
        return Name == type_;
    }

    // Assignment & Parsing.
    inline bool Host::validateLabel_(const char *label, const std::size_t &length) noexcept {
        return static_cast<std::size_t>(0) < length && length <= static_cast<std::size_t>(63) &&
                ('-' != label[0] && !('0' <= label[0] && label[0] <= '9')) &&
                '-' != label[length - static_cast<std::size_t>(1)] &&
                std::ranges::all_of(label, label + length, [](const char &c) -> bool {
                    return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || '-' == c;
                });
    }

    inline bool Host::assign(const IP::IPv4Address &address) noexcept {
        if (address.stringify(value_)) {
            type_ = IPv4;
            return true;
        }

        clear();
        return false;
    }

    inline bool Host::assign(const IP::IPv6Address &address) noexcept {
        if (address.stringify<true>(value_)) {
            type_ = IPv6;
            return true;
        }

        clear();
        return false;
    }

    inline bool Host::assign(const char *str) noexcept {
        return assign(str, std::strlen(str));
    }

    inline bool Host::assign(const char *str, const std::size_t &length) noexcept {
        return parse(str, length);
    }

    inline bool Host::assign(const std::string &str) noexcept {
        return assign(str.c_str(), str.length());
    }

    inline bool Host::parse(const char *str) noexcept {
        return parse(str, std::strlen(str));
    }

    inline bool Host::parse(const char *str, const std::size_t &length) noexcept {
        if (nullptr == str || static_cast<std::size_t>(0) == length || static_cast<std::size_t>(255) < length) {
            clear();
            return false;
        }

        if ('[' == str[0] && str[length - static_cast<std::size_t>(1)] == ']') {
            IP::IPv6Address address;
            return address.parse(str + static_cast<std::size_t>(1), length - static_cast<std::size_t>(2)) &&
                    assign(address);
        }

        if ('0' <= str[0] && str[0] <= '9') {
            if (IP::IPv4Address address; address.parse(str, length))
                return assign(address);
        }

        const char *const end = str + length;
        const char *previous = str;
        while (previous < end) {
            const char *const label = std::ranges::find(previous, end, '.');
            if (!validateLabel_(previous, label - previous))
                goto bad;

            previous = label + static_cast<std::size_t>(1);
        }

        try {
            value_.resize(length);
        }
        catch (...) {
            goto bad;
        }

        memcpy(value_.data(), str, length);
        for (char &c : value_)
            c = ('A' <= c && c <= 'Z') ? static_cast<char>(c + ' ') : c;

        type_ = Name;

        return true;

    bad:
        clear();

        return false;
    }

    inline bool Host::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    // Stringification.
    inline std::size_t Host::length() const noexcept {
        return value_.length();
    }

    inline std::string Host::stringify() const noexcept {
        return value_;
    }

    inline bool Host::stringify(std::string &str) const noexcept {
        try {
            str.assign(value_);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    inline bool Host::stringify(std::string &str, const std::size_t &offset) const noexcept {
        if (const std::size_t len = length() + offset; len > str.length()) {
            try {
                str.resize(len);
            }
            catch (...) {
                return false;
            }
        }

        memcpy(&str[offset], value_.data(), value_.length());

        return true;
    }

    // Instance-based utility functions.
    inline bool Host::empty() const noexcept {
        return None == type_;
    }

    inline void Host::clear() noexcept {
        value_.clear();
        type_ = None;
    }

    // Operators.
    inline Host::operator bool() const noexcept {
        return !empty();
    }

    inline Host& Host::operator=(const IP::IPv4Address &address) noexcept {
        [[maybe_unused]] const bool _ = assign(address);
        return *this;
    }

    inline Host& Host::operator=(const IP::IPv6Address &address) noexcept {
        [[maybe_unused]] const bool _ = assign(address);
        return *this;
    }

    inline Host& Host::operator=(const char *str) noexcept {
        [[maybe_unused]] const bool _ = assign(str);
        return *this;
    }

    inline Host& Host::operator=(const std::string &str) noexcept {
        [[maybe_unused]] const bool _ = assign(str);
        return *this;
    }

    // Destructors.
    inline Host::~Host() noexcept = default;

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_AUTHORITY_IMPL_HOST_IPP
