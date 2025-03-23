/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URI_HOST_IMPL_HOST_IPP
#define CRONZ_URI_HOST_IMPL_HOST_IPP 1

#include "cronz/uri/authority/host.hpp"

#include "cronz/uri/decode.hpp"
#include "cronz/uri/encode.hpp"

#include "cronz/rfc/rule/domain.hpp"
#include "cronz/rfc/rule/host.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    // Properties.
    inline bool Host::_generateIndices() noexcept {
        if (isRegisteredName()) {
            try {
                _indices.push_back(static_cast<std::size_t>(0));
                return true;
            } catch (...) {
                clear();
                return false;
            }
        }

        const char delimiter = ((isIPv6()) ? ':' : '.');

        std::size_t n = std::ranges::count_if(_value, [delimiter](const char c) -> bool {
            return delimiter == c;
        });

        if (_value.front() != delimiter)
            ++n;

        try {
            _indices.reserve(n);

            if (_value.front() != delimiter)
                _indices.push_back(static_cast<std::size_t>(0));
        } catch (...) {
            clear();
            return false;
        }

        n = static_cast<std::size_t>(0);
        for (const char c: _value) {
            ++n;

            if (delimiter == c)
                _indices.push_back(n);
        }

        return true;
    }

    inline IPv4Address Host::ipv4() const noexcept {
        return isIPv4() ? _ip._ipv4 : IPv4Address();
    }

    inline IPv6Address Host::ipv6() const noexcept {
        return isIPv6() ? _ip._ipv6 : IPv6Address();
    }

    inline std::string_view Host::value() const noexcept {
        return _value;
    }

    inline bool Host::isIPv4() const noexcept {
        return IPv4 == _type;
    }

    inline bool Host::isIPv6() const noexcept {
        return IPv6 == _type;
    }

    inline bool Host::isRegisteredName() const noexcept {
        return Name == _type;
    }

    inline bool Host::isDNSDomain() const noexcept {
        return DNSD == _type;
    }

    inline std::size_t Host::length() const noexcept {
        return isRegisteredName() ? URICalculateEncodedComponentLength(_value) : _value.length();
    }

    inline std::size_t Host::count() const noexcept {
        return _indices.size();
    }

    inline bool Host::empty() const noexcept {
        return _value.empty();
    }

    inline void Host::clear() noexcept {
        _value.clear();
        _indices.clear();
        _type = None;
    }

    // Assignment.
    inline bool Host::assign(const IPv4Address &address) noexcept {
        clear();

        if (address.stringify(_value)) {
            _ip._ipv4 = address;
            _type = IPv4;
            return _generateIndices();
        }

        clear();
        return false;
    }

    inline bool Host::assign(const IPv6Address &address) noexcept {
        clear();

        if (address.stringify(_value)) {
            _ip._ipv6 = address;
            _type = IPv6;
            return _generateIndices();
        }

        clear();
        return false;
    }

    inline bool Host::assign(const std::string_view address) noexcept {
        clear();

        if (address.empty())
            return true;

        if ('[' == address.front()) {
            if (']' != address.back())
                goto parse_bad;

            const std::string_view v6 = address.substr(1, address.length() - 2);

            _ip._ipv6 = IPv6Address();
            if (!_ip._ipv6.parse(v6) || _ip._ipv6.hasMask())
                goto parse_bad;

            _type = IPv6;

            goto parse_ok;
        }

        if (!RFC::IsRegName(address))
            goto parse_bad;

        try {
            _value.assign(address);
        } catch (...) {
            goto parse_bad;
        }

        _ip._ipv4 = IPv4Address();
        if (_ip._ipv4.parse(address)) {
            _type = IPv4;

            if (_ip._ipv4.hasMask())
                goto parse_bad;

            goto parse_ok;
        }

        if (RFC::IsDomain(address)) {
            _type = DNSD;
            goto parse_ok;
        }

        _type = Name;

    parse_ok:
        try {
            _value.assign(address);
        } catch (...) {
            goto parse_bad;
        }

        if (isRegisteredName() && !URIDecodeComponentInPlace(_value))
            goto parse_bad;

        for (char &c: _value) {
            if (RFC::IsAlphaUpper(c))
                c = static_cast<char>(c + 32);
        }

        return _generateIndices();

    parse_bad:
        clear();
        return false;
    }

    // Stringification.
    inline std::string Host::stringify() const noexcept {
        std::string str;
        return stringify(str) ? str : std::string();
    }

    inline bool Host::stringify(std::string &str) const noexcept {
        str.clear();

        auto offset = static_cast<std::size_t>(0);
        return stringify(str, offset);
    }

    inline bool Host::stringify(std::string &str, std::size_t &offset) const noexcept {
        if (const std::size_t len = (length() + offset);
            str.length() < len) {
            try {
                str.resize(len);
            } catch (...) {
                return false;
            }
        }

        if (isRegisteredName())
            return URIEncodeComponent(_value, str, offset);

        memcpy(str.data() + offset, _value.data(), _value.length());
        offset += _value.length();

        return true;
    }

    // Instance-based utility functions.
    inline void Host::forEach(const IterationCallbackFunction &callback) const noexcept {
        auto previous = static_cast<std::size_t>(0);

        for (auto i = static_cast<std::size_t>(1); i < _indices.size(); ++i) {
            const std::size_t index = _indices[i];

            callback(std::string_view(&_value[previous], &_value[index - static_cast<std::size_t>(1)]));

            previous = index;
        }

        callback(std::string_view(&_value[previous], _value.length() - previous));
    }

    // Operators.
    inline Host::operator bool() const noexcept {
        return !empty();
    }

CRONZ_END_URI_NAMESPACE

#endif // CRONZ_URI_HOST_IMPL_HOST_IPP
