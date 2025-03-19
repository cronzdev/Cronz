/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_STREAM_HPP
#define CRONZ_COMPRESSION_STREAM_HPP 1

#include "cronz/compression/internal/stream/base.hpp"

CRONZ_BEGIN_MAIN_NAMESPACE
    class CompressionStreamContext final {
        // Properties.
        CRONZ_NAMESPACE_INTERNAL::CompressionStreamContextImpl *_context = nullptr;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         * @details The algorithm of the stream is set to None.
         */
        CompressionStreamContext() noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Gets the compression algorithm of the stream.
         * @return The compression algorithm of the stream.
         */
        CRONZ_NODISCARD_L1 CompressionAlgorithm algorithm() const noexcept;

        /**
         * @brief Gets the compression mode of the stream.
         * @return The compression mode of the stream.
         */
        CRONZ_NODISCARD_L1 CompressionMode mode() const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Initializes the stream with the given algorithm and mode.
         * @param[in] algorithm The algorithm to use.
         * @param[in] mode The mode to use.
         * @return `true` if the stream is initialized successfully.
         * @return `false` if the stream is not initialized successfully.
         * @details If the algorithm is not supported or the mode is None, the function returns `false`.
         * @details If the algorithm and the current algorithm are equal, and the mode is equal to the current mode,
         * the function returns `true`. Otherwise, the function initializes the stream with the given algorithm and mode.
         */
        CRONZ_NODISCARD_L2 bool initialize(CompressionAlgorithm algorithm, CompressionMode mode) noexcept;

        /**
         * @brief Processes the input data and writes the output data.
         * @tparam DataType The data type of the input and output data.
         * @param[in] input The input data.
         * @param[in] inputSize The size of the input data.
         * @param[out] output The output data.
         * @param[in, out] outputSize The size of the output data. The function sets the actual size of the output data.
         * Initially, the value is the size of the output buffer.
         * @return `true` if the data is processed successfully.
         * @return `false` if the data is not processed successfully.
         * @details The function processes the input data with the initialized algorithm and mode.
         */
        template<CompressionAlgorithmDataType DataType>
        CRONZ_NODISCARD_L2 bool process(const DataType *input, std::size_t inputSize, DataType *output,
                                        std::size_t &outputSize) noexcept;

        /**
         * @brief Flushes the remaining data.
         * @tparam DataType The data type of the output data.
         * @param[out] output The output data.
         * @param[in, out] outputSize The size of the output data. The function sets the actual size of the output data.
         * Initially, the value is the size of the output buffer.
         * @return `true` if the data is flushed successfully.
         * @return `false` if the data is not flushed successfully.
         * @details The function flushes the remaining data with the initialized algorithm and mode.
         */
        template<CompressionAlgorithmDataType DataType>
        CRONZ_NODISCARD_L2 bool getRemainingData(DataType *output, std::size_t &outputSize) noexcept;

        /**
         * @brief Checks whether the stream has more output data.
         * @return `true` if the stream has more output data.
         * @return `false` if the stream does not have more output data.
         */
        CRONZ_NODISCARD_L1 bool hasMoreOutput() const noexcept;

        /**
         * @brief Resets the stream.
         */
        void reset() noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         * @details Calls the reset function.
         */
        ~CompressionStreamContext() noexcept;

        /** @} */
    };

CRONZ_END_MAIN_NAMESPACE

#include "cronz/compression/impl/stream.ipp"

#endif // CRONZ_COMPRESSION_STREAM_HPP
