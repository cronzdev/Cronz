/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_TYPES_HPP
#define CRONZ_SESSION_TYPES_HPP 1

#include "cronz/internal/namespace.hpp"

#define CRONZ_SESSION_NAMESPACE_INTERNAL    CRONZ_NAMESPACE_INTERNAL

#define CRONZ_BEGIN_SESSION_NAMESPACE   CRONZ_BEGIN_MAIN_NAMESPACE
#define CRONZ_END_SESSION_NAMESPACE     CRONZ_END_MAIN_NAMESPACE

#define CRONZ_BEGIN_SESSION_INTERNAL_NAMESPACE  CRONZ_BEGIN_MAIN_INTERNAL_NAMESPACE
#define CRONZ_END_SESSION_INTERNAL_NAMESPACE    CRONZ_END_MAIN_INTERNAL_NAMESPACE

#include <chrono>
#include <cstdint>

CRONZ_BEGIN_SESSION_NAMESPACE
    /**
     * @ingroup cronz_session
     * @brief Session ID type.
     * @typedef std::uint_fast64_t SessionId
     */
    using SessionId = std::uint_fast64_t;

    /**
     * @ingroup cronz_session
     * @brief Session time type.
     * @typedef std::chrono::system_clock::duration::rep SessionTime
     */
    using SessionTime = std::chrono::system_clock::duration::rep;

    /**
     * @ingroup cronz_session
     * @brief Session count type.
     * @typedef std::uint_fast64_t SessionCount
     */
    using SessionCount = std::uint_fast64_t;

    template<typename SessionDataType>
    class Session;

    /**
     * @ingroup cronz_session
     * @brief Session reference type.
     * @typedef std::shared_ptr<Session<SessionDataType> > SessionRef
     */
    template<typename SessionDataType>
    using SessionRef = std::shared_ptr<Session<SessionDataType> >;

    /**
     * @ingroup cronz_session
     * @brief Session pointer type.
     * @typedef Session<SessionDataType> * SessionPtr
     */
    template<typename SessionDataType>
    using SessionPtr = Session<SessionDataType> *;

    /**
     * @ingroup cronz_session
     * @brief Session Id generator function type.
     * @typedef SessionId (*SessionIdGeneratorFunctionType)()
     */
    using SessionIdGeneratorFunctionType = SessionId(*)();

    /**
     * @ingroup cronz_session
     * @brief Session on create function type.
     * @typedef void (*SessionOnCreateFunctionType)(const SessionRef<SessionDataType> &)
     */
    template<typename SessionDataType>
    using SessionOnCreateFunctionType = void(*)(const SessionRef<SessionDataType> &);

    /**
     * @ingroup cronz_session
     * @brief Session on destroy function type.
     * @typedef void (*SessionOnDestroyFunctionType)(const SessionRef<SessionDataType> &)
     */
    template<typename SessionDataType>
    using SessionOnDestroyFunctionType = void(*)(const SessionRef<SessionDataType> &);

CRONZ_END_SESSION_NAMESPACE

#endif // CRONZ_SESSION_TYPES_HPP
