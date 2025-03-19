/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_IMPL_STREAM_IPP
#define CRONZ_COMPRESSION_IMPL_STREAM_IPP 1

#include "cronz/compression/stream.hpp"

#include "cronz/compression/internal/stream/brotli.hpp"
#include "cronz/compression/internal/stream/deflate.hpp"

CRONZ_BEGIN_MAIN_NAMESPACE
    // Constructors.

    inline CompressionStreamContext::CompressionStreamContext() noexcept = default;

    // Properties.

    inline CompressionAlgorithm CompressionStreamContext::algorithm() const noexcept {
        return nullptr != _context ? _context->algorithm() : CompressionAlgorithm::None;
    }

    inline CompressionMode CompressionStreamContext::mode() const noexcept {
        return nullptr != _context ? _context->mode() : CompressionMode::None;
    }

    // Instance-based utility functions.

    inline bool CompressionStreamContext::initialize(const CompressionAlgorithm algorithm,
                                                     const CompressionMode mode) noexcept {
        if (!algorithm.isSupported() || CompressionMode::None == mode)
            return false;

        if (this->algorithm() == algorithm && this->mode() == mode)
            return true;

#if CRONZ_ENABLE_BROTLI
        if (CompressionAlgorithm::Brotli == algorithm) {
            if (CompressionMode::Compress == mode)
                _context = new(std::nothrow) CRONZ_NAMESPACE_INTERNAL::CompressionStreamContextImplBrotliEnc();
            else if (CompressionMode::Decompress == mode)
                _context = new(std::nothrow) CRONZ_NAMESPACE_INTERNAL::CompressionStreamContextImplBrotliDec();
        }
#endif // CRONZ_ENABLE_BROTLI

#if CRONZ_ENABLE_ZLIB
        if (CompressionAlgorithm::Deflate == algorithm) {
            if (CompressionMode::Compress == mode)
                _context = new(std::nothrow) CRONZ_NAMESPACE_INTERNAL::CompressionStreamContextImplDeflateEnc();
            else if (CompressionMode::Decompress == mode)
                _context = new(std::nothrow) CRONZ_NAMESPACE_INTERNAL::CompressionStreamContextImplDeflateDec();
        }
#endif // CRONZ_ENABLE_ZLIB

        if (nullptr != _context && !_context->create()) {
            delete _context;
            _context = nullptr;
        }

        return nullptr != _context;
    }

    template<CompressionAlgorithmDataType DataType>
    inline bool CompressionStreamContext::process(const DataType *input, const std::size_t inputSize,
                                                  DataType *output, std::size_t &outputSize) noexcept {
        if (static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()) < inputSize ||
            static_cast<std::size_t>(0) == inputSize || nullptr == input)
            return false;

        if (static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()) < outputSize)
            return false;

        if (nullptr == output && static_cast<std::size_t>(0) != outputSize)
            return false;

        return nullptr != _context && _context->process(input, inputSize, output, outputSize);
    }

    template<CompressionAlgorithmDataType DataType>
    inline bool CompressionStreamContext::getRemainingData(DataType *output, std::size_t &outputSize) noexcept {
        if (static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()) < outputSize)
            return false;

        if (nullptr == output || static_cast<std::size_t>(0) == outputSize)
            return false;

        return nullptr != _context && _context->getRemainingData(output, outputSize);
    }

    inline bool CompressionStreamContext::hasMoreOutput() const noexcept {
        return nullptr != _context && _context->hasMoreOutput();
    }

    inline void CompressionStreamContext::reset() noexcept {
        if (nullptr != _context) {
            _context->destroy();
            delete _context;
            _context = nullptr;
        }
    }

    // Destructor.
    inline CompressionStreamContext::~CompressionStreamContext() noexcept {
        reset();
    }

CRONZ_END_MAIN_NAMESPACE

#endif // CRONZ_COMPRESSION_IMPL_STREAM_IPP
