/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_V6_HPP
#define CRONZ_IP_ADDRESS_V6_HPP 1

#include "cronz/ip/address/v4.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(IP)
    /**
     * @ingroup cronz_ip_address
     * @brief IPv6 address container.
     * @struct IPv6Address
     * @remark IPv6 parsing and stringification process follows the specifications stated by
     * [RFC5952](https://datatracker.ietf.org/doc/html/rfc5952).
     */
    struct IPv6Address {
        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief IPv6 address group.
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
                 * @brief Group value packed into a `std::uint16_t`.
                 */
                std::uint16_t value;

                /**
                 * @brief Individual bytes of the group.
                 */
                std::array<std::uint8_t, static_cast<std::size_t>(2)> bytes;
            };
        };

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
                 * @brief Low 64-bits of the address packed into a `std::uint64_t`.
                 */
                std::uint64_t low64;

                /**
                 * @brief High 64-bits of the address packed into a `std::uint64_t`.
                 */
                std::uint64_t high64;
            };

            /**
             * @brief Individual 16-bit digits of the address.
             */
            std::array<uint16_t, static_cast<std::size_t>(8)> groups;

            /**
             * @brief Individual bytes of the address.
             */
            std::array<uint8_t, static_cast<std::size_t>(16)> bytes;

            /**
             * @brief Individual bits of the address.
             */
            std::bitset<static_cast<std::size_t>(128)> bits;
        };

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        IPv6Address() noexcept;

        /**
         * @brief Constructor with group array initializer.
         * @param[in] groups Groups.
         */
        IPv6Address(const std::array<std::uint16_t, static_cast<std::size_t>(8)> &groups) noexcept;

        /**
         * @brief Constructor with byte array initializer.
         * @param[in] bytes Bytes.
         */
        IPv6Address(const std::array<std::uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept;

        /**
         * @brief Constructor with bitset initializer.
         * @param[in] bits Bit set.
         */
        IPv6Address(const std::bitset<static_cast<std::size_t>(128)> &bits) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv6Address(const char *str) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @param[in] length Length of the string representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv6Address(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv6Address(const std::string &str) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Finds the largest zero sequence in the address.
         * @param[out] sequence Zero sequence indices (zero-based).
         * @return `true` if a sequence with at least one element is found, otherwise, `false`.
         * @remark If there are multiple zero-sequences, the first one or the one with the largest range is assigned to
         * `sequence`.
         * @remark For this function to return `true`, at least one of the values in `sequence` should have a value other
         * than `std::numeric_limits<std::size_t>::max()`. However, if no sequences are found but `sequence` had a value
         * previously assigned to it, those values might be preserved.
         * @remark If the second sequence equals to `std::numeric_limits<std::size_t>::max()`, this indicates that all
         * the fields starting from the first index (first value in `sequence`) are zero.
         */
        CRONZ_NODISCARD_L2 bool findLargestZeroSequence(std::pair<std::size_t, std::size_t> &sequence) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /**
         * @brief Stringifies the address.
         * @tparam Compress Whether to compress the output. If false, zero fields will be printed as well.
         * @return Stringification result. Upon failure, this will be empty.
         */
        template <bool Compress = true>
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the address.
         * @tparam Compress Whether to compress the output. If false, zero fields will be printed as well.
         * @param[out] str Stringification result.
         * @return `true` if the stringification is successful, otherwise, `false`.
         */
        template <bool Compress = true>
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Returns the stringified length of the address.
         * @tparam Compress Whether to compress the output. If false, zero fields will be printed as well.
         * @return The stringified length of the address.
         */
        template <bool Compress>
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Resets the container.
         * @remark Sets all values to `0`.
         */
        void reset() noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief @brief Tells whether the container contains a valid IPv6 address.
         * @return `true` if the container contains a valid IPv6 address, otherwise, `false`.
         * @remark Valid address refers to any non-`0.0.0.0` address.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /**
         * @brief Assigns a byte array as the address.
         * @param[in] bytes Byte array.
         * @return Reference to the current container.
         */
        IPv6Address& operator=(const std::array<std::uint8_t, static_cast<std::size_t>(16)> &bytes) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] bits Bit set.
         * @return Reference to the current container.
         */
        IPv6Address& operator=(const std::bitset<static_cast<std::size_t>(128)> &bits) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] str String representation of the address.
         * @return Reference to the current container.
         * @remark Upon failure during the parsing of `str`, the value is set to `0`.
         */
        IPv6Address& operator=(const char *str) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] str String representation of the address.
         * @return Reference to the current container.
         * @remark Upon failure during the parsing of `str`, the value is set to `0`.
         */
        IPv6Address& operator=(const std::string &str) noexcept;

        /**
         * @brief Tells if the container has the same value as another container.
         * @param[in] address Container to be compared with.
         * @return `true` if the container has the same value as the other container.
         */
        CRONZ_NODISCARD_L1 bool operator==(const IPv6Address &address) const noexcept;

        /**
         * @brief Tells if the container does not have the same value as another container.
         * @param[in] address Container to be compared with.
         * @return `true` if the container does not have the same value as the other container.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const IPv6Address &address) const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~IPv6Address() noexcept;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @return `IPv6Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv6Address Parse(const char *str) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @return `IPv6Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv6Address Parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @return `IPv6Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv6Address Parse(const std::string &str) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @param[out] address `IPv6Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const char *str, IPv6Address &address) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @param[out] address `IPv6Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         * @remark Upon failure, the value of `address` is preserved.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const char *str, const std::size_t &length, IPv6Address &address) noexcept;

        /**
         * @brief Parses an ipv6 string.
         * @param[in] str String to be parsed.
         * @param[out] address `IPv6Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const std::string &str, IPv6Address &address) noexcept;

        /**
         * @brief Stringifies the address.
         * @tparam Compress Whether to compress the output. If false, zero fields will be printed as well.
         * @param[in] address Address to be stringified.
         * @return Stringification result. Upon failure, this will be empty.
         */
        template <bool Compress = true>
        CRONZ_NODISCARD_L1 static std::string Stringify(const IPv6Address &address) noexcept;

        /**
         * @brief Stringifies the address.
         * @tparam Compress Whether to compress the output. If false, zero fields will be printed as well.
         * @param[in] address Address to be stringified.
         * @param[out] str Stringification result.
         * @return `true` if the stringification is successful, otherwise, `false`.
         */
        template <bool Compress = true>
        CRONZ_NODISCARD_L2 static bool Stringify(const IPv6Address &address, std::string &str) noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/ip/address/impl/v6.ipp"

#endif // CRONZ_IP_ADDRESS_V6_HPP
