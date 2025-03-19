/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_INTERNAL_OS_HPP
#define CRONZ_INTERNAL_OS_HPP 1

// Windows
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define CRONZ_OS_WINDOWS 1
#endif // defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)

// Windows (Cygwin)
#if defined(__CYGWIN__)
#define CRONZ_OS_WINDOWS_CYGWIN 1
#endif // defined(__CYGWIN__)

// Linux
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define CRONZ_OS_LINUX 1
#endif // defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)

// UNIX
#if defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#define CRONZ_OS_UNIX 1
#endif // defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)

#endif // CRONZ_INTERNAL_OS_HPP
