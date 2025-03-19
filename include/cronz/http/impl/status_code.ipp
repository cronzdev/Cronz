/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_IMPL_STATUS_CODE_IPP
#define CRONZ_HTTP_IMPL_STATUS_CODE_IPP 1

#include "cronz/http/status_code.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Static properties.
    inline const std::unordered_map<StatusCode::StatusCodeEnum, std::string_view> StatusCode::StatusCodeReasons = {
        {StatusCode::StatusCodeEnum::Continue, "Continue"},
        {StatusCode::StatusCodeEnum::SwitchingProtocols, "Switching Protocols"},
        {StatusCode::StatusCodeEnum::Processing, "Processing"}, {StatusCode::StatusCodeEnum::EarlyHints, "Early Hints"},
        {StatusCode::StatusCodeEnum::OK, "OK"}, {StatusCode::StatusCodeEnum::Created, "Created"},
        {StatusCode::StatusCodeEnum::Accepted, "Accepted"},
        {StatusCode::StatusCodeEnum::NonAuthoritativeInformation, "Non-Authoritative Information"},
        {StatusCode::StatusCodeEnum::NoContent, "No Content"},
        {StatusCode::StatusCodeEnum::ResetContent, "Reset Content"},
        {StatusCode::StatusCodeEnum::PartialContent, "Partial Content"},
        {StatusCode::StatusCodeEnum::MultiStatus, "Multi-Status"},
        {StatusCode::StatusCodeEnum::AlreadyReported, "Already Reported"},
        {StatusCode::StatusCodeEnum::IMUsed, "IM Used"},
        {StatusCode::StatusCodeEnum::MultipleChoices, "Multiple Choices"},
        {StatusCode::StatusCodeEnum::MovedPermanently, "Moved Permanently"},
        {StatusCode::StatusCodeEnum::Found, "Found"}, {StatusCode::StatusCodeEnum::SeeOther, "See Other"},
        {StatusCode::StatusCodeEnum::NotModified, "Not Modified"}, {StatusCode::StatusCodeEnum::UseProxy, "Use Proxy"},
        {StatusCode::StatusCodeEnum::TemporaryRedirect, "Temporary Redirect"},
        {StatusCode::StatusCodeEnum::PermanentRedirect, "Permanent Redirect"},
        {StatusCode::StatusCodeEnum::BadRequest, "Bad Request"},
        {StatusCode::StatusCodeEnum::Unauthorized, "Unauthorized"},
        {StatusCode::StatusCodeEnum::PaymentRequired, "Payment Required"},
        {StatusCode::StatusCodeEnum::Forbidden, "Forbidden"}, {StatusCode::StatusCodeEnum::NotFound, "Not Found"},
        {StatusCode::StatusCodeEnum::MethodNotAllowed, "Method Not Allowed"},
        {StatusCode::StatusCodeEnum::NotAcceptable, "Not Acceptable"},
        {StatusCode::StatusCodeEnum::ProxyAuthenticationRequired, "Proxy Authentication Required"},
        {StatusCode::StatusCodeEnum::RequestTimeout, "Request Timeout"},
        {StatusCode::StatusCodeEnum::Conflict, "Conflict"}, {StatusCode::StatusCodeEnum::Gone, "Gone"},
        {StatusCode::StatusCodeEnum::LengthRequired, "Length Required"},
        {StatusCode::StatusCodeEnum::PreconditionFailed, "Precondition Failed"},
        {StatusCode::StatusCodeEnum::ContentTooLarge, "Content Too Large"},
        {StatusCode::StatusCodeEnum::URITooLong, "URI Too Long"},
        {StatusCode::StatusCodeEnum::UnsupportedMediaType, "Unsupported Media Type"},
        {StatusCode::StatusCodeEnum::RangeNotSatisfiable, "Range Not Satisfiable"},
        {StatusCode::StatusCodeEnum::ExpectationFailed, "Expectation Failed"},
        {StatusCode::StatusCodeEnum::MisdirectedRequest, "Misdirected Request"},
        {StatusCode::StatusCodeEnum::UnprocessableContent, "Unprocessable Content"},
        {StatusCode::StatusCodeEnum::Locked, "Locked"},
        {StatusCode::StatusCodeEnum::FailedDependency, "Failed Dependency"},
        {StatusCode::StatusCodeEnum::TooEarly, "Too Early"},
        {StatusCode::StatusCodeEnum::UpgradeRequired, "Upgrade Required"},
        {StatusCode::StatusCodeEnum::PreconditionRequired, "Precondition Required"},
        {StatusCode::StatusCodeEnum::TooManyRequests, "Too Many Requests"},
        {StatusCode::StatusCodeEnum::RequestHeaderFieldsTooLarge, "Request Header Fields Too Large"},
        {StatusCode::StatusCodeEnum::UnavailableForLegalReasons, "Unavailable For Legal Reasons"},
        {StatusCode::StatusCodeEnum::InternalServerError, "Internal Server Error"},
        {StatusCode::StatusCodeEnum::NotImplemented, "Not Implemented"},
        {StatusCode::StatusCodeEnum::BadGateway, "Bad Gateway"},
        {StatusCode::StatusCodeEnum::ServiceUnavailable, "Service Unavailable"},
        {StatusCode::StatusCodeEnum::GatewayTimeout, "Gateway Timeout"},
        {StatusCode::StatusCodeEnum::HTTPVersionNotSupported, "HTTP Version Not Supported"},
        {StatusCode::StatusCodeEnum::VariantAlsoNegotiates, "Variant Also Negotiates"},
        {StatusCode::StatusCodeEnum::InsufficientStorage, "Insufficient Storage"},
        {StatusCode::StatusCodeEnum::LoopDetected, "Loop Detected"},
        {StatusCode::StatusCodeEnum::NetworkAuthenticationRequired, "Network Authentication Required"},
        {StatusCode::StatusCodeEnum::Invalid, ""}
    };

    inline const std::array<StatusCode::Category, static_cast<std::size_t>(5)> StatusCode::Categories = {
        StatusCode::Category::Informational,
        StatusCode::Category::Success,
        StatusCode::Category::Redirection,
        StatusCode::Category::ClientError,
        StatusCode::Category::ServerError
    };

    inline const std::array<StatusCode, static_cast<std::size_t>(62)> StatusCode::StatusCodes = {
        StatusCode(StatusCodeEnum::Continue), StatusCode(StatusCodeEnum::SwitchingProtocols),
        StatusCode(StatusCodeEnum::Processing), StatusCode(StatusCodeEnum::EarlyHints), StatusCode(StatusCodeEnum::OK),
        StatusCode(StatusCodeEnum::Created), StatusCode(StatusCodeEnum::Accepted),
        StatusCode(StatusCodeEnum::NonAuthoritativeInformation), StatusCode(StatusCodeEnum::NoContent),
        StatusCode(StatusCodeEnum::ResetContent), StatusCode(StatusCodeEnum::PartialContent),
        StatusCode(StatusCodeEnum::MultiStatus), StatusCode(StatusCodeEnum::AlreadyReported),
        StatusCode(StatusCodeEnum::IMUsed), StatusCode(StatusCodeEnum::MultipleChoices),
        StatusCode(StatusCodeEnum::MovedPermanently), StatusCode(StatusCodeEnum::Found),
        StatusCode(StatusCodeEnum::SeeOther), StatusCode(StatusCodeEnum::NotModified),
        StatusCode(StatusCodeEnum::UseProxy), StatusCode(StatusCodeEnum::TemporaryRedirect),
        StatusCode(StatusCodeEnum::PermanentRedirect), StatusCode(StatusCodeEnum::BadRequest),
        StatusCode(StatusCodeEnum::Unauthorized), StatusCode(StatusCodeEnum::PaymentRequired),
        StatusCode(StatusCodeEnum::Forbidden), StatusCode(StatusCodeEnum::NotFound),
        StatusCode(StatusCodeEnum::MethodNotAllowed), StatusCode(StatusCodeEnum::NotAcceptable),
        StatusCode(StatusCodeEnum::ProxyAuthenticationRequired), StatusCode(StatusCodeEnum::RequestTimeout),
        StatusCode(StatusCodeEnum::Conflict), StatusCode(StatusCodeEnum::Gone),
        StatusCode(StatusCodeEnum::LengthRequired), StatusCode(StatusCodeEnum::PreconditionFailed),
        StatusCode(StatusCodeEnum::ContentTooLarge), StatusCode(StatusCodeEnum::URITooLong),
        StatusCode(StatusCodeEnum::UnsupportedMediaType), StatusCode(StatusCodeEnum::RangeNotSatisfiable),
        StatusCode(StatusCodeEnum::ExpectationFailed), StatusCode(StatusCodeEnum::MisdirectedRequest),
        StatusCode(StatusCodeEnum::UnprocessableContent), StatusCode(StatusCodeEnum::Locked),
        StatusCode(StatusCodeEnum::FailedDependency), StatusCode(StatusCodeEnum::TooEarly),
        StatusCode(StatusCodeEnum::UpgradeRequired), StatusCode(StatusCodeEnum::PreconditionRequired),
        StatusCode(StatusCodeEnum::TooManyRequests), StatusCode(StatusCodeEnum::RequestHeaderFieldsTooLarge),
        StatusCode(StatusCodeEnum::UnavailableForLegalReasons), StatusCode(StatusCodeEnum::InternalServerError),
        StatusCode(StatusCodeEnum::NotImplemented), StatusCode(StatusCodeEnum::BadGateway),
        StatusCode(StatusCodeEnum::ServiceUnavailable), StatusCode(StatusCodeEnum::GatewayTimeout),
        StatusCode(StatusCodeEnum::HTTPVersionNotSupported), StatusCode(StatusCodeEnum::VariantAlsoNegotiates),
        StatusCode(StatusCodeEnum::InsufficientStorage), StatusCode(StatusCodeEnum::LoopDetected),
        StatusCode(StatusCodeEnum::NetworkAuthenticationRequired)
    };

    // Static utility functions.
    inline StatusCode::StatusCodeEnum StatusCode::_v2e(const StatusCodeValueType value) noexcept {
        switch (value) {
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Continue):
                return StatusCodeEnum::Continue;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::SwitchingProtocols):
                return StatusCodeEnum::SwitchingProtocols;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Processing):
                return StatusCodeEnum::Processing;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::EarlyHints):
                return StatusCodeEnum::EarlyHints;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::OK):
                return StatusCodeEnum::OK;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Created):
                return StatusCodeEnum::Created;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Accepted):
                return StatusCodeEnum::Accepted;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NonAuthoritativeInformation):
                return StatusCodeEnum::NonAuthoritativeInformation;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NoContent):
                return StatusCodeEnum::NoContent;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::ResetContent):
                return StatusCodeEnum::ResetContent;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::PartialContent):
                return StatusCodeEnum::PartialContent;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::MultiStatus):
                return StatusCodeEnum::MultiStatus;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::AlreadyReported):
                return StatusCodeEnum::AlreadyReported;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::IMUsed):
                return StatusCodeEnum::IMUsed;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::MultipleChoices):
                return StatusCodeEnum::MultipleChoices;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::MovedPermanently):
                return StatusCodeEnum::MovedPermanently;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Found):
                return StatusCodeEnum::Found;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::SeeOther):
                return StatusCodeEnum::SeeOther;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NotModified):
                return StatusCodeEnum::NotModified;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::UseProxy):
                return StatusCodeEnum::UseProxy;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::TemporaryRedirect):
                return StatusCodeEnum::TemporaryRedirect;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::PermanentRedirect):
                return StatusCodeEnum::PermanentRedirect;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::BadRequest):
                return StatusCodeEnum::BadRequest;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Unauthorized):
                return StatusCodeEnum::Unauthorized;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::PaymentRequired):
                return StatusCodeEnum::PaymentRequired;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Forbidden):
                return StatusCodeEnum::Forbidden;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NotFound):
                return StatusCodeEnum::NotFound;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::MethodNotAllowed):
                return StatusCodeEnum::MethodNotAllowed;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NotAcceptable):
                return StatusCodeEnum::NotAcceptable;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::ProxyAuthenticationRequired):
                return StatusCodeEnum::ProxyAuthenticationRequired;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::RequestTimeout):
                return StatusCodeEnum::RequestTimeout;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Conflict):
                return StatusCodeEnum::Conflict;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Gone):
                return StatusCodeEnum::Gone;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::LengthRequired):
                return StatusCodeEnum::LengthRequired;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::PreconditionFailed):
                return StatusCodeEnum::PreconditionFailed;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::ContentTooLarge):
                return StatusCodeEnum::ContentTooLarge;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::URITooLong):
                return StatusCodeEnum::URITooLong;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::UnsupportedMediaType):
                return StatusCodeEnum::UnsupportedMediaType;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::RangeNotSatisfiable):
                return StatusCodeEnum::RangeNotSatisfiable;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::ExpectationFailed):
                return StatusCodeEnum::ExpectationFailed;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::MisdirectedRequest):
                return StatusCodeEnum::MisdirectedRequest;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::UnprocessableContent):
                return StatusCodeEnum::UnprocessableContent;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::Locked):
                return StatusCodeEnum::Locked;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::FailedDependency):
                return StatusCodeEnum::FailedDependency;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::TooEarly):
                return StatusCodeEnum::TooEarly;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::UpgradeRequired):
                return StatusCodeEnum::UpgradeRequired;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::PreconditionRequired):
                return StatusCodeEnum::PreconditionRequired;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::TooManyRequests):
                return StatusCodeEnum::TooManyRequests;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::RequestHeaderFieldsTooLarge):
                return StatusCodeEnum::RequestHeaderFieldsTooLarge;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::UnavailableForLegalReasons):
                return StatusCodeEnum::UnavailableForLegalReasons;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::InternalServerError):
                return StatusCodeEnum::InternalServerError;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NotImplemented):
                return StatusCodeEnum::NotImplemented;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::BadGateway):
                return StatusCodeEnum::BadGateway;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::ServiceUnavailable):
                return StatusCodeEnum::ServiceUnavailable;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::GatewayTimeout):
                return StatusCodeEnum::GatewayTimeout;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::HTTPVersionNotSupported):
                return StatusCodeEnum::HTTPVersionNotSupported;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::VariantAlsoNegotiates):
                return StatusCodeEnum::VariantAlsoNegotiates;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::InsufficientStorage):
                return StatusCodeEnum::InsufficientStorage;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::LoopDetected):
                return StatusCodeEnum::LoopDetected;
            case static_cast<StatusCodeValueType>(StatusCodeEnum::NetworkAuthenticationRequired):
                return StatusCodeEnum::NetworkAuthenticationRequired;
            default:
                return _nr(value);
        }
    }

    inline StatusCode::StatusCodeEnum StatusCode::_nr(const StatusCodeValueType code) noexcept {
        if (static_cast<StatusCodeValueType>(100) <= code && code <= static_cast<StatusCodeValueType>(199))
            return StatusCodeEnum::Continue;

        if (static_cast<StatusCodeValueType>(200) <= code && code <= static_cast<StatusCodeValueType>(299))
            return StatusCodeEnum::OK;

        if (static_cast<StatusCodeValueType>(300) <= code && code <= static_cast<StatusCodeValueType>(399))
            return StatusCodeEnum::MultipleChoices;

        if (static_cast<StatusCodeValueType>(400) <= code && code <= static_cast<StatusCodeValueType>(499))
            return StatusCodeEnum::BadRequest;

        if (static_cast<StatusCodeValueType>(500) <= code && code <= static_cast<StatusCodeValueType>(599))
            return StatusCodeEnum::InternalServerError;

        return StatusCodeEnum::Invalid;
    }

    // Constructors.
    inline StatusCode::StatusCode(const StatusCodeEnum code) noexcept : _reason(StatusCodeReasons.at(code)),
                                                                        _value(code) {
    }

    inline StatusCode::StatusCode(const StatusCodeEnum code, const std::string_view reason) noexcept : _reason(reason),
        _value(code) {
    }

    inline StatusCode::StatusCode(const StatusCodeValueType code) noexcept : _value(_v2e(code)) {
        _reason = StatusCodeReasons.at(_value);
    }

    inline StatusCode::StatusCode(const StatusCodeValueType code,
                                  const std::string_view reason) noexcept : _reason(reason), _value(_v2e(code)) {
    }

    // Properties.
    inline StatusCode::StatusCodeEnum &StatusCode::value() noexcept {
        return _value;
    }

    inline StatusCode::StatusCodeEnum StatusCode::value() const noexcept {
        return _value;
    }

    inline StatusCode::StatusCodeEnum &StatusCode::code() noexcept {
        return value();
    }

    inline StatusCode::StatusCodeEnum StatusCode::code() const noexcept {
        return value();
    }

    inline StatusCode::Category StatusCode::category() const noexcept {
        const auto value = static_cast<StatusCodeValueType>(_value);

        if (static_cast<StatusCodeValueType>(100) <= value && value <= static_cast<StatusCodeValueType>(199))
            return Category::Informational;

        if (static_cast<StatusCodeValueType>(200) <= value && value <= static_cast<StatusCodeValueType>(299))
            return Category::Success;

        if (static_cast<StatusCodeValueType>(300) <= value && value <= static_cast<StatusCodeValueType>(399))
            return Category::Redirection;

        if (static_cast<StatusCodeValueType>(400) <= value && value <= static_cast<StatusCodeValueType>(499))
            return Category::ClientError;

        if (static_cast<StatusCodeValueType>(500) <= value && value <= static_cast<StatusCodeValueType>(599))
            return Category::ServerError;

        return Category::Invalid;
    }

    inline std::string &StatusCode::reason() noexcept {
        return _reason;
    }

    inline std::string StatusCode::reason() const noexcept {
        return _reason;
    }

    // Instance-based utility functions.
    inline bool StatusCode::_cmp(const StatusCode &code) const noexcept {
        return _cmp(code._value);
    }

    inline bool StatusCode::_cmp(const StatusCodeEnum code) const noexcept {
        return _cmp(static_cast<StatusCodeValueType>(code));
    }

    template<std::integral T>
    inline bool StatusCode::_cmp(const T code) const noexcept {
        if constexpr (std::is_same_v<T, StatusCodeValueType> || sizeof(T) <= sizeof(StatusCodeValueType))
            return static_cast<StatusCodeValueType>(_value) == static_cast<StatusCodeValueType>(code);

        return false;
    }

    inline void StatusCode::reset() noexcept {
        _value = StatusCodeEnum::Invalid;
        _reason.clear();
    }

    // Static utility functions.
    inline StatusCode::operator bool() const noexcept {
        return _value != StatusCodeEnum::Invalid;
    }

    inline StatusCode::operator StatusCodeEnum() const noexcept {
        return _value;
    }

    inline StatusCode::operator StatusCodeValueType() const noexcept {
        return static_cast<StatusCodeValueType>(_value);
    }

    inline StatusCode::operator Category() const noexcept {
        return category();
    }

    inline StatusCode::operator std::string_view() const noexcept {
        return _reason;
    }

    inline StatusCode &StatusCode::operator=(const StatusCodeEnum code) noexcept {
        _value = code;

        try {
            _reason = StatusCodeReasons.at(_value);
        } catch (...) {
            _reason.clear();
        }

        return *this;
    }

    inline StatusCode &StatusCode::operator=(const StatusCodeValueType code) noexcept {
        _value = _v2e(code);
        _reason = StatusCodeReasons.at(_value);

        try {
            _reason = StatusCodeReasons.at(_value);
        } catch (...) {
            _reason.clear();
        }

        return *this;
    }

    inline StatusCode &StatusCode::operator=(const std::string_view reason) noexcept {
        try {
            _reason = reason;
        } catch (...) {
            _reason.clear();
        }

        return *this;
    }

    inline bool StatusCode::operator==(const StatusCode &code) const noexcept {
        return _cmp(code);
    }

    inline bool StatusCode::operator==(const StatusCodeEnum code) const noexcept {
        return _cmp(code);
    }

    inline bool StatusCode::operator==(const StatusCodeValueType code) const noexcept {
        return _cmp(code);
    }

    inline bool StatusCode::operator!=(const StatusCode &code) const noexcept {
        return !_cmp(code);
    }

    inline bool StatusCode::operator!=(const StatusCodeEnum code) const noexcept {
        return !_cmp(code);
    }

    inline bool StatusCode::operator!=(const StatusCodeValueType code) const noexcept {
        return !_cmp(code);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_IMPL_STATUS_CODE_IPP
