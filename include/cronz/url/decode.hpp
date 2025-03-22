/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_DECODE_HPP
#define CRONZ_URL_DECODE_HPP 1

#include "cronz/url/types.hpp"

CRONZ_BEGIN_URL_NAMESPACE
    /**
     * @ingroup cronz_url
     * @brief Calculate the size of the decoded string.
     * @param[in] component The component to calculate the size.
     * @return The size of the decoded string.
     * @return `std::numeric_limits<std::size_t>::max()` if the component is not a valid URL component.
     */
    CRONZ_NODISCARD_L1 std::size_t URLCalculateDecodedComponentLength(std::string_view component) noexcept;

    /**
     * @ingroup cronz_url
     * @brief Decode the given component.
     * @param[in] component The component to decode.
     * @param[out] decoded The decoded component.
     * @return `true` if the decoding is successful.
     * @return `false` if the decoding is not successful.
     * @remark Upon failure, the content of the decoded is undefined.
     */
    CRONZ_NODISCARD_L2 bool URLDecodeComponent(std::string_view component, std::string &decoded) noexcept;

    /**
     * @ingroup cronz_url
     * @brief Decode the given component.
     * @param[in] component The component to decode.
     * @param[out] decoded The decoded component.
     * @param[inout] offset The offset to overwrite the decoded component.
     * @return `true` if the decoding is successful.
     * @return `false` if the decoding is not successful.
     * @remark Upon failure, the content of the decoded is undefined.
     */
    CRONZ_NODISCARD_L2 bool URLDecodeComponent(std::string_view component, std::string &decoded,
                                               std::size_t &offset) noexcept;

    /**
     * @ingroup cronz_url
     * @brief Decode the given component in place.
     * @param[inout] component The component to decode.
     * @return `true` if the decoding is successful.
     * @return `false` if the decoding is not successful.
     * @remark Upon failure, the content of the component is undefined.
     */
    CRONZ_NODISCARD_L2 bool URLDecodeComponentInPlace(std::string &component) noexcept;

CRONZ_END_URL_NAMESPACE

#include "cronz/url/impl/decode.ipp"

#endif // CRONZ_URL_DECODE_HPP
