/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_IMPL_V4_IPP
#define CRONZ_IP_ADDRESS_IMPL_V4_IPP 1

#include "cronz/ip/address/v4.hpp"

#include <algorithm>
#include <cstring>

CRONZ_BEGIN_MODULE_NAMESPACE(IP)
    // Constructors.
    inline IPv4Address::IPv4Address() noexcept : int32(static_cast<std::int32_t>(0)) {
    }

    inline IPv4Address::IPv4Address(const std::int32_t &int32) noexcept : int32(int32) {
    }

    inline IPv4Address::IPv4Address(const std::uint32_t &uint32) noexcept : uint32(uint32) {
    }

    inline IPv4Address::IPv4Address(const std::uint8_t &byte1, const std::uint8_t &byte2, const std::uint8_t &byte3,
                                    const std::uint8_t &byte4) noexcept : bytes{byte1, byte2, byte3, byte4} {
    }

    inline IPv4Address::IPv4Address(
            const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept : bytes(bytes) {
    }

    inline IPv4Address::IPv4Address(const std::bitset<static_cast<std::size_t>(32)> &bits) noexcept : bits(bits) {
    }

    inline IPv4Address::IPv4Address(const char *str) noexcept : IPv4Address(Parse(str)) {
    }

    inline IPv4Address::IPv4Address(const char *str, const std::size_t &length) noexcept : IPv4Address(
            Parse(str, length)) {
    }

    inline IPv4Address::IPv4Address(const std::string &str) noexcept : IPv4Address(Parse(str)) {
    }

    // Instance-based utility functions.
    inline bool IPv4Address::parse(const char *str) noexcept {
        return parse(str, std::strlen(str));
    }

    inline bool IPv4Address::parse(const char *str, const std::size_t &length) noexcept {
        if (static_cast<std::size_t>(7) > length || length > static_cast<std::size_t>(15))
            return false;

        uint32 = static_cast<std::uint32_t>(0);

        const char *const end = str + length;
        const char *previous = str;

        auto byteIndex = static_cast<std::size_t>(0);
        while (previous < end) {
            if (static_cast<std::size_t>(3) < byteIndex)
                return false;

            const char *const current = std::ranges::find(previous, end, '.');
            if (const auto byteLength = static_cast<std::size_t>(current - previous); static_cast<std::size_t>(0) ==
                byteLength || byteLength > static_cast<std::size_t>(3))
                return false;

            std::uint8_t &byte = bytes[byteIndex];
            while (previous < current) {
                if (const char c = *previous; '0' <= c && c <= '9') {
                    const auto digit = static_cast<std::uint8_t>(c - '0');
                    if (static_cast<std::uint8_t>(25) < byte || (static_cast<std::uint8_t>(25) == byte && static_cast<
                        std::uint8_t>(5) < digit))
                        return false;

                    byte = (byte * static_cast<std::uint8_t>(10)) + static_cast<std::uint8_t>(digit);
                }
                else {
                    return false;
                }

                ++previous;
            }

            ++previous;
            ++byteIndex;
        }

        return static_cast<std::size_t>(4) == byteIndex;
    }

    inline bool IPv4Address::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    inline std::string IPv4Address::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            str.clear();

        return str;
    }

    inline bool IPv4Address::stringify(std::string &str) const noexcept {
        try {
            str.resize(length());
        }
        catch (...) {
            return false;
        }

        auto offset = static_cast<std::size_t>(0);
        for (std::uint8_t byte : bytes) {
            if (static_cast<std::size_t>(0) != offset)
                str[offset++] = '.';

            auto length = static_cast<std::size_t>(0);

            do {
                str[offset++] = static_cast<char>('0' + static_cast<char>(byte % static_cast<std::uint8_t>(10)));
                byte /= static_cast<std::uint8_t>(10);
                ++length;
            }
            while (static_cast<std::size_t>(0) != byte);

            if (static_cast<std::size_t>(2) == length)
                std::swap(str[offset - static_cast<std::size_t>(1)], str[offset - static_cast<std::size_t>(2)]);
            else if (static_cast<std::size_t>(3) == length)
                std::swap(str[offset - static_cast<std::size_t>(1)], str[offset - static_cast<std::size_t>(3)]);
        }

        return true;
    }

    inline std::size_t IPv4Address::length() const noexcept {
        auto length = static_cast<std::size_t>(7);

        for (std::uint8_t byte : bytes) {
            while (static_cast<std::uint8_t>(9) < byte) {
                byte /= static_cast<std::uint8_t>(10);
                ++length;
            }
        }

        return length;
    }

    inline void IPv4Address::reset() noexcept {
        this->uint32 = static_cast<std::uint32_t>(0);
    }

    // Operators.
    inline IPv4Address::operator bool() const noexcept {
        return static_cast<std::uint32_t>(0) != uint32;
    }

    inline IPv4Address& IPv4Address::operator=(const std::int32_t &int32) noexcept {
        this->int32 = int32;
        return *this;
    }

    inline IPv4Address& IPv4Address::operator=(const std::uint32_t &uint32) noexcept {
        this->uint32 = uint32;
        return *this;
    }

    inline IPv4Address& IPv4Address::operator=(
            const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept {
        this->bytes = bytes;
        return *this;
    }

    inline IPv4Address& IPv4Address::operator=(const std::bitset<static_cast<std::size_t>(32)> &bits) noexcept {
        this->bits = bits;
        return *this;
    }

    inline IPv4Address& IPv4Address::operator=(const char *str) noexcept {
        return parse(str) ? *this : operator=(static_cast<std::uint32_t>(0));
    }

    inline IPv4Address& IPv4Address::operator=(const std::string &str) noexcept {
        return parse(str) ? *this : operator=(static_cast<std::uint32_t>(0));
    }

    inline bool IPv4Address::operator==(const IPv4Address &address) const noexcept {
        return this->uint32 == address.uint32;
    }

    inline bool IPv4Address::operator!=(const IPv4Address &address) const noexcept {
        return this->uint32 != address.uint32;
    }

    // Destructors.
    inline IPv4Address::~IPv4Address() noexcept = default;

    // Static utility functions.
    inline IPv4Address IPv4Address::Parse(const char *str) noexcept {
        return Parse(str, std::strlen(str));
    }

    inline IPv4Address IPv4Address::Parse(const char *str, const std::size_t &length) noexcept {
        IPv4Address address;
        [[maybe_unused]] const bool _ = Parse(str, length, address);
        return address;
    }

    inline IPv4Address IPv4Address::Parse(const std::string &str) noexcept {
        return Parse(str.c_str(), str.length());
    }

    inline bool IPv4Address::Parse(const char *str, IPv4Address &address) noexcept {
        return Parse(str, std::strlen(str), address);
    }

    inline bool IPv4Address::Parse(const char *str, const std::size_t &length, IPv4Address &address) noexcept {
        const auto v = address.uint32;
        if (!address.parse(str, length)) {
            address.uint32 = v;
            return false;
        }

        return true;
    }

    inline bool IPv4Address::Parse(const std::string &str, IPv4Address &address) noexcept {
        return Parse(str.c_str(), str.length(), address);
    }

    inline std::string IPv4Address::Stringify(const IPv4Address &address) noexcept {
        return address.stringify();
    }

    inline bool IPv4Address::Stringify(const IPv4Address &address, std::string &str) noexcept {
        return address.stringify(str);
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_IP_ADDRESS_IMPL_V4_IPP
