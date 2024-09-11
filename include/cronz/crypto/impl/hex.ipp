/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_CRYPTO_IMPL_HEX_HPP
#define CRONZ_CRYPTO_IMPL_HEX_HPP 1

#include "cronz/crypto/hex.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(Crypto)
    inline bool IsHexDigit(const char &nibble) noexcept {
        return ('0' <= nibble && nibble <= '9') || ('a' <= nibble && nibble <= 'f') || ('A' <= nibble && nibble <= 'F');
    }

    inline std::uint8_t GetHexDigitValue(const char &nibble) noexcept {
        if ('0' <= nibble && nibble <= '9')
            return nibble - '0';

        if ('a' <= nibble && nibble <= 'f')
            return nibble - 'a' + 10;

        if ('A' <= nibble && nibble <= 'F')
            return nibble - 'A' + 10;

        return static_cast<std::uint8_t>(0);
    }

    template <bool Lowercase>
    inline void ByteToHex(const std::uint8_t &byte, char &n1, char &n2) noexcept {
        static constexpr std::array digits = Lowercase ? HexDigitsLowercase : HexDigitsUppercase;

        n1 = digits[(byte >> 4) & 0x0F];
        n2 = digits[byte & 0x0F];
    }

    inline bool HexToByte(const char &n1, const char &n2, std::uint8_t &byte) noexcept {
        if (!IsHexDigit(n1) || !IsHexDigit(n2))
            return false;

        byte = (GetHexDigitValue(n1) << 4) | GetHexDigitValue(n2);
        return true;
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_CRYPTO_IMPL_HEX_HPP
