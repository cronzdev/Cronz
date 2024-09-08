/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_V4_HPP
#define CRONZ_IP_ADDRESS_V4_HPP 1

#include "cronz/ip/types.hpp"

#include <array>
#include <bitset>
#include <cstdint>
#include <string>

CRONZ_BEGIN_MODULE_NAMESPACE(IP)
    /**
     * @ingroup cronz_ip_address
     * @brief IPv4 address container.
     * @struct IPv4Address
     */
    struct IPv4Address {
        /**
         * @name Properties.
         */
        /** @{ */
        union {
            /**
             * @brief Address bytes packed in a `std::int32_t`.
             */
            std::int32_t int32;

            /**
             * @brief Address bytes packed in a `std::uint32_t`.
             */
            std::uint32_t uint32;

            /**
             * @brief Individual bytes of the address.
             */
            std::array<std::uint8_t, static_cast<std::size_t>(4)> bytes;

            /**
             * @brief Individual bits of the address.
             */
            std::bitset<static_cast<std::size_t>(32)> bits;
        };

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        IPv4Address() noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] int32 Packed `std::int32_t` value.
         */
        IPv4Address(const std::int32_t &int32) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] uint32 Packed `std::uint32_t` value.
         */
        IPv4Address(const std::uint32_t &uint32) noexcept;

        /**
         * @brief Constructor with byte initializers.
         * @param[in] byte1 First byte.
         * @param[in] byte2 Second byte.
         * @param[in] byte3 Third byte.
         * @param[in] byte4 Fourth byte.
         */
        IPv4Address(const std::uint8_t &byte1, const std::uint8_t &byte2, const std::uint8_t &byte3,
                    const std::uint8_t &byte4) noexcept;

        /**
         * @brief Constructor with byte array initializer.
         * @param[in] bytes Bytes.
         */
        IPv4Address(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept;

        /**
         * @brief Constructor with bitset initializer.
         * @param[in] bits Bit set.
         */
        IPv4Address(const std::bitset<static_cast<std::size_t>(32)> &bits) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv4Address(const char *str) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @param[in] length Length of the string representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv4Address(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] str String representation of the address.
         * @remark This will internally call `parse` and depending on the output the container might have a `0` value.
         */
        IPv4Address(const std::string &str) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /**
         * @brief Stringifies the address.
         * @return Stringification result. Upon failure, this will be empty.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the address.
         * @param[out] str Stringification result.
         * @return `true` if the stringification is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Returns the stringified length of the address.
         * @return The stringified length of the address.
         */
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
         * @brief @brief Tells whether the container contains a valid IPv4 address.
         * @return `true` if the container contains a valid IPv4 address, otherwise, `false`.
         * @remark Valid address refers to any non-`0.0.0.0` address.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /**
         * @brief Assigns a packed `std::int32_t` value as the address.
         * @param[in] int32 Packed `std::int32_t` value.
         * @return Reference to the current container.
         */
        IPv4Address& operator=(const std::int32_t &int32) noexcept;

        /**
         * @brief Assigns a packed `std::uint32_t` value as the address.
         * @param[in] uint32 Packed `std::uint32_t` value.
         * @return Reference to the current container.
         */
        IPv4Address& operator=(const std::uint32_t &uint32) noexcept;

        /**
         * @brief Assigns a byte array as the address.
         * @param[in] bytes Byte array.
         * @return Reference to the current container.
         */
        IPv4Address& operator=(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] bits Bit set.
         * @return Reference to the current container.
         */
        IPv4Address& operator=(const std::bitset<static_cast<std::size_t>(32)> &bits) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] str String representation of the address.
         * @return Reference to the current container.
         * @remark Upon failure during the parsing of `str`, the value is set to `0`.
         */
        IPv4Address& operator=(const char *str) noexcept;

        /**
         * @brief Assigns a bit set as the address.
         * @param[in] str String representation of the address.
         * @return Reference to the current container.
         * @remark Upon failure during the parsing of `str`, the value is set to `0`.
         */
        IPv4Address& operator=(const std::string &str) noexcept;

        /**
         * @brief Tells if the container has the same value as another container.
         * @param[in] address Container to be compared with.
         * @return `true` if the container has the same value as the other container.
         */
        CRONZ_NODISCARD_L1 bool operator==(const IPv4Address &address) const noexcept;

        /**
         * @brief Tells if the container does not have the same value as another container.
         * @param[in] address Container to be compared with.
         * @return `true` if the container does not have the same value as the other container.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const IPv4Address &address) const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~IPv4Address() noexcept;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @return `IPv4Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv4Address Parse(const char *str) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @return `IPv4Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv4Address Parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @return `IPv4Address` container with the parsed result.
         * @remark Upon failure, the returned container's content will be empty (equals to `0`).
         */
        CRONZ_NODISCARD_L1 static IPv4Address Parse(const std::string &str) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @param[out] address `IPv4Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const char *str, IPv4Address &address) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @param[in] length Length of the string to be parsed.
         * @param[out] address `IPv4Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         * @remark Upon failure, the value of `address` is preserved.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const char *str, const std::size_t &length, IPv4Address &address) noexcept;

        /**
         * @brief Parses an ipv4 string.
         * @param[in] str String to be parsed.
         * @param[out] address `IPv4Address` container to be overwritten with the parsed result.
         * @return `true` if parsing is done successfully, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 static bool Parse(const std::string &str, IPv4Address &address) noexcept;

        /**
         * @brief Stringifies the address.
         * @param[in] address Address to be stringified.
         * @return Stringification result. Upon failure, this will be empty.
         */
        CRONZ_NODISCARD_L1 static std::string Stringify(const IPv4Address &address) noexcept;

        /**
         * @brief Stringifies the address.
         * @param[in] address Address to be stringified.
         * @param[out] str Stringification result.
         * @return `true` if the stringification is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 static bool Stringify(const IPv4Address &address, std::string &str) noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/ip/address/impl/v4.ipp"

#endif // CRONZ_IP_ADDRESS_V4_HPP
