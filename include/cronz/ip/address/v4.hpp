/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_IP_ADDRESS_V4_HPP
#define CRONZ_IP_ADDRESS_V4_HPP 1

#include "cronz/ip/types.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>

CRONZ_BEGIN_IP_NAMESPACE
    /**
     * @ingroup ip_address
     * @brief IPv4 address structure.
     * @struct IPv4Address
     * @see [RFC1878](https://datatracker.ietf.org/doc/html/rfc1878).
     */
    struct IPv4Address {
        /**
         * @name Static type definitions and constants.
         */
        /** @{ */
        /**
         * @brief Mask value type.
         * @details The mask is used for CIDR notation.
         */
        using MaskValueType = std::int_fast8_t;

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
        inline static constexpr MaskValueType MinMaskValue = static_cast<MaskValueType>(0);

        /**
         * @brief Maximum mask value.
         */
        inline static constexpr MaskValueType MaxMaskValue = static_cast<MaskValueType>(32);

        /** @} */

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
        CRONZ_NODISCARD_L1 IPv4Address subnetMask() const noexcept;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        IPv4Address() noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] int32 Packed `std::int32_t` value.
         */
        explicit IPv4Address(std::int32_t int32) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] int32 Packed `std::int32_t` value.
         * @param[in] mask Mask value.
         * @note The address is reset if the mask is invalid.
         */
        IPv4Address(std::int32_t int32, MaskValueType mask) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] uint32 Packed `std::uint32_t` value.
         */
        explicit IPv4Address(std::uint32_t uint32) noexcept;

        /**
         * @brief Constructor with an initializer.
         * @param[in] uint32 Packed `std::uint32_t` value.
         * @param[in] mask Mask value.
         * @note The address is reset if the mask is invalid.
         */
        IPv4Address(std::uint32_t uint32, MaskValueType mask) noexcept;

        /**
         * @brief Constructor with byte initializers.
         * @param[in] byte1 First byte.
         * @param[in] byte2 Second byte.
         * @param[in] byte3 Third byte.
         * @param[in] byte4 Fourth byte.
         */
        IPv4Address(std::uint8_t byte1, std::uint8_t byte2, std::uint8_t byte3, std::uint8_t byte4) noexcept;

        /**
         * @brief Constructor with byte initializers.
         * @param[in] byte1 First byte.
         * @param[in] byte2 Second byte.
         * @param[in] byte3 Third byte.
         * @param[in] byte4 Fourth byte.
         * @param[in] mask Mask value.
         * @note The address is reset if the mask is invalid.
         */
        IPv4Address(std::uint8_t byte1, std::uint8_t byte2, std::uint8_t byte3, std::uint8_t byte4,
                    MaskValueType mask) noexcept;

        /**
         * @brief Constructor with byte array initializer.
         * @param[in] bytes Bytes.
         */
        explicit(true) IPv4Address(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept;

        /**
         * @brief Constructor with byte array initializer.
         * @param[in] bytes Bytes.
         * @param[in] mask Mask value.
         * @note The address is reset if the mask is invalid.
         */
        IPv4Address(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes, MaskValueType mask) noexcept;

        /**
         * @brief Constructor with string initializer.
         * @param[in] address Address string.
         */
        explicit(true) IPv4Address(std::string_view address) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Parse an IPv4 address from a string.
         * @param[in] address Address string.
         * @return `true` if the address is parsed successfully.
         * @return `false` if the address is invalid or parsing fails.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view address) noexcept;

        /**
         * @brief Convert the address to a string.
         * @return String representation of the address.
         * @return Empty string if the conversion fails.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Convert the address to a string.
         * @param[out] str String representation of the address.
         * @param[in] offset Offset to start writing the address.
         * @return `true` if the conversion is successful.
         * @return `false` if the conversion fails.
         * @note The output string is cleared before appending the address.
         * @note The output string is not cleared if the conversion fails.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str,
                                          std::size_t offset = static_cast<std::size_t>(0)) const noexcept;

        /**
         * @brief Get the length of the string representation.
         * @return Length of the string representation.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Reset the address to zero.
         */
        void reset() noexcept;

        /**
         * @brief Reverse the address bytes.
         */
        void reverse() noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Array subscript operator.
         * @param[in] index Index.
         * @return Reference to the byte at the specified index.
         */
        CRONZ_NODISCARD_L1 constexpr std::uint8_t &operator[](std::size_t index) noexcept;

        /**
         * @brief Array subscript operator.
         * @param[in] index Index.
         * @return Byte at the specified index.
         */
        CRONZ_NODISCARD_L1 constexpr std::uint8_t operator[](std::size_t index) const noexcept;

        /**
         * @brief Conversion operator to `bool`.
         * @return `true` if the address is valid.
         * @return `false` if the address is invalid.
         * @note The address is invalid if it is zero.
         * @note The mask is not considered for validity.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Conversion operator to `std::int32_t`.
         * @return Packed `std::int32_t` value.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::int32_t() const noexcept;

        /**
         * @brief Conversion operator to `std::uint32_t`.
         * @return Packed `std::uint32_t` value.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::uint32_t() const noexcept;

        /**
         * @brief Conversion operator to byte array.
         * @return Bytes.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::array<std::uint8_t, static_cast<std::size_t>(
            4)>() const noexcept;

        /**
         * @brief Conversion operator to string.
         * @return String representation of the address.
         * @note The conversion is done using `stringify()`.
         * @see stringify()
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::string() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] int32 Packed `std::int32_t` value.
         * @return Reference to the modified instance.
         * @note The mask is reset to `EmptyMaskValue`.
         */
        IPv4Address &operator=(const std::int32_t &int32) noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] uint32 Packed `std::uint32_t` value.
         * @return Reference to the modified instance.
         * @note The mask is reset to `EmptyMaskValue`.
         */
        IPv4Address &operator=(const std::uint32_t &uint32) noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] bytes Bytes.
         * @return Reference to the modified instance.
         * @note The mask is reset to `EmptyMaskValue`.
         */
        IPv4Address &operator=(const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] address Address string.
         * @return Reference to the modified instance.
         */
        IPv4Address &operator=(std::string_view address) noexcept;

        /**
         * @brief Equality operator.
         * @param[in] int32 Packed `std::int32_t` value.
         * @return `true` if the addresses are equal.
         * @return `false` if the addresses are not equal.
         * @note The mask is not considered for equality.
         */
        CRONZ_NODISCARD_L1 bool operator==(const std::int32_t &int32) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] uint32 Packed `std::uint32_t` value.
         * @return `true` if the addresses are equal.
         * @return `false` if the addresses are not equal.
         * @note The mask is not considered for equality.
         */
        CRONZ_NODISCARD_L1 bool operator==(const std::uint32_t &uint32) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] bytes Bytes.
         * @return `true` if the addresses are equal.
         * @return `false` if the addresses are not equal.
         * @note The mask is not considered for equality.
         */
        CRONZ_NODISCARD_L1 bool operator==(
            const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] address Address string.
         * @return `true` if the addresses are equal.
         * @return `false` if the addresses are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(std::string_view address) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] other Other address.
         * @return `true` if the addresses are equal.
         * @return `false` if the addresses are not equal.
         * @note The mask is considered for equality.
         */
        CRONZ_NODISCARD_L1 bool operator==(const IPv4Address &other) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] int32 Packed `std::int32_t` value.
         * @return `true` if the addresses are not equal.
         * @return `false` if the addresses are equal.
         * @note The mask is not considered for inequality.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const std::int32_t &int32) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] uint32 Packed `std::uint32_t` value.
         * @return `true` if the addresses are not equal.
         * @return `false` if the addresses are equal.
         * @note The mask is not considered for inequality.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const std::uint32_t &uint32) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] bytes Bytes.
         * @return `true` if the addresses are not equal.
         * @return `false` if the addresses are equal.
         * @note The mask is not considered for inequality.
         */
        CRONZ_NODISCARD_L1 bool operator!=(
            const std::array<std::uint8_t, static_cast<std::size_t>(4)> &bytes) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] address Address string.
         * @return `true` if the addresses are not equal.
         * @return `false` if the addresses are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(std::string_view address) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] other Other address.
         * @return `true` if the addresses are not equal.
         * @return `false` if the addresses are equal.
         * @note The mask is considered for inequality.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const IPv4Address &other) const noexcept;

        /** @} */

        /**
         * @name Friend operators.
         */
        /** @{ */
        /**
         * @brief Equality operator.
         * @tparam T Value type.
         * @param[in] value Value.
         * @param[in] instance Instance.
         * @return `true` if the values are equal.
         * @return `false` if the values are not equal.
         */
        template<typename T>
        friend bool operator==(const T &value, const IPv4Address &instance) noexcept;

        /**
         * @brief Inequality operator.
         * @tparam T Value type.
         * @param[in] value Value.
         * @param[in] instance Instance.
         * @return `true` if the values are not equal.
         * @return `false` if the values are equal.
         */
        template<typename T>
        friend bool operator!=(const T &value, const IPv4Address &instance) noexcept;

        /** @} */
    };

CRONZ_END_IP_NAMESPACE

#include "cronz/ip/address/impl/v4.ipp"

#endif // CRONZ_IP_ADDRESS_V4_HPP
