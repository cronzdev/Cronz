/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_CRYPTOGRAPHY_HEX_HPP
#define CRONZ_CRYPTOGRAPHY_HEX_HPP 1

#include "cronz/cryptography/types.hpp"

/**
 * @defgroup cronz_cryptography_hex Hex
 * @ingroup cronz_cryptography
 */

CRONZ_BEGIN_MAIN_NAMESPACE
    /**
     * @ingroup cronz_cryptography_hex
     * @brief Array of hexadecimal digits in lowercase.
     */
    inline static constexpr std::array<char, static_cast<std::size_t>(16)> HexDigitsLowercase = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    /**
     * @ingroup cronz_cryptography_hex
     * @brief Array of hexadecimal digits in uppercase.
     */
    inline static constexpr std::array<char, static_cast<std::size_t>(16)> HexDigitsUppercase = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    /**
     * @ingroup cronz_cryptography_hex
     * @brief Check if a character is a hexadecimal digit.
     * @param[in] nibble The character to check.
     * @return `true` if the character is a hexadecimal digit.
     * @return `false` if the character is not a hexadecimal digit.
     */
    CRONZ_NODISCARD_L1 bool IsHexDigit(char nibble) noexcept;

    /**
     * @ingroup cronz_cryptography_hex
     * @brief Get the value of a hexadecimal digit.
     * @param[in] nibble The hexadecimal digit.
     * @return The value of the hexadecimal digit.
     * @return `std::numeric_limits<std::uint8_t>::max()` if the character is not a hexadecimal digit.
     */
    CRONZ_NODISCARD_L1 std::uint8_t GetHexDigitValue(char nibble) noexcept;

    /**
     * @ingroup cronz_cryptography_hex
     * @brief Convert a byte to a hexadecimal representation.
     * @tparam Uppercase Whether to use uppercase hexadecimal digits. Default is `false`.
     * @param[in] byte The byte to convert.
     * @param[out] n1 The first hexadecimal digit.
     * @param[out] n2 The second hexadecimal digit.
     */
    template<bool Uppercase = false>
    void ByteToHex(std::uint8_t byte, char &n1, char &n2) noexcept;

    /**
     * @ingroup cronz_cryptography_hex
     * @brief Convert a byte to a hexadecimal representation.
     * @param[in] byte The byte to convert.
     * @param[out] n1 The first hexadecimal digit.
     * @param[out] n2 The second hexadecimal digit.
     * @param[in] uppercase Whether to use uppercase hexadecimal digits.
     */
    void ByteToHex(std::uint8_t byte, char &n1, char &n2, bool uppercase) noexcept;

    CRONZ_NODISCARD_L2 bool HexToByte(char n1, char n2, std::uint8_t &byte) noexcept;

CRONZ_END_MAIN_NAMESPACE

#include "cronz/cryptography/impl/hex.ipp"

#endif // CRONZ_CRYPTOGRAPHY_HEX_HPP
