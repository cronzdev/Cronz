/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_ENCODE_HPP
#define CRONZ_URL_ENCODE_HPP 1

/**
 * @defgroup cronz_url_encode Encoding
 * @ingroup cronz_url
 */

#include "cronz/url/types.hpp"

#include <string>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_encode
     * @brief Tells whether a character should be encoded or not.
     * @param[in] character Character to be tested.
     * @return `true` if the character should be encoded, otherwise, `false`.
     * @sa The characters flagged as safe are `A–Z a–z 0–9 - _ . ! ~ * ' ( )`. For more information, see
     * [encodeURIComponent at mozilla.org](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent#description).
     */
    CRONZ_NODISCARD_L1 bool ShouldEncodeCharacter(const char &character) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Calculates the number of characters in the encoded version of the string.
     * @param[in] decoded Decoded string.
     * @return The number of characters in the encoded version of the string.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculateEncodedLength(const std::string &decoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Calculates the number of characters in the encoded version of the string.
     * @param[in] decoded Decoded string.
     * @param[in] length Length of the decoded string.
     * @return The number of characters in the encoded version of the string.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculateEncodedLength(const char *decoded, const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @return The encoded string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L1 std::string Encode(const std::string &decoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @param[in] length Length of the decoded string.
     * @return The encoded string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L1 std::string Encode(const char *decoded, const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @param[out] encoded Encoded string.
     * @return `true` if encoding was successfully completed, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Encode(const std::string &decoded, std::string &encoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @param[out] encoded Encoded string.
     * @return Number of characters written to `encoded`.
     * @remark The capacity of `encoded` is not tested by this function. That `encoded` has enough capacity must be
     * confirmed before this function is called.
     */
    CRONZ_NODISCARD_L2 std::size_t Encode(const std::string &decoded, char *encoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @param[in] length Length of the decoded string.
     * @param[out] encoded Encoded string.
     * @return `true` if encoding was successfully completed, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Encode(const char *decoded, const std::size_t &length, std::string &encoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string.
     * @param[in] decoded Decoded string.
     * @param[in] length Length of the decoded string.
     * @param[out] encoded Encoded string.
     * @return Number of characters written to `encoded`.
     * @remark The capacity of `encoded` is not tested by this function. That `encoded` has enough capacity must be
     * confirmed before this function is called.
     */
    CRONZ_NODISCARD_L2 std::size_t Encode(const char *decoded, const std::size_t &length, char *encoded) noexcept;

    /**
     * @ingroup cronz_url_encode
     * @brief Encodes a string in-place.
     * @param[inout] str Decoded string as input, encoded string as output.
     * @return `true` if encoding was successfully completed, otherwise, `false`.
     * @remark Upon failure, contents of `str` will be preserved.
     */
    CRONZ_NODISCARD_L2 bool EncodeInPlace(std::string &str) noexcept;

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/impl/encode.ipp"

#endif // CRONZ_URL_ENCODE_HPP
