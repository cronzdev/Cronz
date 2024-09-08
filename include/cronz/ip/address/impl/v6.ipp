/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_IMPL_V6_IPP
#define CRONZ_IP_ADDRESS_IMPL_V6_IPP 1

#include "cronz/ip/address/v6.hpp"
#include "cronz/url/hex.hpp"

#include <algorithm>
#include <cstring>
#include <limits>

CRONZ_BEGIN_MODULE_NAMESPACE(IP)
    // Constructors.
    inline IPv6Address::IPv6Address() noexcept : bits{0} {
    }

    inline IPv6Address::IPv6Address(
            const std::array<std::uint16_t, static_cast<std::size_t>(8)> &groups) noexcept : groups(groups) {
    }

    inline IPv6Address::IPv6Address(
            const std::array<std::uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept : bytes(bytes) {
    }

    inline IPv6Address::IPv6Address(const std::bitset<static_cast<std::size_t>(128)> &bits) noexcept : bits(bits) {
    }

    inline IPv6Address::IPv6Address(const char *str) noexcept : IPv6Address(Parse(str)) {
    }

    inline IPv6Address::IPv6Address(const char *str, const std::size_t &length) noexcept : IPv6Address(
            Parse(str, length)) {
    }

    inline IPv6Address::IPv6Address(const std::string &str) noexcept : IPv6Address(Parse(str)) {
    }

    // Instance-based utility functions.
    inline bool IPv6Address::findLargestZeroSequence(std::pair<std::size_t, std::size_t> &sequence) const noexcept {
        std::pair test = {
                std::numeric_limits<std::size_t>::max(),
                std::numeric_limits<std::size_t>::max()
        };

        for (auto i = static_cast<std::size_t>(0); i < groups.size(); ++i) {
            if (static_cast<std::uint16_t>(0) == groups[i]) {
                if (std::numeric_limits<std::size_t>::max() == test.first)
                    test.first = i;

                test.second = i;
            }
            else if (std::numeric_limits<std::size_t>::max() != test.first) {
                if (std::numeric_limits<std::size_t>::max() == test.first || (test.second - test.first) > (sequence.
                    second - sequence.first))
                    sequence = test;

                test.first = test.second = std::numeric_limits<std::size_t>::max();
            }
        }

        if (std::numeric_limits<std::size_t>::max() != test.first && std::numeric_limits<std::size_t>::max() != test.
            second)
            sequence = test;

        return (std::numeric_limits<std::size_t>::max() != sequence.first) && (std::numeric_limits<std::size_t>::max()
            != sequence.second);
    }

    // Conversion.
    inline bool IPv6Address::parse(const char *str) noexcept {
        return parse(str, std::strlen(str));
    }

    inline bool IPv6Address::parse(const char *str, const std::size_t &length) noexcept {
        if (static_cast<std::size_t>(2) > length || length > static_cast<std::size_t>(39))
            return false;

        reset();

        const char *const beg = str;
        const char *const end = str + length;
        const char *const last = end - static_cast<std::size_t>(1);

        auto groupIndex = static_cast<std::size_t>(0);

        bool doubleColons = false;
        std::size_t doubleColonsPos = std::numeric_limits<std::size_t>::max();

        std::array<char, static_cast<std::size_t>(4)> characters{};
        std::array<std::uint8_t, static_cast<std::size_t>(2)> bytes{};

        const char *previous = beg;
        while (previous < end) {
            if (groups.size() == groupIndex)
                return false;

            const char *current = std::ranges::find(previous, end, ':');
            const std::size_t currentLength = current - previous;

            if (static_cast<std::size_t>(4) < currentLength)
                return false;

            if (static_cast<std::size_t>(0) == currentLength) {
                if (current == last)
                    return true;

                if (current == beg) {
                    if (':' != current[1])
                        return false;

                    ++current;
                }
                else if (doubleColons || ((current + static_cast<std::size_t>(1)) >= end) || ':' != current[-1]) {
                    return false;
                }

                doubleColons = true;
                doubleColonsPos = groupIndex;
            }
            else {
                characters.fill('0');
                memcpy(characters.data() + (characters.size() - currentLength), previous, currentLength);

                if (!URL::HexToByte(characters[0], characters[1], bytes[0]) ||
                    !URL::HexToByte(characters[2], characters[3], bytes[1]))
                    return false;

                memcpy(&groups[groupIndex++], bytes.data(), bytes.size());
            }

            previous = current + static_cast<std::size_t>(1);
        }

        if (!doubleColons && ':' == last[0])
            return false;

        if (doubleColons) {
            std::size_t numFilledGroups = groupIndex - doubleColonsPos;
            if (static_cast<std::size_t>(0) == numFilledGroups) {
                if (static_cast<std::size_t>(2) == length)
                    return true;

                return false;
            }

            auto i = static_cast<std::size_t>(1);
            while (doubleColonsPos < groupIndex) {
                std::swap(groups[doubleColonsPos + numFilledGroups - i], groups[groups.size() - i]);
                ++i;
                --numFilledGroups;
                ++doubleColonsPos;
            }

            return true;
        }

        return groupIndex == groups.size();
    }

    inline bool IPv6Address::parse(const std::string &str) noexcept {
        return parse(str.c_str(), str.length());
    }

    template <bool Compress>
    inline std::string IPv6Address::stringify() const noexcept {
        std::string str;
        if (!stringify<Compress>(str))
            str.clear();

        return str;
    }

    template <bool Compress>
    inline bool IPv6Address::stringify(std::string &str) const noexcept {
        const std::size_t len = IPv6Address::length<Compress>();

        try {
            str.resize(len);
        }
        catch (...) {
            return false;
        }

        if constexpr (Compress) {
            std::pair<std::size_t, std::size_t> sequence;
            [[maybe_unused]] bool _ = findLargestZeroSequence(sequence);
            _ = _ || (static_cast<std::size_t>(1) <= (sequence.second - sequence.first));

            char temp;

            bool n = false;
            for (auto o = static_cast<std::size_t>(0), byteIndex = static_cast<std::size_t>(0), groupIndex = static_cast
                              <std::size_t>(0); o < len; byteIndex += static_cast<std::size_t>(2), ++groupIndex) {
                if (sequence.first <= groupIndex && groupIndex <= sequence.second) {
                    n = (sequence.second == groupIndex);
                    if (sequence.first == groupIndex || n)
                        str[o++] = ':';

                    continue;
                }

                if (static_cast<std::size_t>(0) != o && !n)
                    str[o++] = ':';

                n = false;

                const std::uint8_t b1 = bytes[byteIndex];
                const std::uint8_t b2 = bytes[byteIndex + static_cast<std::size_t>(1)];

                if (static_cast<std::uint8_t>(0) != b1) {
                    if (static_cast<std::uint8_t>(16) <= b1) {
                        URL::ByteToHex<true>(b1, str[o], str[o + static_cast<std::size_t>(1)]);
                        o += static_cast<std::size_t>(2);
                    }
                    else {
                        URL::ByteToHex<true>(b1, temp, str[o]);
                        o += static_cast<std::size_t>(1);
                    }

                    URL::ByteToHex<true>(b2, str[o], str[o + static_cast<std::size_t>(1)]);

                    o += static_cast<std::size_t>(2);
                }
                else {
                    if (static_cast<std::uint8_t>(16) <= b2) {
                        URL::ByteToHex<true>(b2, str[o], str[o + static_cast<std::size_t>(1)]);
                        o += static_cast<std::size_t>(2);
                    }
                    else {
                        URL::ByteToHex<true>(b2, temp, str[o]);
                        o += static_cast<std::size_t>(1);
                    }
                }
            }

            return true;
        }
        else {
            std::size_t i;
            std::size_t j;
            for (i = static_cast<std::size_t>(0), j = static_cast<std::size_t>(0); i < len; i += static_cast<
                     std::size_t>(5), j += static_cast<std::size_t>(2)) {
                URL::ByteToHex<true>(bytes[j], str[i], str[i + static_cast<std::size_t>(1)]);
                URL::ByteToHex<true>(bytes[j + static_cast<std::size_t>(1)], str[i + static_cast<std::size_t>(2)],
                                     str[i + static_cast<std::size_t>(3)]);
            }

            for (i = static_cast<std::size_t>(4); i < len; i += static_cast<std::size_t>(5))
                str[i] = ':';
        }

        return true;
    }

    template <bool Compress>
    inline std::size_t IPv6Address::length() const noexcept {
        if constexpr (Compress) {
            std::pair<std::size_t, std::size_t> sequence;
            [[maybe_unused]] bool _ = findLargestZeroSequence(sequence);
            _ = _ || (static_cast<std::size_t>(1) <= (sequence.second - sequence.first));

            auto len = static_cast<std::size_t>(7);
            if (_) {
                len -= (sequence.second - sequence.first);

                if (static_cast<std::size_t>(0) == sequence.first)
                    ++len;

                if (static_cast<std::size_t>(7) == sequence.second)
                    ++len;
            }

            for (auto i = static_cast<std::size_t>(0), groupIndex = static_cast<std::size_t>(0); i < bytes.size(); i +=
                 static_cast<std::size_t>(2), ++groupIndex) {
                if (sequence.first <= groupIndex && groupIndex <= sequence.second)
                    continue;

                const std::uint8_t &b1 = bytes[i];
                const std::uint8_t &b2 = bytes[i + static_cast<std::size_t>(1)];

                if (static_cast<std::uint8_t>(0) != b1) {
                    len += static_cast<std::size_t>(3);

                    if (static_cast<std::uint8_t>(16) <= b1)
                        ++len;
                }
                else {
                    ++len;

                    if (static_cast<std::uint8_t>(16) <= b2)
                        ++len;
                }
            }

            return len;
        }
        else {
            return static_cast<std::size_t>(39);
        }
    }

    inline void IPv6Address::reset() noexcept {
        bytes.fill(static_cast<std::uint8_t>(0));
    }

    // Operators.
    inline IPv6Address::operator bool() const noexcept {
        return static_cast<std::uint64_t>(0) != low64 && static_cast<std::uint64_t>(0) != high64;
    }

    inline IPv6Address& IPv6Address::operator=(
            const std::array<std::uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept {
        this->bytes = bytes;
        return *this;
    }

    inline IPv6Address& IPv6Address::operator=(const std::bitset<static_cast<std::size_t>(128)> &bits) noexcept {
        this->bits = bits;
        return *this;
    }

    inline IPv6Address& IPv6Address::operator=(const char *str) noexcept {
        return *this;
    }

    inline IPv6Address& IPv6Address::operator=(const std::string &str) noexcept {
        return *this;
    }

    inline bool IPv6Address::operator==(const IPv6Address &address) const noexcept {
        return this->low64 == address.low64 && this->high64 == address.high64;
    }

    inline bool IPv6Address::operator!=(const IPv6Address &address) const noexcept {
        return this->low64 != address.low64 || this->high64 != address.high64;
    }

    // Destructors.
    inline IPv6Address::~IPv6Address() noexcept = default;

    // Static utility functions.
    inline IPv6Address IPv6Address::Parse(const char *str) noexcept {
        return Parse(str, std::strlen(str));
    }

    inline IPv6Address IPv6Address::Parse(const char *str, const std::size_t &length) noexcept {
        IPv6Address address;
        [[maybe_unused]] const bool _ = Parse(str, length, address);
        return address;
    }

    inline IPv6Address IPv6Address::Parse(const std::string &str) noexcept {
        return Parse(str.c_str(), str.length());
    }

    inline bool IPv6Address::Parse(const char *str, IPv6Address &address) noexcept {
        return Parse(str, std::strlen(str), address);
    }

    inline bool IPv6Address::Parse(const char *str, const std::size_t &length, IPv6Address &address) noexcept {
        const auto v = address.bytes;
        if (!address.parse(str, length)) {
            address.bytes = v;
            return false;
        }

        return true;
    }

    inline bool IPv6Address::Parse(const std::string &str, IPv6Address &address) noexcept {
        return Parse(str.c_str(), str.length(), address);
    }

    template <bool Compress>
    inline std::string IPv6Address::Stringify(const IPv6Address &address) noexcept {
        return address.stringify<Compress>();
    }

    template <bool Compress>
    inline bool IPv6Address::Stringify(const IPv6Address &address, std::string &str) noexcept {
        return address.stringify<Compress>(str);
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_IP_ADDRESS_IMPL_V6_IPP
