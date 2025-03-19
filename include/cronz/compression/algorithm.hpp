/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_ALGORITHM_HPP
#define CRONZ_COMPRESSION_ALGORITHM_HPP 1

#include "cronz/compression/types.hpp"

#include <array>

CRONZ_BEGIN_MAIN_NAMESPACE
    /**
     * @ingroup compression
     * @brief A class that represents the compression algorithms.
     * @class CompressionAlgorithm
     */
    class CompressionAlgorithm final {
    public:
        /**
         * @brief An enumeration that represents the compression algorithms.
         * @enum CompressionAlgorithm::Enum
         */
        enum Enum : char {
            /**
             * @brief No compression.
             */
            None = '\0',

            /**
             * @brief Brotli compression.
             */
            Brotli = 'b',

            /**
             * @brief Deflate compression.
             */
            Deflate = 'd',

            /**
             * @brief GZip compression.
             */
            Gzip = 'g',

            /**
             * @brief LZW compression.
             */
            LZW = 'l',

            /**
             * @brief Z-standard compression.
             */
            Zstd = 'z'
        };

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief The compression algorithm.
         */
        Enum value;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        CompressionAlgorithm() noexcept;

        /**
         * @brief Constructor with algorithm.
         * @param[in] algorithm The compression algorithm.
         */
        explicit(false) CompressionAlgorithm(Enum algorithm) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Checks whether the current algorithm is supported.
         * @return `true` if the algorithm is supported.
         * @return `false` if the algorithm is not supported.
         */
        CRONZ_NODISCARD_L1 bool isSupported() const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Assigns the given algorithm to the current algorithm.
         * @param[in] algorithm The algorithm to assign.
         */
        CompressionAlgorithm &operator=(Enum algorithm) noexcept;

        /**
         * @brief Checks whether the given algorithm is equal to the current algorithm.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithms are equal.
         * @return `false` if the algorithms are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(CompressionAlgorithm algorithm) const noexcept;

        /**
         * @brief Checks whether the given algorithm is equal to the current algorithm.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithms are equal.
         * @return `false` if the algorithms are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(Enum algorithm) const noexcept;

        /**
         * @brief Checks whether the given algorithm is not equal to the current algorithm.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithms are not equal.
         * @return `false` if the algorithms are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(CompressionAlgorithm algorithm) const noexcept;

        /**
         * @brief Checks whether the given algorithm is not equal to the current algorithm.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithms are not equal.
         * @return `false` if the algorithms are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(Enum algorithm) const noexcept;

        /** @} */

        /**
         * @name Destructors.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~CompressionAlgorithm() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */
        /**
         * @brief Checks whether the given algorithm is supported.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithm is supported.
         * @return `false` if the algorithm is not supported.
         */
        CRONZ_NODISCARD_L1 static bool IsSupported(CompressionAlgorithm algorithm) noexcept;

        /**
         * @brief Checks whether the given algorithm is supported.
         * @param[in] algorithm The algorithm to check.
         * @return `true` if the algorithm is supported.
         * @return `false` if the algorithm is not supported.
         */
        CRONZ_NODISCARD_L1 static bool IsSupported(Enum algorithm) noexcept;

        /**
         * @brief Checks whether the given algorithm is supported.
         * @tparam Algorithm The algorithm to check.
         * @return `true` if the algorithm is supported.
         * @return `false` if the algorithm is not supported.
         */
        template<Enum Algorithm>
        CRONZ_NODISCARD_L1 static constexpr bool IsSupported() noexcept;

        /** @} */

        /**
         * @name Static member variables.
         */
        /** @{ */
        /**
         * @brief An array that contains all the algorithms.
         */
        static constexpr std::array Algorithms = {Brotli, Deflate, Gzip, LZW, Zstd};

        /** @} */

        /**
         * @name Friends.
         */
        /** @{ */
        friend bool operator==(Enum algorithm, CompressionAlgorithm instance) noexcept;

        friend bool operator!=(Enum algorithm, CompressionAlgorithm instance) noexcept;

        /** @} */
    };

    CRONZ_NODISCARD_L1 inline bool operator==(const CompressionAlgorithm::Enum algorithm,
                                              const CompressionAlgorithm instance) noexcept {
        return algorithm == instance.value;
    }

    CRONZ_NODISCARD_L1 inline bool operator!=(const CompressionAlgorithm::Enum algorithm,
                                              const CompressionAlgorithm instance) noexcept {
        return algorithm != instance.value;
    }

CRONZ_END_MAIN_NAMESPACE

#include "cronz/compression/impl/algorithm.ipp"

#endif // CRONZ_COMPRESSION_ALGORITHM_HPP
