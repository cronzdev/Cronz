/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_INTERNAL_STREAM_BASE_HPP
#define CRONZ_COMPRESSION_INTERNAL_STREAM_BASE_HPP 1

#include "cronz/compression/algorithm.hpp"
#include "cronz/compression/mode.hpp"

#include <limits>

CRONZ_BEGIN_MAIN_INTERNAL_NAMESPACE
    struct CompressionStreamContextImpl {
        // Constructor.
        CompressionStreamContextImpl() noexcept = default;

        // Properties.
        CRONZ_NODISCARD_L1 virtual constexpr CompressionAlgorithm algorithm() const noexcept = 0;

        CRONZ_NODISCARD_L1 virtual constexpr CompressionMode mode() const noexcept = 0;

        // Methods.
        CRONZ_NODISCARD_L1 virtual bool create() noexcept = 0;

        CRONZ_NODISCARD_L1 virtual bool process(const void *input, std::size_t inputSize, void *output,
                                                std::size_t &outputSize) noexcept = 0;

        CRONZ_NODISCARD_L1 virtual bool getRemainingData(void *output, std::size_t &outputSize) noexcept = 0;

        CRONZ_NODISCARD_L1 virtual bool hasMoreOutput() const noexcept = 0;

        virtual void destroy() noexcept = 0;

        // Destructor.
        virtual ~CompressionStreamContextImpl() = default;
    };

CRONZ_END_MAIN_INTERNAL_NAMESPACE

#include "cronz/compression/internal/stream/impl/base.ipp"

#endif // CRONZ_COMPRESSION_INTERNAL_STREAM_BASE_HPP
