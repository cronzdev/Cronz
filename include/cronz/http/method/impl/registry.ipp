/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2025 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_HTTP_METHOD_IMPL_REGISTRY_IPP
#define CRONZ_HTTP_METHOD_IMPL_REGISTRY_IPP 1

#include "cronz/http/method/registry.hpp"

CRONZ_BEGIN_HTTP_NAMESPACE
    // Properties.
    inline std::size_t MethodRegistry::count() const noexcept {
        return _methods.size();
    }

    // Method registration.
    inline bool MethodRegistry::registerMethod(const std::string_view method) noexcept {
        try {
            const Method m(method);
            return registerMethod(m);
        } catch (...) {
            return false;
        }
    }

    inline bool MethodRegistry::registerMethod(const Method &method) noexcept {
        if (!method.isValid() || isRegistered(method))
            return false;

        try {
            _methods.push_back(method);
        } catch (...) {
            return false;
        }

        return true;
    }

    inline bool MethodRegistry::registerAllPredefinedMethods() noexcept {
        try {
            std::vector<Method> predefinedMethods;
            predefinedMethods.reserve(Method::PredefinedMethods.size());

            for (const Method &m: Method::PredefinedMethods) {
                if (!isRegistered(m))
                    predefinedMethods.push_back(m);
            }

            _methods.insert(_methods.end(), predefinedMethods.cbegin(), predefinedMethods.cend());
        } catch (...) {
            return false;
        }

        return true;
    }

    inline bool MethodRegistry::isRegistered(const std::string_view method) const noexcept {
        return std::ranges::any_of(_methods, [&method](const Method &m) {
            return m.compare(method);
        });
    }

    inline bool MethodRegistry::isRegistered(const Method &method) const noexcept {
        return isRegistered(method.value);
    }

    inline void MethodRegistry::unregisterMethod(const std::string_view method) noexcept {
        if (!Method::IsValid(method))
            return;

        for (auto it = _methods.cbegin(); it != _methods.cend(); ++it) {
            if (it->compare(method)) {
                _methods.erase(it);
                return;
            }
        }
    }

    inline void MethodRegistry::unregisterMethod(const Method &method) noexcept {
        return unregisterMethod(method.value);
    }

    inline void MethodRegistry::unregisterAllMethods() noexcept {
        _methods.clear();
    }

    // Iterators.
    inline MethodRegistry::Iterator MethodRegistry::begin() noexcept {
        return _methods.begin();
    }

    inline MethodRegistry::Iterator MethodRegistry::end() noexcept {
        return _methods.end();
    }

    inline MethodRegistry::ConstIterator MethodRegistry::begin() const noexcept {
        return _methods.cbegin();
    }

    inline MethodRegistry::ConstIterator MethodRegistry::end() const noexcept {
        return _methods.cend();
    }

    inline MethodRegistry::ConstIterator MethodRegistry::cbegin() const noexcept {
        return _methods.cbegin();
    }

    inline MethodRegistry::ConstIterator MethodRegistry::cend() const noexcept {
        return _methods.cend();
    }

    inline MethodRegistry::ReverseIterator MethodRegistry::rbegin() noexcept {
        return _methods.rbegin();
    }

    inline MethodRegistry::ReverseIterator MethodRegistry::rend() noexcept {
        return _methods.rend();
    }

    inline MethodRegistry::ConstReverseIterator MethodRegistry::rbegin() const noexcept {
        return _methods.crbegin();
    }

    inline MethodRegistry::ConstReverseIterator MethodRegistry::rend() const noexcept {
        return _methods.crend();
    }

    inline MethodRegistry::ConstReverseIterator MethodRegistry::crbegin() const noexcept {
        return _methods.crbegin();
    }

    inline MethodRegistry::ConstReverseIterator MethodRegistry::crend() const noexcept {
        return _methods.crend();
    }

CRONZ_END_HTTP_NAMESPACE

#endif // CRONZ_HTTP_METHOD_IMPL_REGISTRY_IPP
