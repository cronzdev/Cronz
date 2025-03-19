/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_IMPL_V4_IPP
#define CRONZ_IP_ADDRESS_IMPL_V4_IPP 1

#include "cronz/ip/address/v4.hpp"

CRONZ_BEGIN_IP_NAMESPACE
    // Properties.
    inline bool IPv4Address::hasMask() const noexcept {
        return MinMaskValue <= mask && mask <= MaxMaskValue;
    }

    inline std::size_t IPv4Address::addressCount() const noexcept {
        if (hasMask())
            return static_cast<std::size_t>(static_cast<std::uint32_t>(1) << (MaxMaskValue - mask));

        return static_cast<std::size_t>(1);
    }

    inline IPv4Address IPv4Address::subnetMask() const noexcept {
        if (hasMask()) {
            IPv4Address address(static_cast<std::uint32_t>(0xFFFFFFFF) << (MaxMaskValue - mask));

            if constexpr (std::endian::native == std::endian::little)
                address.reverse();

            return address;
        }

        return IPv4Address(0xFFFFFFFFU);
    }

    // Constructors.
    inline IPv4Address::IPv4Address() noexcept : int32(static_cast<std::int32_t>(0)) {
    }

    inline IPv4Address::IPv4Address(const std::int32_t int32) noexcept : int32(int32) {
    }

    inline IPv4Address::IPv4Address(const std::int32_t int32, const MaskValueType mask) noexcept : int32(int32),
        mask(mask) {
        if (!hasMask())
            reset();
    }

    inline IPv4Address::IPv4Address(const std::uint32_t uint32) noexcept : uint32(uint32) {
    }

    inline IPv4Address::IPv4Address(const std::uint32_t uint32, const MaskValueType mask) noexcept : uint32(uint32),
        mask(mask) {
        if (!hasMask())
            reset();
    }

    inline IPv4Address::IPv4Address(const std::uint8_t byte1, const std::uint8_t byte2, const std::uint8_t byte3,
                                    const std::uint8_t byte4) noexcept : bytes{byte1, byte2, byte3, byte4} {
    }

    inline IPv4Address::IPv4Address(const std::uint8_t byte1, const std::uint8_t byte2, const std::uint8_t byte3,
                                    const std::uint8_t byte4, const MaskValueType mask) noexcept : bytes{
            byte1, byte2, byte3, byte4
        },
        mask(mask) {
        if (!hasMask())
            reset();
    }

    inline IPv4Address::IPv4Address(
        const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept : bytes(bytes) {
    }

    inline IPv4Address::IPv4Address(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes,
                                    const MaskValueType mask) noexcept : bytes(bytes), mask(mask) {
        if (!hasMask())
            reset();
    }

    inline IPv4Address::IPv4Address(const std::string_view address) noexcept : int32(static_cast<std::int32_t>(0)) {
        [[maybe_unused]] const bool _ = parse(address);
    }

    // Instance-based utility functions.
    inline bool IPv4Address::parse(const std::string_view address) noexcept {
        auto byteIndex = static_cast<std::size_t>(0);

        auto previous = address.cbegin();
        auto end = address.cend();

        if (static_cast<std::size_t>(7) > address.length() || address.length() > static_cast<std::size_t>(18))
            goto parse_bad;

        if (const auto maskPos = std::ranges::find(previous, end, '/');
            end != maskPos) {
            mask = static_cast<MaskValueType>(0);

            auto current = maskPos;
            std::advance(current, static_cast<std::ptrdiff_t>(1));

            if (const auto length = std::distance(current, end);
                length > static_cast<std::ptrdiff_t>(2) || length == static_cast<std::ptrdiff_t>(0))
                goto parse_bad;

            while (current != end) {
                if (const char c = *current;
                    '0' <= c && c <= '9') {
                    mask *= static_cast<MaskValueType>(10);
                    mask += static_cast<MaskValueType>(c - '0');
                } else {
                    goto parse_bad;
                }

                std::advance(current, static_cast<std::ptrdiff_t>(1));
            }

            if (!hasMask())
                goto parse_bad;

            end = maskPos;
        } else {
            mask = EmptyMaskValue;
        }

        if (static_cast<std::ptrdiff_t>(15) < std::distance(previous, end))
            goto parse_bad;

        while (previous < end) {
            if (static_cast<std::size_t>(3) < byteIndex)
                goto parse_bad;

            const auto current = std::ranges::find(previous, end, '.');
            if (const auto length = std::distance(previous, current);
                length > static_cast<std::ptrdiff_t>(3) || length == static_cast<std::ptrdiff_t>(0))
                goto parse_bad;

            auto byte = static_cast<std::uint8_t>(0);
            while (previous < current) {
                if (const char c = *previous;
                    '0' <= c && c <= '9') {
                    const auto digit = static_cast<std::uint8_t>(c - '0');
                    if ((static_cast<std::uint8_t>(25) < byte) ||
                        (static_cast<std::uint8_t>(25) == byte && static_cast<std::uint8_t>(5) < digit))
                        goto parse_bad;

                    byte = (byte * static_cast<std::uint8_t>(10)) + digit;
                } else {
                    goto parse_bad;
                }

                std::advance(previous, static_cast<std::ptrdiff_t>(1));
            }

            bytes[byteIndex++] = byte;
            std::advance(previous, static_cast<std::ptrdiff_t>(1));
        }

        if (static_cast<std::size_t>(4) != byteIndex)
            goto parse_bad;

        return true;

    parse_bad:
        reset();

        return false;
    }

    inline std::string IPv4Address::stringify() const noexcept {
        std::string str;
        if (!stringify(str))
            str.clear();

        return str;
    }

    inline bool IPv4Address::stringify(std::string &str, std::size_t offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            str.size() < len) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        auto n = static_cast<std::uint8_t>(0);
        for (std::uint8_t byte: bytes) {
            auto length = static_cast<std::size_t>(0);

            do {
                str[offset++] = static_cast<char>('0' + static_cast<char>(byte % static_cast<std::uint8_t>(10)));
                byte /= static_cast<std::uint8_t>(10);
                ++length;
            } while (static_cast<std::size_t>(0) != byte);

            if (static_cast<std::size_t>(2) == length)
                std::swap(str[offset - static_cast<std::size_t>(1)], str[offset - static_cast<std::size_t>(2)]);
            else if (static_cast<std::size_t>(3) == length)
                std::swap(str[offset - static_cast<std::size_t>(1)], str[offset - static_cast<std::size_t>(3)]);

            if (static_cast<std::uint8_t>(4) != ++n)
                str[offset++] = '.';
        }

        if (hasMask()) {
            str[offset++] = '/';

            if (static_cast<MaskValueType>(10) < mask) {
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask / static_cast<MaskValueType>(10)));
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask % static_cast<MaskValueType>(10)));
            } else {
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask));
            }
        }

        return true;
    }

    inline std::size_t IPv4Address::length() const noexcept {
        auto length = static_cast<std::size_t>(7);

        for (std::uint8_t byte: bytes) {
            while (static_cast<std::uint8_t>(9) < byte) {
                byte /= static_cast<std::uint8_t>(10);
                ++length;
            }
        }

        if (hasMask())
            length += ((static_cast<MaskValueType>(10) < mask)
                           ? static_cast<std::size_t>(3)
                           : static_cast<std::size_t>(2));

        return length;
    }

    inline void IPv4Address::reset() noexcept {
        int32 = static_cast<std::int32_t>(0);
        mask = EmptyMaskValue;
    }

    inline void IPv4Address::reverse() noexcept {
        std::ranges::reverse(bytes);
    }

    // Operators.
    inline constexpr std::uint8_t &IPv4Address::operator[](const std::size_t index) noexcept {
        return bytes[index];
    }

    inline constexpr std::uint8_t IPv4Address::operator[](const std::size_t index) const noexcept {
        return bytes[index];
    }

    inline IPv4Address::operator bool() const noexcept {
        return static_cast<bool>(int32);
    }

    inline IPv4Address::operator std::int32_t() const noexcept {
        return int32;
    }

    inline IPv4Address::operator std::uint32_t() const noexcept {
        return uint32;
    }

    inline IPv4Address::operator std::array<std::uint8_t, static_cast<std::size_t>(4)>() const noexcept {
        return bytes;
    }

    inline IPv4Address::operator std::string() const noexcept {
        return stringify();
    }

    inline IPv4Address &IPv4Address::operator=(const std::int32_t &int32) noexcept {
        mask = EmptyMaskValue;

        this->int32 = int32;
        return *this;
    }

    inline IPv4Address &IPv4Address::operator=(const std::uint32_t &uint32) noexcept {
        mask = EmptyMaskValue;

        this->uint32 = uint32;
        return *this;
    }

    inline IPv4Address &IPv4Address::operator=(
        const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept {
        mask = EmptyMaskValue;

        memcpy(this->bytes.data(), bytes.data(), bytes.size());
        return *this;
    }

    inline IPv4Address &IPv4Address::operator=(const std::string_view address) noexcept {
        [[maybe_unused]] const auto _ = parse(address);
        return *this;
    }

    inline bool IPv4Address::operator==(const std::int32_t &int32) const noexcept {
        return this->int32 == int32;
    }

    inline bool IPv4Address::operator==(const std::uint32_t &uint32) const noexcept {
        return this->uint32 == uint32;
    }

    inline bool IPv4Address::operator==(
        const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) const noexcept {
        return this->bytes == bytes;
    }

    inline bool IPv4Address::operator==(const std::string_view address) const noexcept {
        return stringify() == address;
    }

    inline bool IPv4Address::operator==(const IPv4Address &other) const noexcept {
        return int32 == other.int32 && mask == other.mask;
    }

    inline bool IPv4Address::operator!=(const std::int32_t &int32) const noexcept {
        return this->int32 != int32;
    }

    inline bool IPv4Address::operator!=(const std::uint32_t &uint32) const noexcept {
        return this->uint32 != uint32;
    }

    inline bool IPv4Address::operator!=(
        const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) const noexcept {
        return this->bytes != bytes;
    }

    inline bool IPv4Address::operator!=(const std::string_view address) const noexcept {
        return stringify() != address;
    }

    inline bool IPv4Address::operator!=(const IPv4Address &other) const noexcept {
        return int32 != other.int32 || mask != other.mask;
    }

    // Friend operators.
    template<typename T>
    inline bool operator==(const T &value, const IPv4Address &instance) noexcept {
        return instance == value;
    }

    template<typename T>
    inline bool operator!=(const T &value, const IPv4Address &instance) noexcept {
        return instance != value;
    }

CRONZ_END_IP_NAMESPACE

#endif // CRONZ_IP_ADDRESS_IMPL_V4_IPP
