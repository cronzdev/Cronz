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

#ifndef CRONZ_INTERNAL_NAMESPACE_HPP
#define CRONZ_INTERNAL_NAMESPACE_HPP 1

/* * * * * * * * * * *
 * Namespace Macros  *
 * * * * * * * * * * */
#define CRONZ_NAMESPACE_NAME                    Cronz
#define CRONZ_NAMESPACE_INTERNAL                Internal

#define CRONZ_BEGIN_NAMESPACE(ns_)              namespace ns_ {
#define CRONZ_END_NAMESPACE                     }

#define CRONZ_BEGIN_MAIN_NAMESPACE              CRONZ_BEGIN_NAMESPACE(CRONZ_NAMESPACE_NAME)
#define CRONZ_END_MAIN_NAMESPACE                CRONZ_END_NAMESPACE

#define CRONZ_BEGIN_MAIN_INTERNAL_NAMESPACE     CRONZ_BEGIN_NAMESPACE(CRONZ_NAMESPACE_NAME::CRONZ_NAMESPACE_INTERNAL)
#define CRONZ_END_MAIN_INTERNAL_NAMESPACE       CRONZ_END_NAMESPACE

#endif // CRONZ_INTERNAL_NAMESPACE_HPP
