/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_IMPL_ENCODE_IPP
#define CRONZ_URI_IMPL_ENCODE_IPP 1

#include "cronz/uri/encode.hpp"

#include "cronz/cryptography/hex.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    inline bool URIShouldEncode(const char character) noexcept {
        return !(('a' <= character && character <= 'z') || ('A' <= character && character <= 'Z') ||
                 ('0' <= character && character <= '9') || '-' == character || '_' == character ||
                 '.' == character || '!' == character || '~' == character || '*' == character ||
                 '\'' == character || '(' == character || ')' == character);
    }

    inline bool URIShouldEncodeComponent(const std::string_view component) noexcept {
        return std::ranges::any_of(component, [](const char character) -> bool {
            return URIShouldEncode(character);
        });
    }

    inline std::size_t URICalculateEncodedComponentLength(const std::string_view component) noexcept {
        std::size_t len = component.length();

        for (const char character: component) {
            if (URIShouldEncode(character))
                len += static_cast<std::size_t>(2);
        }

        return len;
    }

    inline bool URIEncodeComponent(const std::string_view component, std::string &encoded) noexcept {
        auto offset = static_cast<std::size_t>(0);
        return URIEncodeComponent(component, encoded, offset);
    }

    inline bool URIEncodeComponent(const std::string_view component, std::string &encoded,
                                   std::size_t &offset) noexcept {
        if (const std::size_t length = (URICalculateEncodedComponentLength(component) + offset);
            encoded.size() < length) {
            try {
                encoded.resize(length);
            } catch (...) {
                return false;
            }
        }

        for (auto i = static_cast<std::size_t>(0); i < component.length(); ++i) {
            if (const char character = component[i];
                URIShouldEncode(character)) {
                encoded[offset++] = '%';

                ByteToHex<true>(character, encoded[offset], encoded[offset + static_cast<std::size_t>(1)]);
                offset += static_cast<std::size_t>(2);
            } else {
                encoded[offset++] = character;
            }
        }

        return true;
    }

    inline bool URIEncodeComponentInPlace(std::string &component) noexcept {
        const std::size_t decodedLength = component.length();
        const std::size_t encodedLength = URICalculateEncodedComponentLength(component);

        if (decodedLength == encodedLength)
            return true;

        try {
            component.resize(encodedLength);
        } catch (...) {
            return false;
        }

        for (auto encodedIndex = encodedLength, decodedIndex = static_cast<std::size_t>(1);
             decodedIndex <= decodedLength;
             ++decodedIndex) {
            if (const char character = component[decodedLength - decodedIndex];
                URIShouldEncode(character)) {
                encodedIndex -= static_cast<std::size_t>(3);

                component[encodedIndex] = '%';
                ByteToHex<true>(character, component[encodedIndex + static_cast<std::size_t>(1)],
                                component[encodedIndex + static_cast<std::size_t>(2)]);
            } else {
                component[--encodedIndex] = character;
            }
        }

        return true;
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_IMPL_ENCODE_IPP
