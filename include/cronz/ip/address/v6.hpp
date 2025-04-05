/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_V6_HPP
#define CRONZ_IP_ADDRESS_V6_HPP 1

#include "cronz/ip/address/v4.hpp"

CRONZ_BEGIN_IP_NAMESPACE
    /**
     * @ingroup ip_address
     * @brief IPv6 address structure.
     * @struct IPv6Address
     * @remark IPv6 parsing and stringification processes follow the specifications stated by:
     * - [RFC5952](https://datatracker.ietf.org/doc/html/rfc5952)
     * - [RFC4291](https://datatracker.ietf.org/doc/html/rfc4291)
     * - [RFC8200](https://datatracker.ietf.org/doc/html/rfc8200)
     */
    struct IPv6Address {
        /**
         * @name Static type definitions and constants.
         */
        /** @{ */
        /**
         * @brief IPv6 address groups.
         * @struct IPv6AddressGroup
         */
        struct IPv6AddressGroup {
            union {
                struct {
                    /**
                     * @brief First byte of the group.
                     */
                    std::uint8_t byte1;

                    /**
                     * @brief Second byte of the group.
                     */
                    std::uint8_t byte2;
                };

                /**
                 * @brief Packed value of the group.
                 */
                std::uint16_t value;

                /**
                 * @brief Bytes of the group.
                 */
                std::array<std::uint8_t, static_cast<std::size_t>(2)> bytes;
            };
        };

        /**
         * @brief Mask value type.
         * @details The mask is used for CIDR notation.
         */
        using MaskValueType = std::uint_fast8_t;

        /**
         * @brief Empty mask value.
         */
        inline static constexpr MaskValueType EmptyMaskValue = std::numeric_limits<MaskValueType>::max();

        /**
         * @brief Invalid mask value.
         */
        inline static constexpr MaskValueType InvalidMaskValue = std::numeric_limits<MaskValueType>::min();

        /**
         * @brief Minimum mask value.
         */
        inline static constexpr MaskValueType MinMaskValue = static_cast<MaskValueType>(8);

        /**
         * @brief Maximum mask value.
         */
        inline static constexpr MaskValueType MaxMaskValue = static_cast<MaskValueType>(128);

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        union {
            struct {
                /**
                 * @brief First group of the address.
                 */
                IPv6AddressGroup group1;

                /**
                 * @brief Second group of the address.
                 */
                IPv6AddressGroup group2;

                /**
                 * @brief Third group of the address.
                 */
                IPv6AddressGroup group3;

                /**
                 * @brief Fourth group of the address.
                 */
                IPv6AddressGroup group4;

                /**
                 * @brief Fifth group of the address.
                 */
                IPv6AddressGroup group5;

                /**
                 * @brief Sixth group of the address.
                 */
                IPv6AddressGroup group6;

                /**
                 * @brief Seventh group of the address.
                 */
                IPv6AddressGroup group7;

                /**
                 * @brief Eighth group of the address.
                 */
                IPv6AddressGroup group8;
            };

            struct {
                /**
                 * @brief First 64-bit part of the address.
                 */
                std::uint64_t low64;

                /**
                 * @brief Second 64-bit part of the address.
                 */
                std::uint64_t high64;
            };

            /**
             * @brief 16-bit groups of the address.
             */
            std::array<uint16_t, static_cast<std::size_t>(8)> groups;

            /**
             * @brief Bytes of the address.
             */
            std::array<uint8_t, static_cast<std::size_t>(16)> bytes{};
        };

        /**
         * @brief Address mask.
         * @note The mask is used for CIDR notation.
         */
        MaskValueType mask = EmptyMaskValue;

        /**
         * @brief Test if the address has a mask.
         * @return `true` if the address has a mask.
         * @return `false` if the address does not have a mask.
         */
        CRONZ_NODISCARD_L1 bool hasMask() const noexcept;

        /**
         * @brief Get the number of addresses in the subnet.
         * @return Number of addresses in the subnet.
         */
        CRONZ_NODISCARD_L1 std::size_t addressCount() const noexcept;

        /**
         * @brief Get the subnet mask.
         * @return Subnet mask.
         */
        CRONZ_NODISCARD_L1 IPv6Address subnetMask() const noexcept;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        IPv6Address() noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] low64 First 64-bit part of the address.
         * @param[in] high64 Second 64-bit part of the address.
         */
        IPv6Address(std::uint64_t low64, std::uint64_t high64) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] groups 16-bit groups of the address.
         */
        explicit(true) IPv6Address(const std::array<uint16_t, static_cast<std::size_t>(8)> &groups) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] bytes Bytes of the address.
         */
        explicit(true) IPv6Address(const std::array<uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] address Address string.
         */
        explicit(true) IPv6Address(std::string_view address) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Parse an IPv6 address.
         * @param[in] address Address string.
         * @return `true` if the address is valid.
         * @return `false` if the address is not valid.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view address) noexcept;

        /**
         * @brief Stringify the address.
         * @param[in] compressed Compressed representation.
         * @return String representation of the address.
         * @remark Upon failure, empty string is returned.
         */
        CRONZ_NODISCARD_L1 std::string stringify(bool compressed = true) const noexcept;

        /**
         * @brief Stringify the address.
         * @param[out] str String representation of the address.
         * @param[in] compressed Compressed representation.
         * @return `true` if the stringification is successful.
         * @return `false` if the stringification fails.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, bool compressed = true) const noexcept;

        /**
         * @brief Stringify the address.
         * @param[out] str String representation of the address.
         * @param[out] offset Position in the string to start writing.
         * @param[in] compressed Compressed representation.
         * @return `true` if the stringification is successful.
         * @return `false` if the stringification fails.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset, bool compressed = true) const noexcept;

        /**
         * @brief Get the length of the string representation.
         * @param[in] compressed Compressed representation.
         * @return Length of the string representation.
         */
        CRONZ_NODISCARD_L1 std::size_t length(bool compressed = true) const noexcept;

        /**
         * @brief Reset the address.
         */
        void reset() noexcept;

        /**
         * @brief Find the largest zero sequence in the address.
         * @param[out] start Start index of the sequence.
         * @param[out] length Length of the sequence.
         * @return `true` if a zero sequence is found.
         * @return `false` if a zero sequence is not found.
         */
        CRONZ_NODISCARD_L1 bool findLargestZeroSequence(std::size_t &start, std::size_t &length) const noexcept;

        /** @} */
    };

CRONZ_END_IP_NAMESPACE

#include "cronz/ip/address/impl/v6.ipp"

#endif // CRONZ_IP_ADDRESS_V6_HPP
