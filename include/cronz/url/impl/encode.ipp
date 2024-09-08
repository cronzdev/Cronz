/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_IMPL_ENCODE_HPP
#define CRONZ_URL_IMPL_ENCODE_HPP 1

#include "cronz/url/encode.hpp"
#include "cronz/url/hex.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    inline bool ShouldEncodeCharacter(const char &character) noexcept {
        return !(('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z') || ('0' <= character
                && character <= '9') || '-' == character || '_' == character || '.' == character || '!' == character ||
            '~'
            == character || '*' == character || '\'' == character || '(' == character || ')' == character);
    }

    inline std::size_t CalculateEncodedLength(const std::string &decoded) noexcept {
        return CalculateEncodedLength(decoded.c_str(), decoded.size());
    }

    inline std::size_t CalculateEncodedLength(const char *decoded, const std::size_t &length) noexcept {
        auto l = static_cast<std::size_t>(0);
        for (auto i = static_cast<std::size_t>(0); i < length; ++i)
            l += ShouldEncodeCharacter(decoded[i]) ? static_cast<std::size_t>(3) : static_cast<std::size_t>(1);
        return l;
    }

    inline std::string Encode(const std::string &decoded) noexcept {
        return Encode(decoded.c_str(), decoded.length());
    }

    inline std::string Encode(const char *decoded, const std::size_t &length) noexcept {
        std::string encoded;
        [[maybe_unused]] const bool _ = Encode(decoded, length, encoded);
        return encoded;
    }

    inline bool Encode(const std::string &decoded, std::string &encoded) noexcept {
        return Encode(decoded.c_str(), decoded.length(), encoded);
    }

    inline std::size_t Encode(const std::string &decoded, char *encoded) noexcept {
        return Encode(decoded.c_str(), decoded.length(), encoded);
    }

    inline bool Encode(const char *decoded, const std::size_t &length, std::string &encoded) noexcept {
        const std::size_t encodedLength = CalculateEncodedLength(decoded, length);

        try {
            encoded.resize(encodedLength);
        }
        catch (...) {
            return false;
        }

        [[maybe_unused]] const std::size_t _ = Encode(decoded, length, encoded.data());
        return true;
    }

    inline std::size_t Encode(const char *decoded, const std::size_t &length, char *encoded) noexcept {
        auto j = static_cast<std::size_t>(0);
        for (auto i = static_cast<std::size_t>(0); i < length; ++i) {
            if (ShouldEncodeCharacter(decoded[i])) {
                encoded[j++] = '%';
                ByteToHex<false>(static_cast<std::uint8_t>(decoded[i]), encoded[j],
                                 encoded[j + static_cast<std::size_t>(1)]);
                j += static_cast<std::size_t>(2);
            }
            else {
                encoded[j++] = decoded[i];
            }
        }

        return j;
    }

    inline bool EncodeInPlace(std::string &str) noexcept {
        const std::size_t decodedLength = str.length();
        const std::size_t encodedLength = CalculateEncodedLength(str);
        if (encodedLength == decodedLength)
            return true;

        try {
            str.resize(encodedLength);
        }
        catch (...) {
            return false;
        }

        auto eIndex = encodedLength;
        for (auto dIndex = static_cast<std::size_t>(1); dIndex <= decodedLength; ++dIndex) {
            if (const char &c = str[decodedLength - dIndex]; ShouldEncodeCharacter(c)) {
                eIndex -= static_cast<std::size_t>(3);
                str[eIndex] = '%';
                ByteToHex<false>(static_cast<std::uint8_t>(c), str[eIndex + static_cast<std::size_t>(1)],
                                 str[eIndex + static_cast<std::size_t>(2)]);
            }
            else {
                str[--eIndex] = c;
            }
        }

        return true;
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_IMPL_ENCODE_HPP
