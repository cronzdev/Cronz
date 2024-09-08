/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_PORT_HPP
#define CRONZ_URL_AUTHORITY_PORT_HPP 1

#include "cronz/url/scheme.hpp"

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_authority
     * @brief Port number type.
     * @typedef std::uint16_t Port
     */
    typedef std::uint16_t Port;

    /**
     * @ingroup cronz_url_authority
     * @brief Parses port number from string.
     * @param[in] str String to be parsed.
     * @return Port number.
     * @remark Upon failure, returns `0`.
     */
    CRONZ_NODISCARD_L1 Port ParsePort(const std::string &str) noexcept;

    /**
     * @ingroup cronz_url_authority
     * @brief Parses port number from string.
     * @param[in] str String to be parsed.
     * @param[in] length Length of the string to be parsed.
     * @return Port number.
     * @remark Upon failure, returns `0`.
     */
    CRONZ_NODISCARD_L1 Port ParsePort(const char *str, const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_url_authority
     * @brief Parses port number from string.
     * @param[in] str String to be parsed.
     * @param[out] port Port number.
     * @return `true` if parsing is successful, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool ParsePort(const std::string &str, Port &port) noexcept;

    /**
     * @ingroup cronz_url_authority
     * @brief Parses port number from string.
     * @param[in] str String to be parsed.
     * @param[in] length Length of the string to be parsed.
     * @param[out] port Port number.
     * @return `true` if parsing is successful, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool ParsePort(const char *str, const std::size_t &length, Port &port) noexcept;

    CRONZ_NODISCARD_L1 std::string StringifyPort(const Port &port) noexcept;

    CRONZ_NODISCARD_L2 bool StringifyPort(const Port &port, std::string &str) noexcept;

    CRONZ_NODISCARD_L2 bool StringifyPort(const Port &port, std::string &str, const std::size_t &offset) noexcept;

    /**
     * @ingroup cronz_url_authority
     * @brief Returns the default port for a scheme.
     * @param[in] scheme Scheme.
     * @return The default assigned port number for the given scheme. `0`, if the scheme is unknown or no assignment is
     * found.
     */
    CRONZ_NODISCARD_L1 Port GetSchemePort(const Scheme &scheme) noexcept;

    /**
     * @brief Tells the number of characters in the string representation of the port.
     * @param[in] port Port number.
     * @return Number of characters in the string representation of the port.
     */
    CRONZ_NODISCARD_L1 std::size_t CalculatePortLength(Port port) noexcept;

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/authority/impl/port.ipp"

#endif // CRONZ_URL_AUTHORITY_PORT_HPP
