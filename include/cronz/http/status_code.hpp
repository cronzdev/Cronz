/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_STATUS_CODE_HPP
#define CRONZ_HTTP_STATUS_CODE_HPP 1

#include "cronz/http/types.hpp"

#include <string>
#include <string_view>

CRONZ_BEGIN_HTTP_NAMESPACE
    // [RFC9110 - Section 15](https://datatracker.ietf.org/doc/html/rfc9110#section-15)
    //    * @remark The list is generated based on the following documents:
    //   *  - [RFC9110 - 16.2.1 Status Code Registry](https://datatracker.ietf.org/doc/html/rfc9110#name-status-code-registry)
    //   *  - [Hypertext Transfer Protocol (HTTP) Status Code Registry](https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml)
// https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.2
    class StatusCode {
    public:
        /**
         * @name Static type definitions.
         */
        /** @{ */
        typedef std::uint_fast32_t StatusCodeValueType;

        /**
         * @brief Status code categories.
         * @enum Category
         */
        enum class Category : StatusCodeValueType {
            /**
             * @brief Informational (1xx).
             */
            Informational = static_cast<StatusCodeValueType>(100),

            /**
             * @brief Success (2xx).
             */
            Success = static_cast<StatusCodeValueType>(200),

            /**
             * @brief Redirection (3xx).
             */
            Redirection = static_cast<StatusCodeValueType>(300),

            /**
             * @brief Client error (4xx).
             */
            ClientError = static_cast<StatusCodeValueType>(400),

            /**
             * @brief Server error (5xx).
             */
            ServerError = static_cast<StatusCodeValueType>(500),

            /**
             * @brief Unknown or invalid category.
             */
            Invalid = std::numeric_limits<StatusCodeValueType>::max()
        };

        /**
         * @brief Status code enumeration.
         * @enum StatusCodeEnum
         */
        enum StatusCodeEnum : StatusCodeValueType {
            /**
             * @brief Continue.
             */
            Continue = static_cast<StatusCodeValueType>(100),

            /**
             * @brief Switching Protocols.
             */
            SwitchingProtocols = static_cast<StatusCodeValueType>(101),

            /**
             * @brief Processing.
             */
            Processing = static_cast<StatusCodeValueType>(102),

            /**
             * @brief Early Hints.
             */
            EarlyHints = static_cast<StatusCodeValueType>(103),

            /**
             * @brief OK.
             */
            OK = static_cast<StatusCodeValueType>(200),

            /**
             * @brief Created.
             */
            Created = static_cast<StatusCodeValueType>(201),

            /**
             * @brief Accepted.
             */
            Accepted = static_cast<StatusCodeValueType>(202),

            /**
             * @brief Non-Authoritative Information.
             */
            NonAuthoritativeInformation = static_cast<StatusCodeValueType>(203),

            /**
             * @brief No Content.
             */
            NoContent = static_cast<StatusCodeValueType>(204),

            /**
             * @brief Reset Content.
             */
            ResetContent = static_cast<StatusCodeValueType>(205),

            /**
             * @brief Partial Content.
             */
            PartialContent = static_cast<StatusCodeValueType>(206),

            /**
             * @brief Multi-Status.
             */
            MultiStatus = static_cast<StatusCodeValueType>(207),

            /**
             * @brief Already Reported.
             */
            AlreadyReported = static_cast<StatusCodeValueType>(208),

            /**
             * @brief IM Used.
             */
            IMUsed = static_cast<StatusCodeValueType>(226),

            /**
             * @brief Multiple Choices.
             */
            MultipleChoices = static_cast<StatusCodeValueType>(300),

            /**
             * @brief Moved Permanently.
             */
            MovedPermanently = static_cast<StatusCodeValueType>(301),

            /**
             * @brief Found.
             */
            Found = static_cast<StatusCodeValueType>(302),

            /**
             * @brief See Other.
             */
            SeeOther = static_cast<StatusCodeValueType>(303),

            /**
             * @brief Not Modified.
             */
            NotModified = static_cast<StatusCodeValueType>(304),

            /**
             * @brief Use Proxy.
             */
            UseProxy = static_cast<StatusCodeValueType>(305),

            /**
             * @brief Temporary Redirect.
             */
            TemporaryRedirect = static_cast<StatusCodeValueType>(307),

            /**
             * @brief Permanent Redirect.
             */
            PermanentRedirect = static_cast<StatusCodeValueType>(308),

            /**
             * @brief Bad Request.
             */
            BadRequest = static_cast<StatusCodeValueType>(400),

            /**
             * @brief Unauthorized.
             */
            Unauthorized = static_cast<StatusCodeValueType>(401),

            /**
             * @brief Payment Required.
             */
            PaymentRequired = static_cast<StatusCodeValueType>(402),

            /**
             * @brief Forbidden.
             */
            Forbidden = static_cast<StatusCodeValueType>(403),

            /**
             * @brief Not Found.
             */
            NotFound = static_cast<StatusCodeValueType>(404),

            /**
             * @brief Method Not Allowed.
             */
            MethodNotAllowed = static_cast<StatusCodeValueType>(405),

            /**
             * @brief Not Acceptable.
             */
            NotAcceptable = static_cast<StatusCodeValueType>(406),

            /**
             * @brief Proxy Authentication Required.
             */
            ProxyAuthenticationRequired = static_cast<StatusCodeValueType>(407),

            /**
             * @brief Request Timeout.
             */
            RequestTimeout = static_cast<StatusCodeValueType>(408),

            /**
             * @brief Conflict.
             */
            Conflict = static_cast<StatusCodeValueType>(409),

            /**
             * @brief Gone.
             */
            Gone = static_cast<StatusCodeValueType>(410),

            /**
             * @brief Length Required.
             */
            LengthRequired = static_cast<StatusCodeValueType>(411),

            /**
             * @brief Precondition Failed.
             */
            PreconditionFailed = static_cast<StatusCodeValueType>(412),

            /**
             * @brief Content Too Large.
             */
            ContentTooLarge = static_cast<StatusCodeValueType>(413),

            /**
             * @brief URI Too Long.
             */
            URITooLong = static_cast<StatusCodeValueType>(414),

            /**
             * @brief Unsupported Media Type.
             */
            UnsupportedMediaType = static_cast<StatusCodeValueType>(415),

            /**
             * @brief Range Not Satisfiable.
             */
            RangeNotSatisfiable = static_cast<StatusCodeValueType>(416),

            /**
             * @brief Expectation Failed.
             */
            ExpectationFailed = static_cast<StatusCodeValueType>(417),

            /**
             * @brief Misdirected Request.
             */
            MisdirectedRequest = static_cast<StatusCodeValueType>(421),

            /**
             * @brief Unprocessable Content.
             */
            UnprocessableContent = static_cast<StatusCodeValueType>(422),

            /**
             * @brief Locked.
             */
            Locked = static_cast<StatusCodeValueType>(423),

            /**
             * @brief Failed Dependency.
             */
            FailedDependency = static_cast<StatusCodeValueType>(424),

            /**
             * @brief Too Early.
             */
            TooEarly = static_cast<StatusCodeValueType>(425),

            /**
             * @brief Upgrade Required.
             */
            UpgradeRequired = static_cast<StatusCodeValueType>(426),

            /**
             * @brief Precondition Required.
             */
            PreconditionRequired = static_cast<StatusCodeValueType>(428),

            /**
             * @brief Too Many Requests.
             */
            TooManyRequests = static_cast<StatusCodeValueType>(429),

            /**
             * @brief Request Header Fields Too Large.
             */
            RequestHeaderFieldsTooLarge = static_cast<StatusCodeValueType>(431),

            /**
             * @brief Unavailable For Legal Reasons.
             */
            UnavailableForLegalReasons = static_cast<StatusCodeValueType>(451),

            /**
             * @brief Internal Server Error.
             */
            InternalServerError = static_cast<StatusCodeValueType>(500),

            /**
             * @brief Not Implemented.
             */
            NotImplemented = static_cast<StatusCodeValueType>(501),

            /**
             * @brief Bad Gateway.
             */
            BadGateway = static_cast<StatusCodeValueType>(502),

            /**
             * @brief Service Unavailable.
             */
            ServiceUnavailable = static_cast<StatusCodeValueType>(503),

            /**
             * @brief Gateway Timeout.
             */
            GatewayTimeout = static_cast<StatusCodeValueType>(504),

            /**
             * @brief HTTP Version Not Supported.
             */
            HTTPVersionNotSupported = static_cast<StatusCodeValueType>(505),

            /**
             * @brief Variant Also Negotiates.
             */
            VariantAlsoNegotiates = static_cast<StatusCodeValueType>(506),

            /**
             * @brief Insufficient Storage.
             */
            InsufficientStorage = static_cast<StatusCodeValueType>(507),

            /**
             * @brief Loop Detected.
             */
            LoopDetected = static_cast<StatusCodeValueType>(508),

            /**
             * @brief Network Authentication Required.
             */
            NetworkAuthenticationRequired = static_cast<StatusCodeValueType>(511),

            /**
             * @brief Invalid or unknown status code.
             */
            Invalid = std::numeric_limits<StatusCodeValueType>::max()
        };

        /** @} */

        /**
         * @name Static properties.
         */
        /** @{ */
        /**
         * @brief Status code categories.
         */
        static const std::array<Category, static_cast<std::size_t>(5)> Categories;

        /**
         * @brief Status codes.
         */
        static const std::array<StatusCode, static_cast<std::size_t>(62)> StatusCodes;

        /**
         * @brief Status code reasons.
         */
        static const std::unordered_map<StatusCodeEnum, std::string_view> StatusCodeReasons;

        /** @} */

    private:
        // Properties.
        std::string _reason{};
        StatusCodeEnum _value = StatusCodeEnum::Invalid;

        // Instance-based utility functions.
        CRONZ_NODISCARD_L1 bool _cmp(const StatusCode &code) const noexcept;

        CRONZ_NODISCARD_L1 bool _cmp(StatusCodeEnum code) const noexcept;

        template<std::integral T>
        CRONZ_NODISCARD_L1 bool _cmp(T code) const noexcept;

        // Static utility functions.
        CRONZ_NODISCARD_L1 static StatusCodeEnum _v2e(StatusCodeValueType value) noexcept;

        CRONZ_NODISCARD_L1 static StatusCodeEnum _nr(StatusCodeValueType code) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        StatusCode() noexcept = default;

        /**
         * @brief Constructor with status code enumeration.
         * @param[in] code Status code enumeration.
         */
        explicit(false) StatusCode(StatusCodeEnum code) noexcept;

        /**
         * @brief Constructor with status code enumeration and reason.
         * @param[in] code Status code enumeration.
         * @param[in] reason Reason.
         */
        StatusCode(StatusCodeEnum code, std::string_view reason) noexcept;

        /**
         * @brief Constructor with status code value.
         * @param[in] code Status code value.
         */
        explicit(false) StatusCode(StatusCodeValueType code) noexcept;

        /**
         * @brief Constructor with status code enumeration and reason.
         * @param[in] code Status code enumeration.
         * @param[in] reason Reason.
         */
        StatusCode(StatusCodeValueType code, std::string_view reason) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Status code value.
         * @return Reference to the status code.
         */
        CRONZ_NODISCARD_L1 StatusCodeEnum &value() noexcept;

        /**
         * @brief Status code value.
         * @return Status code value.
         */
        CRONZ_NODISCARD_L1 StatusCodeEnum value() const noexcept;

        /**
         * @brief Status code value.
         * @return Reference to the status code.
         */
        CRONZ_NODISCARD_L1 StatusCodeEnum &code() noexcept;

        /**
         * @brief Status code value.
         * @return Status code value.
         */
        CRONZ_NODISCARD_L1 StatusCodeEnum code() const noexcept;

        /**
         * @brief Status code category.
         * @return Status code category.
         */
        CRONZ_NODISCARD_L1 Category category() const noexcept;

        /**
         * @brief Status code reason.
         * @return Reference to the status code reason.
         */
        CRONZ_NODISCARD_L1 std::string &reason() noexcept;

        /**
         * @brief Status code reason.
         * @return Status code reason.
         */
        CRONZ_NODISCARD_L1 std::string reason() const noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        /**
         * @brief Reset the status code.
         * @remark The status code is set to `StatusCodeEnum::Invalid` and the reason is cleared.
         */
        void reset() noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Boolean conversion operator.
         * @return `true` if the status code is valid.
         * @return `false` if the status code is invalid.
         * @remark The status code is invalid if it is equal to `StatusCodeEnum::Invalid`.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Status code enumeration conversion operator.
         * @return Status code enumeration.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator StatusCodeEnum() const noexcept;

        /**
         * @brief Status code value conversion operator.
         * @return Status code value.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator StatusCodeValueType() const noexcept;

        /**
         * @brief Status code category conversion operator.
         * @return Status code category.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator Category() const noexcept;

        /**
         * @brief String view conversion operator.
         * @return Status code reason.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::string_view() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] code Status code.
         * @return Reference to the status code.
         * @remark Reason is set based on the status code.
         */
        StatusCode &operator=(StatusCodeEnum code) noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] code Status code.
         * @return Reference to the status code.
         * @remark Reason is set based on the status code.
         */
        StatusCode &operator=(StatusCodeValueType code) noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] reason Reason.
         * @return Reference to the status code.
         * @remark The status code is not changed. Only the reason is updated.
         */
        StatusCode &operator=(std::string_view reason) noexcept;

        /**
         * @brief Equality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are equal.
         * @return `false` if the status codes are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(const StatusCode &code) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are equal.
         * @return `false` if the status codes are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(StatusCodeEnum code) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are equal.
         * @return `false` if the status codes are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(StatusCodeValueType code) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are not equal.
         * @return `false` if the status codes are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const StatusCode &code) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are not equal.
         * @return `false` if the status codes are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(StatusCodeEnum code) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] code Status code.
         * @return `true` if the status codes are not equal.
         * @return `false` if the status codes are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(StatusCodeValueType code) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        ~StatusCode() noexcept = default;

        /** @} */

        /**
         * @name Static utility functions.
         */
        /** @{ */

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/impl/status_code.ipp"

#endif // CRONZ_HTTP_STATUS_CODE_HPP
