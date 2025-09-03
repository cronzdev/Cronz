/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_COOKIE_COOKIE_HPP
#define CRONZ_HTTP_COOKIE_COOKIE_HPP 1

#include "cronz/http/cookie/date.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Cookie class.
     * @class Cookie
     * @tparam Renamable Whether the container is renamable.
     * @remark All the fields/attributes are monitored and verified by this class.
     * @remark The `Expires` attribute has a higher priority than the `MaxAge` attribute. Thus, if both are assigned,
     * only `Expires` will be stringified.
     * @remark If the timestamp of `Expires` is `0`, it is interpreted as invalid/empty.
     * @remark If the `MaxAge` has a value of `0`, it is interpreted as invalid/empty.
     */
    template <bool Renamable = true>
    class Cookie final {
    public:
        /**
         * @name Static constants.
         */
        /** @{ */
        /**
         * @brief Domain.
         */
        inline static constexpr auto Domain = "Domain";

        /**
         * @brief Expires.
         */
        inline static constexpr auto Expires = "Expires";

        /**
         * @brief Max Age.
         */
        inline static constexpr auto MaxAge = "MaxAge";

        /**
         * @brief Path.
         */
        inline static constexpr auto Path = "Path";

        /**
         * @brief Secure.
         */
        inline static constexpr auto Secure = "Secure";

        /**
         * @brief Http Only.
         */
        inline static constexpr auto HttpOnly = "HttpOnly";

        /** @} */
    private:
        // Attributes.
        std::string _name{};
        std::string _value{};
        CookieDate _expires{};
        std::uint64_t _maxAge = std::numeric_limits<std::uint64_t>::max();
        std::string _domain{};
        std::string _path{};
        bool _secure = false;
        bool _httpOnly = false;
        bool _sameSite = false;

        // Friends.
        friend class CookieManager;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Cookie() noexcept = default;

        /** @} */

        /**
         * @name Attributes.
         */
        /** @{ */
        /**
         * @brief Returns the name of the cookie.
         * @return The name of the cookie.
         */
        CRONZ_NODISCARD_L1 const std::string& name() const noexcept;

        /**
         * @brief Returns the name of the cookie.
         * @return The name of the cookie.
         */
        CRONZ_NODISCARD_L1 const std::string& getName() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~Cookie() noexcept = default;

        /** @} */
    };

    using ImmutableCookie = Cookie<false>;
    using MutableCookie = Cookie<true>;
CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/cookie/impl/cookie.ipp"

#endif // CRONZ_HTTP_COOKIE_COOKIE_HPP
