/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_ENCODE_HPP
#define CRONZ_URI_ENCODE_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief Check if the character should be encoded.
     * @param[in] character The character to check.
     * @return `true` if the character should be encoded.
     * @return `false` if the character should not be encoded.
     */
    CRONZ_NODISCARD_L1 bool URIShouldEncode(char character) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Check if the component should be encoded.
     * @param[in] component The component to check.
     * @return `true` if the component should be encoded.
     * @return `false` if the component should not be encoded.
     * @remark This function checks if any character in the given string should be encoded. Thus, rather than checking
     * the whole URI, it is more accurate to check a part of the URI. This function is not smart enough to detect the
     * separators, etc. in the URI.
     */
    CRONZ_NODISCARD_L1 bool URIShouldEncodeComponent(std::string_view component) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Calculate the size of the encoded string.
     * @param[in] component The component to calculate the size.
     * @return The size of the encoded string.
     */
    CRONZ_NODISCARD_L1 std::size_t URICalculateEncodedComponentLength(std::string_view component) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Encode the given component.
     * @param[in] component The component to encode.
     * @param[out] encoded The encoded component.
     * @return `true` if the encoding is successful.
     * @return `false` if the encoding is not successful.
     * @remark Upon failure, the content of the component is undefined.
     */
    CRONZ_NODISCARD_L2 bool URIEncodeComponent(std::string_view component, std::string &encoded) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Encode the given component.
     * @param[in] component The component to encode.
     * @param[out] encoded The encoded component.
     * @param[inout] offset The offset to overwrite the encoded component.
     * @return `true` if the encoding is successful.
     * @return `false` if the encoding is not successful.
     * @remark Upon failure, the content of the encoded is undefined.
     */
    CRONZ_NODISCARD_L2 bool URIEncodeComponent(std::string_view component, std::string &encoded,
                                               std::size_t &offset) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Encode the given component in place.
     * @param[inout] component The component to encode.
     * @return `true` if the encoding is successful.
     * @return `false` if the encoding is not successful.
     * @remark Upon failure, the content of the component is undefined.
     */
    CRONZ_NODISCARD_L1 bool URIEncodeComponentInPlace(std::string &component) noexcept;

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/impl/encode.ipp"

#endif // CRONZ_URI_ENCODE_HPP
