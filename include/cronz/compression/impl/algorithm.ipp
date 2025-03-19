/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_IMPL_ALGORITHM_IPP
#define CRONZ_COMPRESSION_IMPL_ALGORITHM_IPP 1

#include "cronz/compression/algorithm.hpp"

CRONZ_BEGIN_MAIN_NAMESPACE
    // Constructors.
    inline CompressionAlgorithm::CompressionAlgorithm() noexcept : value(CompressionAlgorithm::Enum::None) {
    }

    inline CompressionAlgorithm::CompressionAlgorithm(const Enum algorithm) noexcept : value(algorithm) {
    }

    // Instance-based utility functions.
    inline bool CompressionAlgorithm::isSupported() const noexcept {
        return IsSupported(value);
    }

    // Operators.
    inline CompressionAlgorithm &CompressionAlgorithm::operator=(const Enum algorithm) noexcept {
        value = algorithm;
        return *this;
    }

    inline bool CompressionAlgorithm::operator==(const CompressionAlgorithm algorithm) const noexcept {
        return value == algorithm.value;
    }

    inline bool CompressionAlgorithm::operator==(const Enum algorithm) const noexcept {
        return value == algorithm;
    }

    inline bool CompressionAlgorithm::operator!=(const CompressionAlgorithm algorithm) const noexcept {
        return value != algorithm.value;
    }

    inline bool CompressionAlgorithm::operator!=(const Enum algorithm) const noexcept {
        return value != algorithm;
    }

    // Static utility functions.
    inline bool CompressionAlgorithm::IsSupported(const CompressionAlgorithm algorithm) noexcept {
        return IsSupported(algorithm.value);
    }

    inline bool CompressionAlgorithm::IsSupported(const Enum algorithm) noexcept {
#if CRONZ_ENABLE_BROTLI
        if (CompressionAlgorithm::Brotli == algorithm)
            return true;
#endif // CRONZ_ENABLE_BROTLI

#if CRONZ_ENABLE_ZLIB
        if (CompressionAlgorithm::Deflate == algorithm || CompressionAlgorithm::Gzip == algorithm)
            return true;
#endif // CRONZ_ENABLE_ZLIB

        return false;
    }

    template<CompressionAlgorithm::Enum Algorithm>
    inline constexpr bool CompressionAlgorithm::IsSupported() noexcept {
#if CRONZ_ENABLE_BROTLI
        if constexpr (CompressionAlgorithm::Brotli == Algorithm)
            return true;
#endif // CRONZ_ENABLE_BROTLI

#if CRONZ_ENABLE_ZLIB
        if constexpr (CompressionAlgorithm::Deflate == Algorithm || CompressionAlgorithm::Gzip == Algorithm)
            return true;
#endif // CRONZ_ENABLE_ZLIB

        return false;
    }

CRONZ_END_MAIN_NAMESPACE

#endif // CRONZ_COMPRESSION_IMPL_ALGORITHM_IPP
