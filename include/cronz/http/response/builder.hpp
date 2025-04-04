/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_RESPONSE_BUILDER_HPP
#define CRONZ_HTTP_RESPONSE_BUILDER_HPP 1

#include "cronz/http/response/response.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class ResponseBuilder final {
        enum class State : std::int_fast32_t {
            NONE = 1,

            PREPARED,

            HEADERS,

            BODY_CONTENT,
            BODY_FINISHED,

            COMPLETE
        };

        // Properties.
        std::size_t _size;
        std::string _block;
        std::size_t _offset;

        State _state = State::NONE;
        Version _version = Version::Invalid;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        ResponseBuilder() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 bool isComplete() const noexcept;

        /** @} */

        /**
         * @name Response building.
         */
        /** @{ */
        CRONZ_NODISCARD_L2 bool prepare(const Version &version, Response &response) noexcept;

        CRONZ_NODISCARD_L2 bool buildNextBlock(Response &response) noexcept;

        CRONZ_NODISCARD_L1 std::string_view getBlockData() const noexcept;

        void advance(std::size_t bytes) noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~ResponseBuilder() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/response/impl/builder.ipp"

#endif // CRONZ_HTTP_RESPONSE_BUILDER_HPP
