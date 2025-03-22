/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_DECODE_IPP
#define CRONZ_URI_IMPL_DECODE_IPP 1

#include "cronz/uri/decode.hpp"
#include <limits>

#include "cronz/rfc/rule/hexdig.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    inline std::size_t URLCalculateDecodedComponentLength(const std::string_view component) noexcept {
        std::size_t len = component.length();

        auto i = static_cast<std::size_t>(0);
        for (; i < component.length(); ++i) {
            if ('%' == component[i]) {
                if (!RFC::IsHexDig(component[i + 1]) || !RFC::IsHexDig(component[i + 2]))
                    return std::numeric_limits<std::size_t>::max();

                i += static_cast<std::size_t>(2);
                len -= static_cast<std::size_t>(2);
            }
        }

        if (i > component.length())
            return std::numeric_limits<std::size_t>::max();

        return len;
    }

    inline bool URLDecodeComponent(const std::string_view component, std::string &decoded) noexcept {
        auto offset = static_cast<std::size_t>(0);
        return URLDecodeComponent(component, decoded, offset);
    }

    inline bool URLDecodeComponent(const std::string_view component, std::string &decoded,
                                   std::size_t &offset) noexcept {
        const std::size_t decodedLength = URLCalculateDecodedComponentLength(component);
        if (const std::size_t length = (decodedLength + offset);
            decoded.size() < length) {
            try {
                decoded.resize(length);
            } catch (...) {
                return false;
            }
        }

        for (auto i = static_cast<std::size_t>(0); i < component.length(); ++i) {
            if (const char character = component[i];
                '%' == character) {
                if (!HexToByte(component[i + static_cast<std::size_t>(1)],
                               component[i + static_cast<std::size_t>(2)],
                               reinterpret_cast<std::uint8_t &>(decoded[offset++])))
                    return false;

                i += static_cast<std::size_t>(2);
            } else {
                decoded[offset++] = character;
            }
        }

        return true;
    }

    inline bool URLDecodeComponentInPlace(std::string &component) noexcept {
        const std::size_t decodedLength = URLCalculateDecodedComponentLength(component);
        const std::size_t encodedLength = component.length();

        if (std::numeric_limits<std::size_t>::max() == decodedLength)
            return false;

        if (decodedLength == encodedLength)
            return true;

        for (auto decodedIndex = static_cast<std::size_t>(0), encodedIndex = static_cast<std::size_t>(0);
             encodedIndex < encodedLength;
             ++decodedIndex, ++encodedIndex) {
            if (const char character = component[encodedIndex];
                '%' == character) {
                if (!HexToByte(component[encodedIndex + static_cast<std::size_t>(1)],
                               component[encodedIndex + static_cast<std::size_t>(2)],
                               reinterpret_cast<std::uint8_t &>(component[decodedIndex])))
                    return false;

                encodedIndex += static_cast<std::size_t>(2);
            } else {
                component[decodedIndex] = component[encodedIndex];
            }
        }

        component.resize(decodedLength);
        return true;
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_IMPL_DECODE_IPP
