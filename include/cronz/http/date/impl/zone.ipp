/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_DATE_IMPL_ZONE_IPP
#define CRONZ_HTTP_DATE_IMPL_ZONE_IPP 1

#include "cronz/http/date/zone.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Static constants and types.
    inline const std::array<std::pair<Zone::Offset, std::string_view>, static_cast<std::size_t>(12)>
    Zone::OffsetAbbreviations = {
        std::make_pair(ADT, "ADT"), std::make_pair(AST, "AST"), std::make_pair(BST, "BST"),
        std::make_pair(CET, "CET"), std::make_pair(CST, "CST"), std::make_pair(EDT, "EDT"),
        std::make_pair(EST, "EST"), std::make_pair(GMT, "GMT"), std::make_pair(JST, "JST"),
        std::make_pair(PST, "PST"), std::make_pair(PDT, "PDT"), std::make_pair(UTC, "UTC")
    };

    // Constructors.
    inline Zone::Zone(const ZoneOffsetType offset) noexcept : _offset(offset) {
    }

    inline Zone::Zone(const Offset offset) noexcept : _offset(static_cast<ZoneOffsetType>(offset)) {
    }

    inline Zone::Zone(const std::string_view zone) noexcept {
        [[maybe_unused]] const bool _ = _parseTimezone(zone);
    }

    // Properties.
    inline Zone::ZoneOffsetType Zone::timezoneOffset() const noexcept {
        return getTimezoneOffset();
    }

    inline Zone::ZoneOffsetType Zone::getTimezoneOffset() const noexcept {
        return _offset;
    }

    inline bool Zone::timezoneOffset(const ZoneOffsetType offset) noexcept {
        return setTimezoneOffset(offset);
    }

    inline bool Zone::setTimezoneOffset(const ZoneOffsetType offset) noexcept {
        const auto h = static_cast<ZoneOffsetType>(offset / static_cast<ZoneOffsetType>(100));
        const auto m = static_cast<ZoneOffsetType>(offset % static_cast<ZoneOffsetType>(100));

        if (static_cast<ZoneOffsetType>(-23) <= h && h <= static_cast<ZoneOffsetType>(23) &&
            static_cast<ZoneOffsetType>(-59) <= m && m <= static_cast<ZoneOffsetType>(59)) {
            _offset = offset;
            return true;
        }

        return false;
    }

    inline Zone::ZoneOffsetType Zone::getTimezoneOffsetInMinutes() const noexcept {
        const auto h = static_cast<ZoneOffsetType>(std::abs(
            static_cast<ZoneOffsetType>(_offset / static_cast<ZoneOffsetType>(100))));
        const auto m = static_cast<ZoneOffsetType>(std::abs(
            static_cast<ZoneOffsetType>(_offset % static_cast<ZoneOffsetType>(100))));

        const ZoneOffsetType v = h * static_cast<ZoneOffsetType>(60) + m;
        return (_offset < static_cast<ZoneOffsetType>(0)) ? -v : v;
    }

    inline bool Zone::setTimezoneOffsetInMinutes(const ZoneOffsetType minutes) noexcept {
        if (static_cast<ZoneOffsetType>(1440) < std::abs(minutes))
            return false;

        const auto h = static_cast<ZoneOffsetType>(std::abs(
            static_cast<ZoneOffsetType>(minutes / static_cast<ZoneOffsetType>(60))));
        const auto m = static_cast<ZoneOffsetType>(std::abs(
            static_cast<ZoneOffsetType>(minutes % static_cast<ZoneOffsetType>(60))));

        const ZoneOffsetType v = h * static_cast<ZoneOffsetType>(100) + m;
        return setTimezoneOffset((minutes < static_cast<ZoneOffsetType>(0)) ? -v : v);
    }

    inline void Zone::setTimezone(const Zone &zone) noexcept {
        _offset = zone._offset;
    }

    // Instance-based utility functions.
    inline void Zone::_resetZone() noexcept {
        _offset = static_cast<ZoneOffsetType>(0);
    }

    // Parsing.
    inline bool Zone::_parseOffset(const std::string_view offset) noexcept {
        auto value = static_cast<ZoneOffsetType>(0);

        for (auto i = static_cast<std::size_t>(1); i < offset.length(); ++i) {
            const char c = offset[i];
            if (!RFC::IsDigit(c))
                goto parse_bad;

            value = (value * static_cast<ZoneOffsetType>(10)) + static_cast<ZoneOffsetType>(c - '0');
        }

        if ('-' == offset.front())
            value = -value;
        else if ('+' != offset.front())
            goto parse_bad;

        return setTimezoneOffset(value);

    parse_bad:
        _resetZone();
        return false;
    }

    inline bool Zone::_parseZone(const std::string_view zone) noexcept {
        for (const auto &[offset, abbreviation]: OffsetAbbreviations) {
            if (zone == abbreviation) {
                _offset = static_cast<ZoneOffsetType>(offset);
                return true;
            }
        }

        _resetZone();
        return false;
    }

    inline bool Zone::_parseTimezone(const std::string_view timezone) noexcept {
        if (static_cast<std::size_t>(3) == timezone.size())
            return _parseZone(timezone);

        if (static_cast<std::size_t>(5) == timezone.size())
            return _parseOffset(timezone);

        return false;
    }

    // Operators.
    inline bool Zone::operator==(const Zone &zone) const noexcept {
        return _offset == zone._offset;
    }

    inline bool Zone::operator!=(const Zone &zone) const noexcept {
        return _offset != zone._offset;
    }

    inline bool Zone::operator<(const Zone &zone) const noexcept {
        return _offset < zone._offset;
    }

    inline bool Zone::operator<=(const Zone &zone) const noexcept {
        return _offset <= zone._offset;
    }

    inline bool Zone::operator>(const Zone &zone) const noexcept {
        return _offset > zone._offset;
    }

    inline bool Zone::operator>=(const Zone &zone) const noexcept {
        return _offset >= zone._offset;
    }

    // Static utility functions.
    inline Zone Zone::CurrentZone() noexcept {
        const std::time_t n = std::time(nullptr);
        const std::time_t l = std::mktime(std::localtime(&n));
        const std::time_t g = std::mktime(std::gmtime(&n));

        return Zone(static_cast<ZoneOffsetType>(l - g));
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_DATE_IMPL_ZONE_IPP
