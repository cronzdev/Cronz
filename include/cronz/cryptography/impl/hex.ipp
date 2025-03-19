/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_CRYPTOGRAPHY_IMPL_HEX_IPP
#define CRONZ_CRYPTOGRAPHY_IMPL_HEX_IPP 1

#include "cronz/cryptography/hex.hpp"

#include "cronz/rfc/rule/hexdig.hpp"

CRONZ_BEGIN_MAIN_NAMESPACE
    inline bool IsHexDigit(const char nibble) noexcept {
        return RFC::IsHexDig(nibble);
    }

    inline std::uint8_t GetHexDigitValue(const char nibble) noexcept {
        if ('0' <= nibble && nibble <= '9')
            return nibble - '0';

        if ('a' <= nibble && nibble <= 'f')
            return nibble - 'a' + 10;

        if ('A' <= nibble && nibble <= 'F')
            return nibble - 'A' + 10;

        return std::numeric_limits<std::uint8_t>::max();
    }

    template<bool Uppercase>
    inline void ByteToHex(const std::uint8_t byte, char &n1, char &n2) noexcept {
        static constexpr std::array digits = Uppercase ? HexDigitsUppercase : HexDigitsLowercase;

        n1 = digits[(byte >> 4) & 0x0F];
        n2 = digits[byte & 0x0F];
    }

    inline void ByteToHex(const std::uint8_t byte, char &n1, char &n2, const bool uppercase) noexcept {
        return uppercase ? ByteToHex<true>(byte, n1, n2) : ByteToHex<false>(byte, n1, n2);
    }

    inline bool HexToByte(const char n1, const char n2, std::uint8_t &byte) noexcept {
        if (!IsHexDigit(n1) || !IsHexDigit(n2))
            return false;

        byte = (GetHexDigitValue(n1) << 4) | GetHexDigitValue(n2);
        return true;
    }

CRONZ_END_MAIN_NAMESPACE

#endif // CRONZ_CRYPTOGRAPHY_IMPL_HEX_IPP
