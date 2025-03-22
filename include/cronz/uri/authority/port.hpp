/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_AUTHORITY_PORT_HPP
#define CRONZ_URI_AUTHORITY_PORT_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief Port number type.
     * @typedef std::uint16_t Port
     */
    typedef std::uint16_t Port;

    /**
     * @ingroup cronz_uri
     * @brief Invalid port number.
     * @details This is the default value of a port number.
     */
    inline constexpr Port InvalidPort = static_cast<Port>(0);

    /**
     * @ingroup cronz_uri
     * @brief Parses a port number from a string.
     * @param[in] str String to parse.
     * @return Parsed port number.
     */
    CRONZ_NODISCARD_L1 Port ParsePort(std::string_view str) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Parses a port number from a string.
     * @param[in] str String to parse.
     * @param[out] port Parsed port number.
     * @return `true` if the port number is successfully parsed.
     * @return `false` if the port number is not successfully parsed.
     */
    CRONZ_NODISCARD_L2 bool ParsePort(std::string_view str, Port &port) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Converts a port number to a string.
     * @param[in] port Port number.
     * @return Stringified port number. Upon failure, an empty string is returned.
     */
    CRONZ_NODISCARD_L1 std::string StringifyPort(Port port) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Converts a port number to a string.
     * @param[in] port Port number.
     * @param[out] str Stringified port number.
     * @return `true` if the port number is successfully stringified.
     * @return `false` if the port number is not successfully stringified.
     */
    CRONZ_NODISCARD_L2 bool StringifyPort(Port port, std::string &str) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Converts a port number to a string.
     * @param[in] port Port number.
     * @param[out] str Stringified port number.
     * @param[inout] offset Offset of the string.
     * @return `true` if the port number is successfully stringified.
     * @return `false` if the port number is not successfully stringified.
     */
    CRONZ_NODISCARD_L2 bool StringifyPort(Port port, std::string &str, std::size_t &offset) noexcept;

    /**
     * @ingroup cronz_uri
     * @brief Calculates the length of a port number.
     * @param[in] port Port number.
     * @return Length of the port number.
     * @remark If the port number equals to `InvalidPort`, the return value will be `0`.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculatePortLength(Port port) noexcept;

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/authority/impl/port.ipp"

#endif // CRONZ_URI_AUTHORITY_PORT_HPP
