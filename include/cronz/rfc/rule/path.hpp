/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_RFC_RULE_PATH_HPP
#define CRONZ_RFC_RULE_PATH_HPP 1

#include "cronz/rfc/types.hpp"

CRONZ_BEGIN_RFC_NAMESPACE
    CRONZ_NODISCARD_L1 bool IsPath(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsPathAbEmpty(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsPathAbsolute(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsPathNoScheme(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsPathRootless(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsPathEmpty(std::string_view path) noexcept;

    CRONZ_NODISCARD_L1 bool IsSegment(std::string_view segment) noexcept;

    CRONZ_NODISCARD_L1 bool IsSegmentNz(std::string_view segment) noexcept;

    CRONZ_NODISCARD_L1 bool IsSegmentNzNc(std::string_view segment) noexcept;

CRONZ_END_RFC_NAMESPACE

#include "cronz/rfc/rule/impl/path.ipp"

#endif // CRONZ_RFC_RULE_PATH_HPP
