/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

/* * * * * * * * * * * * * * * *
 * WARNING: INTERNAL USE ONLY  *
 * * * * * * * * * * * * * * * *
 * This header is for internal configuration macros used throughout the Cronz library.
 * Please do not include this file directly in your projects, or use the macros defined here in your code.
 * These macros are intended for internal use only and may change without notice.
 */

#ifndef CRONZ_INTERNAL_CONFIG_HPP
#define CRONZ_INTERNAL_CONFIG_HPP 1

/* * * * * * * * *
 * [[nodiscard]] *
 * * * * * * * * */
// CRONZ_NODISCARD_L1 and CRONZ_NODISCARD_L2 are provided for different levels of nodiscard enforcement, which can be
// disabled individually if needed.
#ifndef CRONZ_NODISCARD
#define CRONZ_NODISCARD [[nodiscard]]
#endif // CRONZ_NODISCARD

#ifndef CRONZ_NODISCARD_L1
#ifndef CRONZ_DISABLE_NODISCARD_L1
#define CRONZ_NODISCARD_L1 CRONZ_NODISCARD
#else
#define CRONZ_NODISCARD_L1
#endif // CRONZ_DISABLE_NODISCARD_L1
#endif // CRONZ_NODISCARD_L1

#ifndef CRONZ_NODISCARD_L2
#ifndef CRONZ_DISABLE_NODISCARD_L2
#define CRONZ_NODISCARD_L2 CRONZ_NODISCARD
#else
#define CRONZ_NODISCARD_L2
#endif // CRONZ_DISABLE_NODISCARD_L2
#endif // CRONZ_NODISCARD_L2

#endif // CRONZ_INTERNAL_CONFIG_HPP
