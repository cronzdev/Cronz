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

#ifndef CRONZ_INTERNAL_OS_HPP
#define CRONZ_INTERNAL_OS_HPP 1

// Windows
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define CRONZ_OS 1
#define CRONZ_OS_WINDOWS 1
#endif // defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)

// Windows (Cygwin)
#if defined(__CYGWIN__)
#define CRONZ_OS 1
#define CRONZ_OS_WINDOWS_CYGWIN 1
#endif // defined(__CYGWIN__)

// Linux
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define CRONZ_OS 1
#define CRONZ_OS_LINUX 1
#endif // defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)

// UNIX
#if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#define CRONZ_OS 1
#define CRONZ_OS_UNIX 1
#endif // defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)

#ifndef CRONZ_OS
#error "Unsupported or unidentified operating system."
#endif // CRONZ_OS

#endif // CRONZ_INTERNAL_OS_HPP
