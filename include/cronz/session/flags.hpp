/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_SESSION_FLAGS_HPP
#define CRONZ_SESSION_FLAGS_HPP 1

#include "cronz/session/types.hpp"

CRONZ_BEGIN_SESSION_NAMESPACE
    /**
     * @ingroup cronz_session
     * @brief Session manager configuration flags.
     * @enum SessionManagerConfigurationFlagBits
     */
    enum SessionManagerConfigurationFlagBits : std::uint64_t {
        /**
         * @brief Enables multithreading for the session manager.
         * @remark If not used, the session manager will be single-threaded.
         */
        SESSION_MANAGER_ENABLE_MULTITHREADED = 0x0000000000000001,

        /**
         * @brief Tells the session manager to use raw pointers for the session data.
         * @remark If not used, the session manager will use smart pointers for the session data.
         */
        SESSION_MANAGER_USE_RAW_POINTER = 0x0000000000000002,
    };

    /**
     * @ingroup cronz_session
     * @brief Session manager configuration flag type.
     * @typedef std::uint64_t SessionManagerConfigurationFlags
     */
    typedef std::uint64_t SessionManagerConfigurationFlags;

    /**
     * @ingroup cronz_session
     * @brief Default session manager configuration flags.
     * @var SessionManagerConfigurationFlags DefaultSessionManagerConfigurationFlags
     */
    inline static constexpr SessionManagerConfigurationFlags DefaultSessionManagerConfigurationFlags =
            SESSION_MANAGER_ENABLE_MULTITHREADED;

CRONZ_END_SESSION_NAMESPACE

#endif // CRONZ_SESSION_FLAGS_HPP
