/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_AUTHORITY_HOST_HPP
#define CRONZ_URI_AUTHORITY_HOST_HPP 1

#include "cronz/uri/types.hpp"

#include "cronz/ip/address/v4.hpp"
#include "cronz/ip/address/v6.hpp"

#include <functional>

CRONZ_BEGIN_URI_NAMESPACE
    class Host final {
        // Internal constants.
        inline static constexpr char None = '\0';
        inline static constexpr char IPv4 = '4';
        inline static constexpr char IPv6 = '6';
        inline static constexpr char Name = 'r';
        inline static constexpr char DNSD = 'd';

        // Properties.
        union {
            IPv6Address _ipv6;
            IPv4Address _ipv4{};
        } _ip{};

        std::string _value{};

        std::vector<std::size_t> _indices{};

        char _type = None;

        CRONZ_NODISCARD_L1 bool _generateIndices() noexcept;

    public:
        /**
         * @name Static type definitions.
         */
        /** @{ */
        /**
         * @brief Iteration callback function.
         * @param[in] part Part of the host. This can be a subdomain, IP address part, etc.
         * @typedef std::function<void(std::string_view)> IterationCallbackFunction
         */
        typedef std::function<void(std::string_view part)> IterationCallbackFunction;

        /** @} */

        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Host() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the host as an IPv4 address.
         * @return IPv4 address.
         * @remark If the host is not an IPv4 address, an empty address will be returned.
         */
        CRONZ_NODISCARD_L1 IPv4Address ipv4() const noexcept;

        /**
         * @brief Returns the host as an IPv6 address.
         * @return IPv6 address.
         * @remark If the host is not an IPv6 address, an empty address will be returned.
         */
        CRONZ_NODISCARD_L1 IPv6Address ipv6() const noexcept;

        /**
         * @brief Returns the host as a string.
         * @return Host as a string.
         */
        CRONZ_NODISCARD_L1 std::string_view value() const noexcept;

        /**
         * @brief Tells whether the host is an IPv4 address.
         * @return `true` if the host is an IPv4 address.
         * @return `false` if the host is not an IPv4 address.
         */
        CRONZ_NODISCARD_L1 bool isIPv4() const noexcept;

        /**
         * @brief Tells whether the host is an IPv6 address.
         * @return `true` if the host is an IPv6 address.
         * @return `false` if the host is not an IPv6 address.
         */
        CRONZ_NODISCARD_L1 bool isIPv6() const noexcept;

        /**
         * @brief Tells whether the host is a registered name.
         * @return `true` if the host is a registered name.
         * @return `false` if the host is not a registered name.
         * @remark Normally, DNS domain names are considered as registered names. However, this function does not
         * consider DNS domain names as registered names. Use `isDNSDomain()` function to check whether the host is a
         * DNS domain.
         */
        CRONZ_NODISCARD_L1 bool isRegisteredName() const noexcept;

        /**
         * @brief Tells whether the host is a DNS domain.
         * @return `true` if the host is a DNS domain.
         * @return `false` if the host is not a DNS domain.
         */
        CRONZ_NODISCARD_L1 bool isDNSDomain() const noexcept;

        /**
         * @brief Returns the length of the host.
         * @return Length of the host.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells the number of parts in the hostname.
         * @return Number of parts in the hostname.
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /**
         * @brief Tells whether the host is empty.
         * @return `true` if the host is empty.
         * @return `false` if the host is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the host.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Assignment.
         */
        /** @{ */
        /**
         * @brief Assigns an IPv4 address to the host.
         * @param address IPv4 address.
         * @return `true` if the address is assigned successfully.
         * @return `false` if the address is not assigned successfully.
         */
        CRONZ_NODISCARD_L2 bool assign(const IPv4Address &address) noexcept;

        /**
         * @brief Assigns an IPv6 address to the host.
         * @param address IPv6 address.
         * @return `true` if the address is assigned successfully.
         * @return `false` if the address is not assigned successfully.
         */
        CRONZ_NODISCARD_L2 bool assign(const IPv6Address &address) noexcept;

        /**
         * @brief Assigns a string to the host.
         * @param address String.
         * @return `true` if the address is assigned successfully.
         * @return `false` if the address is not assigned successfully.
         * @remark This function will try to parse the address as an IPv4 address, IPv6 address, or a registered name.
         */
        CRONZ_NODISCARD_L2 bool assign(std::string_view address) noexcept;

        /** @} */

        /**
         * @name Stringification.
         */
        /** @{ */
        /**
         * @brief Returns the host as a string.
         * @return Host as a string.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Returns the host as a string.
         * @param[out] str Output string.
         * @return `true` if the host is stringified successfully.
         * @return `false` if the host is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Returns the host as a string.
         * @param[inout] str Output string.
         * @param[inout] offset Offset.
         * @return `true` if the host is stringified successfully.
         * @return `false` if the host is not stringified successfully.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Iterates over the parts of the host.
         * @param[in] callback Callback function.
         * @remark The callback function will be called for each part of the host.
         */
        void forEach(const IterationCallbackFunction &callback) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Conversion operator to `bool`.
         * @return `true` if the host is not empty.
         * @return `false` if the host is empty.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~Host() noexcept = default;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/authority/impl/host.ipp"

#endif // CRONZ_URI_AUTHORITY_HOST_HPP
