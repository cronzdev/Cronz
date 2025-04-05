/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_METHOD_IMPL_METHOD_IPP
#define CRONZ_HTTP_METHOD_IMPL_METHOD_IPP 1

#include "cronz/http/method/method.hpp"

#include "cronz/rfc/rule/token.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    inline const std::array<Method, static_cast<std::size_t>(8)> Method::PredefinedMethods = {
        Method(Method::GET), Method(Method::HEAD), Method(Method::POST), Method(Method::PUT),
        Method(Method::DELETE), Method(Method::CONNECT), Method(Method::OPTIONS), Method(Method::TRACE)
    };

    // Constructors.
    inline Method::Method(const std::string_view method) noexcept : value(method) {
    }

    // Instance-based utility functions.
    inline bool Method::isValid() const noexcept {
        return IsValid(value);
    }

    inline bool Method::compare(const std::string_view method) const noexcept {
        return isValid() && IsValid(method) && RFC::CompareTokens(value, method);
    }

    inline bool Method::compare(const Method &method) const noexcept {
        return compare(method.value);
    }

    // Operators.
    inline Method::operator bool() const noexcept {
        return isValid();
    }

    inline Method::operator std::string_view() const noexcept {
        return value;
    }

    inline Method &Method::operator=(const std::string_view method) noexcept {
        try {
            value.assign(method);
        } catch (...) {
            value.clear();
        }

        return *this;
    }

    inline bool Method::operator==(const std::string_view method) const noexcept {
        return compare(method);
    }

    inline bool Method::operator==(const Method &method) const noexcept {
        return compare(method);
    }

    inline bool Method::operator!=(const std::string_view method) const noexcept {
        return !compare(method);
    }

    inline bool Method::operator!=(const Method &method) const noexcept {
        return !compare(method);
    }

    // Static utility functions.
    inline bool Method::IsValid(const std::string_view method) noexcept {
        return RFC::IsToken(method);
    }

    // Friends.
    inline bool operator==(const std::string_view method, const Method &instance) noexcept {
        return instance.compare(method);
    }

    inline bool operator!=(const std::string_view method, const Method &instance) noexcept {
        return !instance.compare(method);
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_METHOD_IMPL_METHOD_IPP
