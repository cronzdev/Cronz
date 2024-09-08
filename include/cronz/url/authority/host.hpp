/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_AUTHORITY_HOST_HPP
#define CRONZ_URL_AUTHORITY_HOST_HPP 1

#include "cronz/url/types.hpp"
#include "cronz/ip/address/v4.hpp"
#include "cronz/ip/address/v6.hpp"

#include <vector>

CRONZ_BEGIN_MODULE_NAMESPACE(URL)
    /**
     * @ingroup cronz_url_authority
     * @brief Host.
     * @class Host
     * @warning Currently, non-ASCII registered names are not supported. The instructions stated by
     * [RFC1035](https://datatracker.ietf.org/doc/html/rfc1035) and
     * [RFC819](https://datatracker.ietf.org/doc/html/rfc819) are applied. However, IPv4 and IPv6 addresses are
     * supported.
     */
    class Host {
        // Types.
        inline static constexpr char None = '\0';
        inline static constexpr char IPv4 = '4';
        inline static constexpr char IPv6 = '6';
        inline static constexpr char Name = 'n';

        // Properties.
        std::string value_;

        std::vector<std::size_t> indices_;

        char type_ = None;

        // Assignment & Parsing.
        [[nodiscard]] static bool validateLabel_(const char *label, const std::size_t &length) noexcept;

    public:
        /**
         * @brief Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor. Does nothing.
         */
        Host() noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] address IPv4 address.
         * @remark This function internally calls `assign`. Thus, the assignment of `address` might fail.
         */
        Host(const IP::IPv4Address &address) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] address IPv6 address.
         * @remark This function internally calls `assign`. Thus, the assignment of `address` might fail.
         */
        Host(const IP::IPv6Address &address) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str Address.
         * @remark This function internally calls `assign`. Thus, the assignment of `str` might fail.
         */
        Host(const char *str) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str Address.
         * @param[in] length Length of `str`.
         * @remark This function internally calls `assign`. Thus, the assignment of `str` might fail.
         */
        Host(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Constructor with initializer.
         * @param[in] str Address.
         * @remark This function internally calls `assign`. Thus, the assignment of `str` might fail.
         */
        Host(const std::string &str) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Tells if the host is actually an IPv4 address.
         * @return `true` if the host is actually an IPv4 address, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool isIPv4() const noexcept;

        /**
         * @brief Tells if the host is actually an IPv6 address.
         * @return `true` if the host is actually an IPv6 address, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool isIPv6() const noexcept;

        /**
         * @brief Tells if the host is actually a registered name.
         * @return `true` if the host is actually a registered name, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool isRegisteredName() const noexcept;

        /** @} */

        /**
         * @name Assignment & Parsing.
         */
        /** @{ */
        /**
         * @brief Assigns an IPv4 address as the host.
         * @param[in] address IPv4 address.
         * @return `true` if assignment is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool assign(const IP::IPv4Address &address) noexcept;

        /**
         * @brief Assigns an IPv6 address as the host.
         * @param[in] address IPv6 address.
         * @return `true` if assignment is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool assign(const IP::IPv6Address &address) noexcept;

        /**
         * @brief Assigns a string as the host.
         * @param[in] str Address.
         * @return `true` if assignment is successful, otherwise, `false`.
         * @remark This function internally calls `parse`.
         */
        CRONZ_NODISCARD_L2 bool assign(const char *str) noexcept;

        /**
         * @brief Assigns a string as the host.
         * @param[in] str Address.
         * @param[in] length Length of `str`.
         * @return `true` if assignment is successful, otherwise, `false`.
         * @remark This function internally calls `parse`.
         */
        CRONZ_NODISCARD_L2 bool assign(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Assigns a string as the host.
         * @param[in] str Address.
         * @return `true` if assignment is successful, otherwise, `false`.
         * @remark This function internally calls `parse`.
         */
        CRONZ_NODISCARD_L2 bool assign(const std::string &str) noexcept;

        /**
         * @brief Parses an address string.
         * @param[in] str Address.
         * @return `true` if a valid format is found and successfully parsed, otherwise, `false`.
         * @remark `str` can be an IPv4 address, an  IPv6 address, or a registered name.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str) noexcept;

        /**
         * @brief Parses an address string.
         * @param[in] str Address.
         * @param[in] length Length of `str`.
         * @return `true` if a valid format is found and successfully parsed, otherwise, `false`.
         * @remark `str` can be an IPv4 address, an  IPv6 address, or a registered name.
         */
        CRONZ_NODISCARD_L2 bool parse(const char *str, const std::size_t &length) noexcept;

        /**
         * @brief Parses an address string.
         * @param[in] str Address.
         * @return `true` if a valid format is found and successfully parsed, otherwise, `false`.
         * @remark `str` can be an IPv4 address, an  IPv6 address, or a registered name.
         */
        CRONZ_NODISCARD_L2 bool parse(const std::string &str) noexcept;

        /** @} */

        /**
         * @name Stringification.
         */
        /** @{ */
        /**
         * @brief Returns the length of the stored host.
         * @return Length of the stored host.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Returns the stored host.
         * @return Stored host.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Overwrites the host value to the passed string container.
         * @param[out] str Output.
         * @return `true` if operation is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Writes the host value starting at the given position.
         * @param[out] str Output.
         * @param[in] offset Position to start writing.
         * @return `true` if operation is successful, otherwise, `false`.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, const std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Tells if the contained value is empty.
         * @return `true` if the contained value is empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the contained value.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Tells if the contained value is empty.
         * @return `true` if the contained value is empty, otherwise, `false`.
         */
        CRONZ_NODISCARD_L1 operator bool() const noexcept;

        /**
         * @brief Assigns an IPv4 address as the host.
         * @param[in] address IPv4 address.
         * @return Reference to the current container.
         * @remark This function internally calls `assign`. Thus, the assignment of `address` might fail.
         */
        CRONZ_NODISCARD_L2 Host& operator=(const IP::IPv4Address &address) noexcept;

        /**
         * @brief Assigns an IPv6 address as the host.
         * @param[in] address IPv6 address.
         * @return Reference to the current container.
         * @remark This function internally calls `assign`. Thus, the assignment of `address` might fail.
         */
        CRONZ_NODISCARD_L2 Host& operator=(const IP::IPv6Address &address) noexcept;

        /**
         * @brief Assigns a string as the host.
         * @param[in] str Address.
         * @return Reference to the current container.
         * @remark This function internally calls `assign`. Thus, the assignment of `str` might fail.
         */
        CRONZ_NODISCARD_L2 Host& operator=(const char *str) noexcept;

        /**
         * @brief Assigns a string as the host.
         * @param[in] str Address.
         * @return Reference to the current container.
         * @remark This function internally calls `assign`. Thus, the assignment of `str` might fail.
         */
        CRONZ_NODISCARD_L2 Host& operator=(const std::string &str) noexcept;

        /** @} */

        /**
         * @brief Destructors.
         */
        /** @{ */
        /**
         * @brief Default destructor. Does nothing.
         */
        ~Host() noexcept;

        /** @} */
    };

CRONZ_END_MODULE_NAMESPACE

#include "cronz/url/authority/impl/host.ipp"

#endif // CRONZ_URL_AUTHORITY_HOST_HPP
