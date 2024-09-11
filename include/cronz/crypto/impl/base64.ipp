/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_CRYPTO_IMPL_BASE64_HPP
#define CRONZ_CRYPTO_IMPL_BASE64_HPP 1

#include "cronz/crypto/base64.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

CRONZ_BEGIN_MODULE_NAMESPACE(Crypto)
    // Generic.
    inline bool IsInBase64Alphabet(const char &character, const Base64AlphabetType &alphabet) noexcept {
        return std::ranges::any_of(alphabet, [character](const auto &c) {
            return character == c;
        });
    }

    inline bool IsInBase64AlphabetIndicesMap(const char &character, const Base64IndicesMapType &alphabet) noexcept {
        return '\0' != alphabet[character];
    }

    // Encoding.
    template <bool Padded>
    inline std::size_t CalculateBase64EncodedLength(const std::size_t &length) noexcept {
        if (static_cast<std::size_t>(0) == length)
            return static_cast<std::size_t>(0);

        if constexpr (Padded) {
            const std::size_t len = CalculateBase64EncodedLength<false>(length);
            return (static_cast<std::size_t>(0) == (len % static_cast<std::size_t>(4)))
                       ? len
                       : (len + (static_cast<std::size_t>(4) - (len % static_cast<std::size_t>(4))));
        }

        else {
            return static_cast<std::size_t>(0) == (length % static_cast<std::size_t>(3))
                       ? (static_cast<std::size_t>(4) * (length / static_cast<std::size_t>(3)))
                       : static_cast<std::size_t>(std::ceil(
                               static_cast<float>(4.0) * static_cast<float>(length) / static_cast<float>(3.0)));
        }
    }

    inline std::size_t CalculateBase64EncodedLength(const std::size_t &length, const bool &padded) noexcept {
        return padded ? CalculateBase64EncodedLength<true>(length) : CalculateBase64EncodedLength<false>(length);
    }

    template <bool Padded>
    inline std::string Base64Encode(const void *data, const std::size_t &length,
                                    const Base64AlphabetType &alphabet) noexcept {
        std::string encoded;
        if (!Base64Encode<Padded>(data, length, encoded, alphabet))
            encoded.clear();

        return encoded;
    }

    inline std::string Base64Encode(const void *data, const std::size_t &length, const bool &padded,
                                    const Base64AlphabetType &alphabet) noexcept {
        return padded ? Base64Encode<true>(data, length, alphabet) : Base64Encode<false>(data, length, alphabet);
    }

    template <bool Padded>
    inline std::string Base64Encode(const std::string &str, const Base64AlphabetType &alphabet) noexcept {
        return Base64Encode<Padded>(str.c_str(), str.length(), alphabet);
    }

    inline std::string Base64Encode(const std::string &str, const bool &padded,
                                    const Base64AlphabetType &alphabet) noexcept {
        return Base64Encode(str.c_str(), str.length(), padded, alphabet);
    }

    template <bool Padded>
    inline bool Base64Encode(const void *data, const std::size_t &length, std::string &encoded,
                             const Base64AlphabetType &alphabet) noexcept {
        const std::size_t len = CalculateBase64EncodedLength<Padded>(length);

        try {
            encoded.resize(len);
        }
        catch (...) {
            return false;
        }

        const auto str = static_cast<const unsigned char*>(data);

        const unsigned char *const end = str + length;
        const unsigned char *pos = str;

        auto offset = static_cast<std::size_t>(0);
        while (end != pos) {
            auto c = static_cast<unsigned char>(*pos);

            encoded[offset++] = alphabet[(c >> 2) & 0x3F];
            encoded[offset++] = alphabet[(c << 4) + ((end != ++pos) ? ((c = *pos) >> 4) : 0)
                &
                0x3F];

            if constexpr (Padded) {
                encoded[offset++] = (end != pos)
                                        ? alphabet[(c << 2) + ((end != ++pos)
                                                                   ? ((c = *pos) >> 6)
                                                                   : 0) & 0x3F]
                                        : Base64PaddingCharacter;
                encoded[offset++] = (end != pos) ? alphabet[c & 0x3F] : Base64PaddingCharacter;

                pos = (end != pos) ? ++pos : pos;
            }
            else if (end != pos) {
                if (end != ++pos) {
                    encoded[offset++] = alphabet[(c << 2) + ((c = *pos) >> 6) & 0x3F];
                    encoded[offset++] = alphabet[c & 0x3F];

                    ++pos;
                }
                else {
                    encoded[offset++] = alphabet[(c << 2) & 0x3F];
                    encoded[offset++] = alphabet[c & 0x3F];
                }
            }
        }

        return true;
    }

    inline bool Base64Encode(const void *data, const std::size_t &length, std::string &encoded, const bool &padded,
                             const Base64AlphabetType &alphabet) noexcept {
        return padded
                   ? Base64Encode<true>(data, length, encoded, alphabet)
                   : Base64Encode<false>(data, length, encoded, alphabet);
    }

    template <bool Padded>
    inline bool Base64Encode(const std::string &str, std::string &encoded,
                             const Base64AlphabetType &alphabet) noexcept {
        return Base64Encode<Padded>(str.c_str(), str.length(), encoded, alphabet);
    }

    inline bool Base64Encode(const std::string &str, std::string &encoded, const bool &padded,
                             const Base64AlphabetType &alphabet) noexcept {
        return padded ? Base64Encode<true>(str, encoded, alphabet) : Base64Encode<false>(str, encoded, alphabet);
    }

    // Decoding.
    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline ReturnType Base64Decode(const char *encoded, const Base64IndicesMapType &alphabet) noexcept {
        std::string decoded;
        if (!Base64Decode<ReturnType>(encoded, std::strlen(encoded), decoded, alphabet))
            decoded.clear();

        return decoded;
    }

    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline ReturnType Base64Decode(const char *encoded, const std::size_t &length,
                                    const Base64IndicesMapType &alphabet) noexcept {
        std::string decoded;
        if (!Base64Decode<ReturnType>(encoded, length, decoded, alphabet))
            decoded.clear();

        return decoded;
    }

    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline ReturnType Base64Decode(const std::string &encoded, const Base64IndicesMapType &alphabet) noexcept {
        return Base64Decode<ReturnType>(encoded.c_str(), encoded.length(), alphabet);
    }

    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline bool Base64Decode(const char *encoded, ReturnType &decoded, const Base64IndicesMapType &alphabet) noexcept {
        return Base64Decode<ReturnType>(encoded, std::strlen(encoded), decoded, alphabet);
    }

    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline bool Base64Decode(const char *encoded, const std::size_t &length, ReturnType &decoded,
                             const Base64IndicesMapType &alphabet) noexcept {
        try {
            decoded.resize(length);
        }
        catch (...) {
            return false;
        }

        const auto u = reinterpret_cast<const unsigned char*>(encoded);

        const unsigned char *const end = u + length;
        const unsigned char *pos = u;

        auto offset = static_cast<std::size_t>(0);
        while (end != pos) {
            const std::size_t remaining = end - pos;
            if (static_cast<std::size_t>(2) > remaining)
                return false;

            unsigned char c[4] = {*pos, *++pos, '\0', '\0'};
            if (!IsInBase64AlphabetIndicesMap(static_cast<const char>(c[0]), alphabet) ||
                !IsInBase64AlphabetIndicesMap(static_cast<const char>(c[1]), alphabet))
                return false;

            decoded[offset++] = static_cast<ReturnType::value_type>((alphabet[c[0]] << 2) | (alphabet[c[1]] >> 4));

            if (end == ++pos)
                break;

            if ('=' == *pos)
                goto last_padding_test;

            c[2] = *pos;
            if (!IsInBase64AlphabetIndicesMap(static_cast<const char>(c[2]), alphabet))
                return false;

            decoded[offset++] = static_cast<ReturnType::value_type>(((alphabet[c[1]] << 4) & 0xF0) | (alphabet[c[2]] >>
                2));

            if (end == ++pos)
                break;

            if ('=' == *pos) {
                ++pos;
                break;
            }

            c[3] = *pos;

            decoded[offset++] = static_cast<ReturnType::value_type>(((alphabet[c[2]] << 6) & 0xC0) | alphabet[c[3]]);

            ++pos;
        }

    after_loop:

        decoded.resize(offset);

        return (end == pos);

    last_padding_test:
        if (end == ++pos || '=' != *pos)
            return false;

        ++pos;

        goto after_loop;
    }

    template <typename ReturnType>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    inline bool Base64Decode(const std::string &encoded, ReturnType &decoded,
                             const Base64IndicesMapType &alphabet) noexcept {
        return Base64Decode<ReturnType>(encoded.c_str(), encoded.length(), decoded, alphabet);
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_CRYPTO_IMPL_BASE64_HPP
