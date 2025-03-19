/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_COMPRESSION_TYPES_HPP
#define CRONZ_COMPRESSION_TYPES_HPP 1

#include "cronz/internal/namespace.hpp"

#include <concepts>
#include <cstdint>
#include <type_traits>

CRONZ_BEGIN_MAIN_NAMESPACE
    /**
     * @brief A concept that checks whether the given type is a valid compression algorithm.
     * @tparam DataType The type to check.
     * @details The DataType must be one of the following types: char, unsigned char, std::int8_t, std::uint8_t.
     */
    template<typename DataType>
    concept CompressionAlgorithmDataType = requires
    {
        std::is_same_v<DataType, char> || std::is_same_v<DataType, unsigned char> ||
        std::is_same_v<DataType, std::int8_t> || std::is_same_v<DataType, std::uint8_t>;
    };

CRONZ_END_MAIN_NAMESPACE

#endif // CRONZ_COMPRESSION_TYPES_HPP
