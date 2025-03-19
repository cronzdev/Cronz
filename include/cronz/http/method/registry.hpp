/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_METHOD_REGISTRY_HPP
#define CRONZ_HTTP_METHOD_REGISTRY_HPP 1

#include "cronz/http/method/method.hpp"

#include <vector>

CRONZ_BEGIN_HTTP_NAMESPACE
    /**
     * @ingroup cronz_http
     * @brief Method registry.
     * @class MethodRegistry
     */
    class MethodRegistry {
        // Properties.
        std::vector<Method> _methods;

    public:
        /**
         * @name Constructors.
         */
        /** @{ */
        /**
         * @brief Constructor.
         */
        MethodRegistry() noexcept = default;

        /** @} */

        /**
         * @name Properties.
         */
        /** @{ */
        /**
         * @brief Method count.
         * @return Method count.
         */
        CRONZ_NODISCARD_L1 std::size_t count() const noexcept;

        /** @} */

        /**
         * @name Method registration.
         */
        /** @{ */
        /**
         * @brief Registers a method.
         * @param[in] method Method value.
         * @return `true` if the method is registered.
         * @return `false` if the method is not registered.
         * @details The method is registered if it is not already registered. The method value is case-sensitive.
         */
        CRONZ_NODISCARD_L2 bool registerMethod(std::string_view method) noexcept;

        /**
         * @brief Registers a method.
         * @param[in] method Method value.
         * @return `true` if the method is registered.
         * @return `false` if the method is not registered.
         * @details The method is registered if it is not already registered. The method value is case-sensitive.
         */
        CRONZ_NODISCARD_L2 bool registerMethod(const Method &method) noexcept;

        /**
         * @brief Registers the predefined methods.
         * @return `true` if the methods are registered.
         * @return `false` if the methods are not registered.
         */
        CRONZ_NODISCARD_L2 bool registerAllPredefinedMethods() noexcept;

        /**
         * @brief Checks if a method is registered.
         * @param[in] method Method value.
         * @return `true` if the method is registered.
         * @return `false` if the method is not registered.
         * @details The method value is case-sensitive.
         */
        CRONZ_NODISCARD_L1 bool isRegistered(std::string_view method) const noexcept;

        /**
         * @brief Checks if a method is registered.
         * @param[in] method Method value.
         * @return `true` if the method is registered.
         * @return `false` if the method is not registered.
         * @details The method value is case-sensitive.
         */
        CRONZ_NODISCARD_L1 bool isRegistered(const Method &method) const noexcept;

        /**
         * @brief Unregisters a method.
         * @param[in] method Method value.
         * @details The method is unregistered if it is already registered. The method value is case-sensitive.
         */
        void unregisterMethod(std::string_view method) noexcept;

        /**
         * @brief Unregisters a method.
         * @param[in] method Method value.
         * @details The method is unregistered if it is already registered. The method value is case-sensitive.
         */
        void unregisterMethod(const Method &method) noexcept;

        /**
         * @brief Unregisters all methods.
         */
        void unregisterAllMethods() noexcept;

        /** @} */

        /**
         * @name Iterators.
         */
        /** @{ */
        /**
         * @brief Iterator type.
         */
        using Iterator = std::vector<Method>::iterator;

        /**
         * @brief Constant iterator type.
         */
        using ConstIterator = std::vector<Method>::const_iterator;

        /**
         * @brief Reverse iterator type.
         */
        using ReverseIterator = std::vector<Method>::reverse_iterator;

        /**
         * @brief Constant reverse iterator type.
         */
        using ConstReverseIterator = std::vector<Method>::const_reverse_iterator;

        /**
                 * @brief Returns an iterator to the first element of the vector.
                 * @return Iterator to the first element.
                 */
        CRONZ_NODISCARD_L1 Iterator begin() noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 Iterator end() noexcept;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstIterator begin() const noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstIterator end() const noexcept;

        /**
         * @brief Returns an iterator to the first element of the vector.
         * @return Iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstIterator cbegin() const noexcept;

        /**
         * @brief Returns an iterator to the element following the last element of the vector.
         * @return Iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstIterator cend() const noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ReverseIterator rbegin() noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ReverseIterator rend() noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator rbegin() const noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator rend() const noexcept;

        /**
         * @brief Returns a reverse iterator to the first element of the vector.
         * @return Reverse iterator to the first element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator crbegin() const noexcept;

        /**
         * @brief Returns a reverse iterator to the element following the last element of the reversed vector.
         * @return Reverse iterator to the element following the last element.
         */
        CRONZ_NODISCARD_L1 ConstReverseIterator crend() const noexcept;

        /** @} */

        /**
         * @name Destructor.
         */
        /** @{ */
        /**
         * @brief Destructor.
         */
        ~MethodRegistry() noexcept = default;

        /** @} */
    };

CRONZ_END_HTTP_NAMESPACE

#include "cronz/http/method/impl/registry.ipp"

#endif // CRONZ_HTTP_METHOD_REGISTRY_HPP
