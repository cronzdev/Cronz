/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_IMPL_DECODE_HPP
#define CRONZ_URL_IMPL_DECODE_HPP 1

#include "cronz/url/decode.hpp"
#include "cronz/crypto/hex.hpp"

#include <limits>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    inline std::size_t CalculateDecodedLength(const std::string &encoded) noexcept {
        return CalculateDecodedLength(encoded.c_str(), encoded.length());
    }

    inline std::size_t CalculateDecodedLength(const char *encoded, const std::size_t &length) noexcept {
        auto l = static_cast<std::size_t>(0);
        auto i = static_cast<std::size_t>(0);
        for (; i < length; ++i) {
            if ('%' == encoded[i])
                i += static_cast<std::size_t>(2);

            ++l;
        }

        if (i > length)
            return std::numeric_limits<std::size_t>::max();

        return l;
    }

    inline std::string Decode(const std::string &encoded) noexcept {
        return Decode(encoded.c_str(), encoded.length());
    }

    inline std::string Decode(const char *encoded, const std::size_t &length) noexcept {
        std::string decoded;
        [[maybe_unused]] const bool _ = Decode(encoded, length, decoded);
        return decoded;
    }

    inline bool Decode(const std::string &encoded, std::string &decoded) noexcept {
        return Decode(encoded.c_str(), encoded.length(), decoded);
    }

    inline bool Decode(const char *encoded, const std::size_t &length, std::string &decoded) noexcept {
        const std::size_t decodedLength = CalculateDecodedLength(encoded, length);
        if (std::numeric_limits<std::size_t>::max() == decodedLength)
            return false;

        try {
            decoded.resize(decodedLength);
        }
        catch (...) {
            return false;
        }

        auto j = static_cast<std::size_t>(0);
        for (auto i = static_cast<std::size_t>(0); i < length; ++i) {
            if ('%' == encoded[i]) {
                if (!Crypto::HexToByte(encoded[i + static_cast<std::size_t>(1)],
                                       encoded[i + static_cast<std::size_t>(2)],
                                       reinterpret_cast<std::uint8_t&>(decoded[j])))
                    return false;

                i += static_cast<std::size_t>(2);
            }
            else {
                decoded[j] = encoded[i];
            }

            ++j;
        }

        return true;
    }

    inline bool DecodeInPlace(std::string &str) noexcept {
        auto dIndex = static_cast<std::size_t>(0);
        for (auto eIndex = static_cast<std::size_t>(0); eIndex < str.size(); ++eIndex, ++dIndex) {
            if ('%' == str[eIndex]) {
                if (!Crypto::HexToByte(str[eIndex + static_cast<std::size_t>(1)],
                                       str[eIndex + static_cast<std::size_t>(2)],
                                       reinterpret_cast<std::uint8_t&>(str[dIndex])))
                    return false;

                eIndex += static_cast<std::size_t>(2);
            }
            else {
                str[dIndex] = str[eIndex];
            }
        }

        try {
            str.resize(dIndex);
        }
        catch (...) {
            return false;
        }

        return true;
    }

CRONZ_END_MODULE_NAMESPACE

#endif // CRONZ_URL_IMPL_DECODE_HPP
