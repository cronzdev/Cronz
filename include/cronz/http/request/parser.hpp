/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_REQUEST_PARSER_HPP
#define CRONZ_HTTP_REQUEST_PARSER_HPP 1

#include "cronz/http/request/request.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    class RequestParser final {
        // Static type definitions.
        enum class State : std::int_fast32_t {
            START,

            HTTP_METHOD,
            HTTP_PATH,
            HTTP_VERSION_H,
            HTTP_VERSION_HT,
            HTTP_VERSION_HTT,
            HTTP_VERSION_HTTP,
            HTTP_VERSION_HTTP_,
            HTTP_VERSION_HTTP_1,
            HTTP_VERSION_HTTP_1_,
            HTTP_VERSION_HTTP_1_1,

            HTTP_HEADER_CR,
            HTTP_HEADER_LF,
            HTTP_HEADER_START,
            HTTP_HEADER,

            HTTP_BODY_CR,
            HTTP_BODY_LF,
            HTTP_BODY,

            BAD_METHOD,
            BAD_PATH,
            BAD_VERSION,
            BAD_CRLF,
            BAD_HEADER,
            BAD_BODY,

            COMPLETE
        };

        // Properties.
        Request _request{};
        std::array<char, static_cast<std::size_t>(1024)> _buffer{};
        std::size_t _bufferLength = static_cast<std::size_t>(0);
        State _state = State::START;
        Version _version = Version::Invalid;

        // Request parsing.
        template<Version::Enum Version>
        CRONZ_NODISCARD_L1 bool _feed(const char *data, std::size_t length) noexcept;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        RequestParser() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Returns the request.
         * @return The request.
         */
        CRONZ_NODISCARD_L1 constexpr const Request &request() const noexcept;

        CRONZ_NODISCARD_L1 bool isComplete() const noexcept;

        CRONZ_NODISCARD_L1 bool isInvalid() const noexcept;

        CRONZ_NODISCARD_L1 bool isIndeterminate() const noexcept;

        /** @} */

        /**
         * @name Request parsing.
         */
        /** @{ */
        CRONZ_NODISCARD_L1 bool feed(const char *data, std::size_t length) noexcept;

        /** @} */

        /**
         * @name Instance-based utility functions.
         */
        /** @{ */
        void reset() noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Default destructor.
         */
        ~RequestParser() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/request/impl/parser.ipp"

#endif // CRONZ_HTTP_REQUEST_PARSER_HPP
