/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_DECODE_HPP
#define CRONZ_URL_DECODE_HPP 1

/**
 * @defgroup cronz_url_decode Decoding
 * @ingroup cronz_url
 */

#include "cronz/url/types.hpp"

#include <string>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_decode
     * @brief Calculates the number of characters in the decoded version of the string.
     * @param[in] encoded Encoded string.
     * @return The number of characters in the encoded version of the string. Upon failure, this function returns
     * `std::numeric_limits<std::size_t>::max()`.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculateDecodedLength(const std::string &encoded) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Calculates the number of characters in the decoded version of the string.
     * @param[in] encoded Encoded string.
     * @param[in] length Length of the encoded string.
     * @return The number of characters in the encoded version of the string. Upon failure, this function returns
     * `std::numeric_limits<std::size_t>::max()`.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculateDecodedLength(const char *encoded, const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Decodes an encoded string.
     * @param[in] encoded Encoded string.
     * @return Decoded string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L1 std::string Decode(const std::string &encoded) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Decodes an encoded string.
     * @param[in] encoded Encoded string.
     * @param[in] length Length of the encoded string.
     * @return Decoded string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L1 std::string Decode(const char *encoded, const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Decodes an encoded string.
     * @param[in] encoded Encoded string.
     * @param decoded Decoded string.
     * @return `true` if `encoded` was successfully decoded, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Decode(const std::string &encoded, std::string &decoded) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Decodes an encoded string.
     * @param[in] encoded Encoded string.
     * @param[in] length Length of the encoded string.
     * @param[out] decoded Decoded string.
     * @return `true` if `encoded` was successfully decoded, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Decode(const char *encoded, const std::size_t &length, std::string &decoded) noexcept;

    /**
     * @ingroup cronz_url_decode
     * @brief Decodes an encoded string in-place.
     * @param[inout] str Encoded string as input, decoded string as output.
     * @return `true` if decoding was successfully completed, otherwise, `false`.
     * @remark Upon failure, `str` will be corrupt.
     */
    CRONZ_NODISCARD_L2 bool DecodeInPlace(std::string &str) noexcept;

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/impl/decode.ipp"

#endif // CRONZ_URL_DECODE_HPP
