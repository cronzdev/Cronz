/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_HEX_HPP
#define CRONZ_URL_HEX_HPP 1

/**
 * @defgroup cronz_url_hex HEX
 * @ingroup cronz_url
 */

#include "cronz/url/types.hpp"

#include <array>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @brief Array that contains lowercase hex digits.
     * @ingroup cronz_url_hex
     */
    inline static constexpr std::array HexDigitsLowercase = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    /**
     * @brief Array that contains uppercase hex digits.
     * @ingroup cronz_url_hex
     */
    inline static constexpr std::array HexDigitsUppercase = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    /**
     * @brief Tells if a nibble is a valid hex digit.
     * @param[in] nibble Nibble to be tested.
     * @return `true` if the nibble is a valid hex digit, otherwise, `false`.
     * @ingroup cronz_url_hex
     */
    [[nodiscard]] bool IsHexDigit(const char &nibble) noexcept;

    /**
     * @brief Converts a nibble to a byte.
     * @param[in] nibble Nibble to be converted.
     * @return Byte representation of the nibble.
     * @ingroup cronz_url_hex
     * @remark If the `nibble` is an invalid hex digit, returns `0`.
     */
    [[nodiscard]] std::uint8_t GetHexDigitValue(const char &nibble) noexcept;

    /**
     * @brief Converts a byte to two nibbles.
     * @tparam Lowercase If `true`, the nibbles will have lowercase values. If `false`, they will have uppercase values.
     * Defaults to `false`.
     * @param[in] byte Byte to be converted.
     * @param[out] n1 First nibble.
     * @param[out] n2 Second nibble.
     * @ingroup cronz_url_hex
     */
    template <bool Lowercase = false>
    void ByteToHex(const std::uint8_t &byte, char &n1, char &n2) noexcept;

    /**
     * @brief Converts two nibbles to a byte.
     * @param[in] n1 First nibble.
     * @param[in] n2 Second nibble.
     * @param[out] byte Output byte.
     * @return `true` if both nibbles are valid hex digits, otherwise, `false`.
     * @ingroup cronz_url_hex
     */
    [[nodiscard]] bool HexToByte(const char &n1, const char &n2, std::uint8_t &byte) noexcept;

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/impl/hex.ipp"

#endif // CRONZ_URL_HEX_HPP
