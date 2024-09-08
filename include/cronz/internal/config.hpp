/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_INTERNAL_CONFIG_HPP
#define CRONZ_INTERNAL_CONFIG_HPP 1

// [[nodiscard]]
#ifndef CRONZ_DISABLE_NODISCARD_L1
#define CRONZ_NODISCARD_L1 [[nodiscard]]
#else // CRONZ_DISABLE_NODISCARD_L1
#define CRONZ_NODISCARD_L1
#endif // CRONZ_DISABLE_NODISCARD_L1

#ifndef CRONZ_DISABLE_NODISCARD_L2
#define CRONZ_NODISCARD_L2 [[nodiscard]]
#else // CRONZ_DISABLE_NODISCARD_L2
#define CRONZ_NODISCARD_L2
#endif // CRONZ_DISABLE_NODISCARD_L2

#endif // CRONZ_INTERNAL_CONFIG_HPP
