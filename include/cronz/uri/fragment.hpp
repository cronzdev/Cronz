/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_URL_FRAGMENT_HPP
#define CRONZ_URL_FRAGMENT_HPP 1

#include "cronz/uri/types.hpp"

CRONZ_BEGIN_URI_NAMESPACE
    /**
     * @ingroup cronz_uri
     * @brief URL fragment.
     * @class Fragment
     */
    class Fragment {
        // Properties.
        std::string _value;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Default constructor.
         */
        Fragment() noexcept = default;

        /**
         * @brief Constructor with value.
         * @param[in] fragment Fragment value.
         */
        explicit(false) Fragment(std::string_view fragment) noexcept;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Get fragment value.
         * @return Fragment value.
         */
        CRONZ_NODISCARD_L1 std::string_view get() const noexcept;

        /**
         * @brief Set fragment value.
         * @param[in] fragment New fragment value.
         * @return `true` if the value is successfully assigned.
         * @return `false` if the value is not successfully assigned.
         */
        CRONZ_NODISCARD_L2 bool set(std::string_view fragment) noexcept;

        /**
         * @brief Returns the length of the encoded fragment.
         * @return Length of the encoded fragment.
         */
        CRONZ_NODISCARD_L1 std::size_t length() const noexcept;

        /**
         * @brief Tells whether the fragment is empty.
         * @return `true` if the fragment is empty.
         * @return `false` if the fragment is not empty.
         */
        CRONZ_NODISCARD_L1 bool empty() const noexcept;

        /**
         * @brief Clears the fragment.
         */
        void clear() noexcept;

        /** @} */

        /**
         * @name Parsing & Stringification.
         */
        /** @{ */
        /**
         * @brief Parses a fragment from a string.
         * @param[in] fragment String to parse.
         * @return `true` if the fragment is successfully parsed.
         * @return `false` if the fragment is not successfully parsed.
         */
        CRONZ_NODISCARD_L2 bool parse(std::string_view fragment) noexcept;

        /**
         * @brief Stringifies the fragment.
         * @return Fragment value.
         */
        CRONZ_NODISCARD_L1 std::string stringify() const noexcept;

        /**
         * @brief Stringifies the fragment.
         * @param[in] str String to append the fragment to.
         * @return `true` if the fragment is successfully stringified.
         * @return `false` if the fragment is not successfully stringified.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str) const noexcept;

        /**
         * @brief Stringifies the fragment.
         * @param[in] str String to append the fragment to.
         * @param[in] offset Offset to start appending the fragment to.
         * @return `true` if the fragment is successfully stringified.
         * @return `false` if the fragment is not successfully stringified.
         */
        CRONZ_NODISCARD_L2 bool stringify(std::string &str, std::size_t &offset) const noexcept;

        /** @} */

        /**
         * @name Operators.
         */
        /** @{ */
        /**
         * @brief Boolean conversion operator.
         * @return `true` if the fragment is empty.
         * @return `false` if the fragment is not empty.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator bool() const noexcept;

        /**
         * @brief Conversion operator to `std::string_view`.
         * @return Fragment value.
         */
        CRONZ_NODISCARD_L1 explicit(false) operator std::string_view() const noexcept;

        /**
         * @brief Assignment operator.
         * @param[in] fragment New fragment value.
         * @return Reference to the fragment.
         */
        Fragment &operator=(std::string_view fragment) noexcept;

        /**
         * @brief Equality operator.
         * @param[in] fragment Another fragment to compare.
         * @return `true` if the fragments are equal.
         * @return `false` if the fragments are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(std::string_view fragment) const noexcept;

        /**
         * @brief Equality operator.
         * @param[in] fragment Another fragment to compare.
         * @return `true` if the fragments are equal.
         * @return `false` if the fragments are not equal.
         */
        CRONZ_NODISCARD_L1 bool operator==(const Fragment &fragment) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] fragment Another fragment to compare.
         * @return `true` if the fragments are not equal.
         * @return `false` if the fragments are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(const Fragment &fragment) const noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] fragment Another fragment to compare.
         * @return `true` if the fragments are not equal.
         * @return `false` if the fragments are equal.
         */
        CRONZ_NODISCARD_L1 bool operator!=(std::string_view fragment) const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~Fragment() noexcept = default;

        /** @} */

        /**
         * @name Friends.
         */
        /** @{ */
        /**
         * @brief Equality operator.
         * @param[in] fragment Fragment value.
         * @param[in] instance Fragment instance.
         * @return `true` if the fragment is equal to the instance.
         * @return `false` if the fragment is not equal to the instance.
         */
        friend bool operator==(std::string_view fragment, const Fragment &instance) noexcept;

        /**
         * @brief Inequality operator.
         * @param[in] fragment Fragment value.
         * @param[in] instance Fragment instance.
         * @return `true` if the fragment is not equal to the instance.
         * @return `false` if the fragment is equal to the instance.
         */
        friend bool operator!=(std::string_view fragment, const Fragment &instance) noexcept;

        /** @} */
    };

CRONZ_END_URI_NAMESPACE

#include "cronz/uri/impl/fragment.ipp"

#endif // CRONZ_URL_FRAGMENT_HPP
