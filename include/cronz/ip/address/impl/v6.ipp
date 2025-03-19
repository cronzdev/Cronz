/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_IMPL_V6_IPP
#define CRONZ_IP_ADDRESS_IMPL_V6_IPP 1

#include "cronz/ip/address/v6.hpp"
#include "cronz/cryptography/hex.hpp"

CRONZ_BEGIN_IP_NAMESPACE
    // Constructors.
    inline IPv6Address::IPv6Address() noexcept = default;

    inline IPv6Address::IPv6Address(std::uint64_t low64, std::uint64_t high64) noexcept : low64(low64), high64(high64) {
    }

    inline IPv6Address::IPv6Address(const std::array<uint16_t, static_cast<std::size_t>(8)> &groups) noexcept : groups(
        groups) {
    }

    inline IPv6Address::IPv6Address(const std::array<uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept : bytes(
        bytes) {
    }

    inline IPv6Address::IPv6Address(std::string_view address) noexcept : groups{0} {
        [[maybe_unused]] const bool _ = parse(address);
    }

    // Properties.
    inline bool IPv6Address::hasMask() const noexcept {
        return MinMaskValue <= mask && mask <= MaxMaskValue;
    }

    inline std::size_t IPv6Address::addressCount() const noexcept {
        if (!hasMask())
            return static_cast<std::size_t>(1);

        const MaskValueType bits = static_cast<MaskValueType>(128) - mask;
        if ((sizeof(std::size_t) * static_cast<std::size_t>(8)) < static_cast<std::size_t>(bits))
            return std::numeric_limits<std::size_t>::max();

        return static_cast<std::size_t>(1) << bits;
    }

    inline IPv6Address IPv6Address::subnetMask() const noexcept {
        if (!hasMask())
            return {};

        IPv6Address address;
        address.high64 = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF) << mask;
        address.low64 = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF) << (mask - static_cast<MaskValueType>(64));

        return address;
    }

    // Instance-based utility functions.
    inline bool IPv6Address::parse(const std::string_view address) noexcept {
        reset();

        // State variables.
        const char *const beg = address.cbegin();
        const char *end = address.cend();
        const char *last = end - static_cast<std::ptrdiff_t>(1);

        const char *current = address.cbegin();

        auto groupIndex = static_cast<std::size_t>(0);
        std::array<std::uint8_t, static_cast<std::size_t>(2)> groupBytes{};
        std::array<char, static_cast<std::size_t>(4)> groupCharacters{};

        bool containsDoubleColons = false;
        std::size_t doubleColonsPos = std::numeric_limits<std::size_t>::max();

        bool containsIPv4 = false;

        // Check the address length.
        // IPv6 address length is between 2 and 50 characters; including a potential IPv4 part and mask.
        if (static_cast<std::size_t>(2) > address.length() || address.length() > static_cast<std::size_t>(50))
            goto parse_bad;

        // Check the mask.
        if (const char *slash = std::ranges::find(beg, end, '/');
            end != slash) {
            // Parse the mask.
            mask = static_cast<MaskValueType>(0);

            if (beg == slash || last == slash) {
                // Slash at the beginning or end is invalid.
                goto parse_bad;
            }

            if (const auto length = std::distance(slash, end);
                static_cast<std::ptrdiff_t>(0) == length || length > static_cast<std::ptrdiff_t>(4)) {
                // Invalid mask length.
                goto parse_bad;
            }

            for (current = (slash + static_cast<std::ptrdiff_t>(1)); current < end; ++current) {
                if (const char c = *current;
                    '0' <= c && c <= '9') {
                    const auto digit = static_cast<MaskValueType>(c - '0');
                    if (static_cast<MaskValueType>(0) == digit && static_cast<MaskValueType>(0) == mask) {
                        // Leading zero is invalid.
                        goto parse_bad;
                    }

                    if (static_cast<MaskValueType>(12) >= mask && static_cast<MaskValueType>(8) < digit) {
                        // Mask is out of range.
                        goto parse_bad;
                    }

                    mask *= static_cast<MaskValueType>(10);
                    mask += digit;
                } else {
                    // Invalid mask character.
                    goto parse_bad;
                }
            }

            if (!hasMask()) {
                // Mask is invalid.
                goto parse_bad;
            }

            end = slash;
            last = end - static_cast<std::ptrdiff_t>(1);
            current = beg;
        }

        // Parse the address.
        while (current < end) {
            // Group index should not reach the maximum group count.
            if (groups.size() == groupIndex)
                goto parse_bad;

            // Find the next colon and calculate the length of the preceding group.
            const char *colon = std::ranges::find(current, end, ':');
            const auto length = static_cast<std::size_t>(std::distance(current, colon));

            // Check the length of the group.
            if (static_cast<std::size_t>(0) == length) {
                // If the length is zero, that indicates a compressed zero sequence.

                if (containsDoubleColons) {
                    // Double colons can only appear once.
                    goto parse_bad;
                }

                if (beg == colon) {
                    // Zero compression at the beginning.
                    // Ensure that the next character is a colon.
                    if (':' != colon[1])
                        goto parse_bad;

                    std::advance(current, static_cast<std::ptrdiff_t>(1));
                } else if (last == colon) {
                    // Zero compression at the end.
                    // Ensure that the previous character is a colon.
                    if (':' != colon[-1])
                        goto parse_bad;
                }

                containsDoubleColons = true;
                doubleColonsPos = groupIndex;

                // Move to the next character.
                std::advance(current, static_cast<std::ptrdiff_t>(1));
            } else if (static_cast<std::size_t>(7) <= length) {
                // Possible IPv4 part.

                if (static_cast<std::size_t>(6) < groupIndex) {
                    // IPv4 part can only appear in the last two groups.
                    goto parse_bad;
                }

                IPv4Address v4{};
                if (!v4.parse(std::string_view(current, length))) {
                    // Failed to parse the IPv4 part.
                    goto parse_bad;
                }

                // Copy the IPv4 bytes to the address.
                memcpy(&bytes[bytes.size() - v4.bytes.size()], v4.bytes.data(), v4.bytes.size());

                if (colon != end) {
                    // IPv4 has to be at the end.
                    goto parse_bad;
                }

                containsIPv4 = true;

                // End the loop.
                current = colon;
            } else if (static_cast<std::size_t>(4) >= length) {
                // Expected group length is between 1 and 4 characters.

                // Copy the group characters to the buffer.
                groupCharacters.fill('0');
                memcpy(groupCharacters.data() + (groupCharacters.size() - length), current, length);

                // Convert the group characters to bytes.
                if (!HexToByte(groupCharacters[0], groupCharacters[1], groupBytes[0]) ||
                    !HexToByte(groupCharacters[2], groupCharacters[3], groupBytes[1])) {
                    // Invalid hex characters.
                    goto parse_bad;
                }

                memcpy(&groups[groupIndex++], groupBytes.data(), groupBytes.size());

                // Move to the next character.
                std::advance(colon, static_cast<std::ptrdiff_t>(1));
                current = colon;
            } else {
                // Invalid group length.
                goto parse_bad;
            }
        }

        // Check the state and expand the compressed zero sequence.
        if (':' == *last && (containsIPv4 || (!containsDoubleColons || doubleColonsPos != groupIndex))) {
            // Colon at the end is invalid unless there is a double colon.
            goto parse_bad;
        }

        if (containsDoubleColons) {
            const std::size_t maxGroups = (containsIPv4 ? static_cast<std::size_t>(6) : groups.size());

            if (doubleColonsPos == groupIndex) {
                // The rest of the groups are zero. No need to expand.
                groupIndex = maxGroups;
                goto double_colons_skip;
            }

            // Expand the compressed zero sequence.
            memcpy(&groups[doubleColonsPos + maxGroups - groupIndex], &groups[doubleColonsPos],
                   groupIndex * sizeof(std::uint16_t));
            memset(&groups[doubleColonsPos], static_cast<std::uint16_t>(0),
                   (maxGroups - groupIndex) * sizeof(std::uint16_t));

            groupIndex = maxGroups;
        }

    double_colons_skip:
        // If the address contains an IPv4 part, the last two groups are the IPv4 bytes.
        if (containsIPv4)
            groupIndex += static_cast<std::size_t>(2);

        // Check the group count.
        return groups.size() == groupIndex;

    parse_bad:
        reset();
        return false;
    }

    inline std::string IPv6Address::stringify(const bool compressed) const noexcept {
        std::string str;
        if (!stringify(str, compressed, static_cast<std::size_t>(0)))
            str.clear();

        return str;
    }

    inline bool IPv6Address::stringify(std::string &str, const bool compressed, std::size_t offset) const noexcept {
        if (const std::size_t len = (length(compressed) + offset);
            str.size() < len) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (compressed) {
            auto start = static_cast<std::size_t>(0);
            auto length = static_cast<std::size_t>(0);
            auto end = static_cast<std::size_t>(0);
            if (findLargestZeroSequence(start, length))
                end = (start + length) - static_cast<std::size_t>(1);

            char temp;
            for (auto byteIndex = static_cast<std::size_t>(0), groupIndex = static_cast<std::size_t>(0);
                 groupIndex < groups.size(); ++groupIndex, byteIndex += static_cast<std::size_t>(2)) {
                if (start <= groupIndex && groupIndex <= end) {
                    if (start == groupIndex || end == groupIndex)
                        str[offset++] = ':';

                    continue;
                }

                if (static_cast<std::size_t>(0) != groupIndex)
                    str[offset++] = ':';

                const std::uint8_t byte1 = bytes[byteIndex];
                const std::uint8_t byte2 = bytes[byteIndex + static_cast<std::size_t>(1)];

                if (static_cast<std::uint8_t>(0) != byte1) {
                    if (static_cast<std::uint8_t>(16) <= byte1) {
                        ByteToHex<false>(byte1, str[offset], str[offset + static_cast<std::size_t>(1)]);
                        offset += static_cast<std::size_t>(2);
                    } else {
                        ByteToHex<false>(byte1, temp, str[offset++]);
                    }

                    ByteToHex<false>(byte2, str[offset], str[offset + static_cast<std::size_t>(1)]);
                    offset += static_cast<std::size_t>(2);
                } else {
                    if (static_cast<std::uint8_t>(16) <= byte2) {
                        ByteToHex<false>(byte2, str[offset], str[offset + static_cast<std::size_t>(1)]);
                        offset += static_cast<std::size_t>(2);
                    } else {
                        ByteToHex<false>(byte2, temp, str[offset++]);
                    }
                }
            }
        } else {
            auto byteIndex = static_cast<std::size_t>(0);
            while (byteIndex < bytes.size()) {
                if (static_cast<std::size_t>(0) != byteIndex)
                    str[offset++] = ':';

                ByteToHex<false>(bytes[byteIndex++], str[offset], str[offset + static_cast<std::size_t>(1)]);
                ByteToHex<false>(bytes[byteIndex++], str[offset + static_cast<std::size_t>(2)],
                                 str[offset + static_cast<std::size_t>(3)]);

                offset += static_cast<std::size_t>(4);
            }
        }

        if (hasMask()) {
            str[offset++] = '/';

            if (static_cast<MaskValueType>(100) < mask) {
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask / static_cast<MaskValueType>(100)));
                str[offset++] = static_cast<char>(
                    '0' + static_cast<char>((mask / static_cast<MaskValueType>(10) % static_cast<MaskValueType>(10))));
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask % static_cast<MaskValueType>(10)));
            } else if (static_cast<MaskValueType>(10) < mask) {
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask / static_cast<MaskValueType>(10)));
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask % static_cast<MaskValueType>(10)));
            } else {
                str[offset++] = static_cast<char>('0' + static_cast<char>(mask));
            }
        }

        return true;
    }

    inline std::size_t IPv6Address::length(const bool compressed) const noexcept {
        auto len = static_cast<std::size_t>(0);

        if (compressed) {
            len = static_cast<std::size_t>(7);

            auto start = static_cast<std::size_t>(0);
            auto length = static_cast<std::size_t>(0);
            auto end = static_cast<std::size_t>(0);
            if (findLargestZeroSequence(start, length)) {
                end = (start + length) - static_cast<std::size_t>(1);

                len -= (end - start);

                if (static_cast<std::size_t>(0) == start)
                    ++len;

                if (static_cast<std::size_t>(7) == end)
                    ++len;
            }

            for (auto byteIndex = static_cast<std::size_t>(0), groupIndex = static_cast<std::size_t>(0);
                 byteIndex < groups.size(); ++groupIndex, byteIndex += static_cast<std::size_t>(2)) {
                if (start <= groupIndex && groupIndex <= end)
                    continue;

                const std::uint8_t byte1 = bytes[byteIndex];
                const std::uint8_t byte2 = bytes[byteIndex + static_cast<std::size_t>(1)];

                if (static_cast<std::uint8_t>(0) != byte1) {
                    len += static_cast<std::size_t>(3);

                    if (static_cast<std::uint8_t>(16) <= byte1)
                        ++len;
                } else {
                    ++len;

                    if (static_cast<std::uint8_t>(16) <= byte2)
                        ++len;
                }
            }
        } else {
            len = static_cast<std::size_t>(39);
        }

        if (hasMask()) {
            if (static_cast<MaskValueType>(100) <= mask)
                len += static_cast<std::size_t>(4);
            else if (static_cast<MaskValueType>(10) <= mask)
                len += static_cast<std::size_t>(3);
            else
                len += static_cast<std::size_t>(2);
        }

        return len;
    }

    inline void IPv6Address::reset() noexcept {
        low64 = static_cast<std::uint64_t>(0);
        high64 = static_cast<std::uint64_t>(0);

        mask = EmptyMaskValue;
    }

    inline bool IPv6Address::findLargestZeroSequence(std::size_t &start, std::size_t &length) const noexcept {
        constexpr std::size_t _invalid = std::numeric_limits<std::size_t>::max();

        start = static_cast<std::size_t>(0);
        length = static_cast<std::size_t>(0);

        std::size_t testPos = _invalid;
        std::size_t testLen = _invalid;

        for (auto i = static_cast<std::size_t>(0); i < groups.size(); ++i) {
            if (const std::uint16_t &group = groups[i];
                static_cast<std::uint16_t>(0) == group) {
                if (_invalid == testPos) {
                    testPos = i;
                    testLen = static_cast<std::size_t>(0);
                }

                ++testLen;
            } else if (_invalid != testPos) {
                if (length < testLen) {
                    start = testPos;
                    length = testLen;
                }

                testPos = _invalid;
                testLen = _invalid;
            }
        }

        if (_invalid != testPos && length < testLen) {
            start = testPos;
            length = testLen;
        }

        return static_cast<std::size_t>(0) != length;
    }

CRONZ_END_IP_NAMESPACE

#endif // CRONZ_IP_ADDRESS_IMPL_V6_IPP
