/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_MODE_HPP
#define CRONZ_COMPRESSION_MODE_HPP 1

#include "cronz/compression/types.hpp"

CRONZ_BEGIN_MAIN_NAMESPACE
    /**
     * @ingroup compression
     * @brief An enumeration that represents the compression operation modes.
     * @enum CompressionMode
     */
    enum class CompressionMode : char {
        /**
         * @brief Invalid mode.
         */
        None = '\0',

        /**
         * @brief Compress data.
         */
        Compress = 'c',

        /**
         * @brief Decompress data.
         */
        Decompress = 'd'
    };

CRONZ_END_MAIN_NAMESPACE

#endif // CRONZ_COMPRESSION_MODE_HPP
