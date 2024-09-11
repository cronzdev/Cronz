/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#ifndef CRONZ_CRYPTO_BASE64_HPP
#define CRONZ_CRYPTO_BASE64_HPP 1

/**
 * @defgroup cronz_crypto_base64 Base64
 * @ingroup cronz_crypto
 * @remark Follows the instructions from [RC4648](https://datatracker.ietf.org/doc/html/rfc4648).
 */

#include "cronz/crypto/types.hpp"

#include <array>
#include <concepts>
#include <string>
#include <vector>

CRONZ_BEGIN_MODULE_NAMESPACE(Crypto)
    /**
     * @name Generic.
     */
    /** @{ */
    /**
     * @ingroup cronz_crypto_base64
     * @brief Base64 alphabet type.
     * @typedef std::array<char, static_cast<std::size_t>(64)> Base64AlphabetType
     */
    typedef std::array<char, static_cast<std::size_t>(64)> Base64AlphabetType;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Base64 indices map type.
     * @typedef std::array<char, static_cast<std::size_t>(256)> Base64IndicesMapType
     */
    typedef std::array<char, static_cast<std::size_t>(256)> Base64IndicesMapType;

    /**
     * @brief Generates a `Base64IndicesMapType` from a `Base64AlphabetType`.
     * @param[in] alphabet Instance of `Base64AlphabetType`.
     * @return Instance of `Base64IndicesMapType`.
     */
    inline constexpr Base64IndicesMapType GenerateBase64IndicesMap(const Base64AlphabetType &alphabet) noexcept {
        Base64IndicesMapType b64map;

        b64map.fill('\0');

        char index = 0;
        for (const char &character : alphabet)
            b64map[static_cast<unsigned char>(character)] = index++;

        return b64map;
    }

    /**
     * @ingroup cronz_crypto_base64
     * @brief Default Base64 alphabet.
     * @see [Base 64 Encoding](https://datatracker.ietf.org/doc/html/rfc4648#section-4).
     */
    inline static constexpr Base64AlphabetType Base64Alphabet = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
            'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
    };

    /**
     * @ingroup cronz_crypto_base64
     * @brief Default Base64 indices map.
     */
    inline static constexpr Base64IndicesMapType Base64AlphabetIndicesMap = GenerateBase64IndicesMap(Base64Alphabet);

    /**
     * @ingroup cronz_crypto_base64
     * @brief URL and filename safe Base64 alphabet.
     * @see [Base 64 Encoding with URL and Filename Safe Alphabet](https://datatracker.ietf.org/doc/html/rfc4648#section-5).
     */
    inline static constexpr Base64AlphabetType Base64AlphabetSafe = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
            'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
    };

    /**
     * @ingroup cronz_crypto_base64
     * @brief URL and filename safe Base64 indices map.
     */
    inline static constexpr Base64IndicesMapType Base64AlphabetSafeIndicesMap = GenerateBase64IndicesMap(
            Base64AlphabetSafe);

    /**
     * @ingroup cronz_crypto_base64
     * @brief Character to be used for padding Base64 encoded strings.
     */
    inline static constexpr char Base64PaddingCharacter = '=';

    /**
     * @brief Tells if the character exists in the alphabet.
     * @param[in] character Character to be found.
     * @param[in] alphabet Alphabet to be searched.
     * @return `true` if the character exists in the alphabet, otherwise, `false`.
     */
    CRONZ_NODISCARD_L1 bool IsInBase64Alphabet(const char &character, const Base64AlphabetType &alphabet) noexcept;

    /**
     * @brief Tells if the character exists in the indices map.
     * @param[in] character Character to be found.
     * @param[in] alphabet Indices map to be searched.
     * @return `true` if the character exists in the indices map, otherwise, `false`.
     */
    CRONZ_NODISCARD_L1 bool IsInBase64AlphabetIndicesMap(const char &character,
                                                         const Base64IndicesMapType &alphabet) noexcept;

    /** @} */

    /**
     * @name Encoding.
     */
    /** @{ */
    /**
     * @ingroup cronz_crypto_base64
     * @brief Tells the required length for an encoded Base64 string.
     * @tparam Padded Should the length calculated for a padded version.
     * @param[in] length Length of the string to be encoded.
     * @return Required length for an encoded Base64 string.
     */
    template <bool Padded = true>
    CRONZ_NODISCARD_L2 std::size_t CalculateBase64EncodedLength(const std::size_t &length) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Tells the required length for an encoded Base64 string.
     * @param[in] length Length of the string to be encoded.
     * @param[in] padded Should the length calculated for a padded version.
     * @return Required length for an encoded Base64 string.
     */
    CRONZ_NODISCARD_L2 std::size_t CalculateBase64EncodedLength(const std::size_t &length, const bool &padded) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @tparam Padded Whether the encoded string should be padded.
     * @param[in] data Data to be encoded.
     * @param[in] length Byte length of `data`.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return Encoded Base64 string. Upon failure, the returned string will be empty.
     */
    template <bool Padded = true>
    CRONZ_NODISCARD_L2 std::string Base64Encode(const void *data, const std::size_t &length,
                                                const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @param[in] data Data to be encoded.
     * @param[in] length Byte length of `data`.
     * @param[in] padded Whether the encoded string should be padded.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return Encoded Base64 string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L2 std::string Base64Encode(const void *data, const std::size_t &length, const bool &padded,
                                                const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @tparam Padded Whether the encoded string should be padded.
     * @param[in] str String to be encoded.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return Encoded Base64 string. Upon failure, the returned string will be empty.
     */
    template <bool Padded = true>
    CRONZ_NODISCARD_L2 std::string Base64Encode(const std::string &str,
                                                const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @param[in] str String to be encoded.
     * @param[in] padded Whether the encoded string should be padded.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return Encoded Base64 string. Upon failure, the returned string will be empty.
     */
    CRONZ_NODISCARD_L2 std::string Base64Encode(const std::string &str, const bool &padded,
                                                const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @tparam Padded Whether the encoded string should be padded.
     * @param[in] data Data to be encoded.
     * @param[in] length Byte length of `data`.
     * @param[out] encoded Encoded Base64 string.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return `true` if successfully encoded, otherwise, `false`.
     */
    template <bool Padded = true>
    CRONZ_NODISCARD_L2 bool Base64Encode(const void *data, const std::size_t &length, std::string &encoded,
                                         const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @param[in] data Data to be encoded.
     * @param[in] length Byte length of `data`.
     * @param[out] encoded Encoded Base64 string.
     * @param[in] padded Whether the encoded string should be padded.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return `true` if successfully encoded, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Base64Encode(const void *data, const std::size_t &length, std::string &encoded,
                                         const bool &padded,
                                         const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @tparam Padded Whether the encoded string should be padded.
     * @param[in] str String to be encoded.
     * @param[out] encoded Encoded Base64 string.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return `true` if successfully encoded, otherwise, `false`.
     */
    template <bool Padded = true>
    CRONZ_NODISCARD_L2 bool Base64Encode(const std::string &str, std::string &encoded,
                                         const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Encodes a string.
     * @param[in] str String to be encoded.
     * @param[out] encoded Encoded Base64 string.
     * @param[in] padded Whether the encoded string should be padded.
     * @param[in] alphabet Alphabet to be used. By default, `Base64Alphabet` is used, but customized alphabets can also
     * be used.
     * @return `true` if successfully encoded, otherwise, `false`.
     */
    CRONZ_NODISCARD_L2 bool Base64Encode(const std::string &str, std::string &encoded, const bool &padded,
                                         const Base64AlphabetType &alphabet = Base64Alphabet) noexcept;

    /** @} */

    /**
     * @name Decoding.
     */
    /** @{ */
    /**
     * @ingroup cronz_crypto_base64
     * @brief Limits the return type of decoding functions.
     * The return type must be one of the following:
     *  - `std::string`
     *  - `std::vector<char>`
     *  - `std::vector<unsigned char>`
     */
    template <typename ReturnType>
    concept Base64DecodeReturnTypeRequirement = requires {
        std::is_same_v<std::string, ReturnType> || std::is_same_v<std::vector<char>, ReturnType> || std::is_same_v<
            std::vector<unsigned char>, ReturnType>;
    };

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[in] alphabet Alphabet to be used.
     * @return Decoded data. Upon failure this will be empty.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L1 ReturnType Base64Decode(const char *encoded,
                                               const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap)
        noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[in] length Length of `encoded`.
     * @param[in] alphabet Alphabet to be used.
     * @return Decoded data. Upon failure this will be empty.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L1 ReturnType Base64Decode(const char *encoded, const std::size_t &length,
                                               const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap)
        noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[in] alphabet Alphabet to be used.
     * @return Decoded data. Upon failure this will be empty.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L1 ReturnType Base64Decode(const std::string &encoded,
                                               const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap)
        noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[out] decoded Decoded data.
     * @param[in] alphabet Alphabet to be used.
     * @return `true` if successfully decoded, otherwise, `false`.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L2 bool Base64Decode(const char *encoded, ReturnType &decoded,
                                         const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[in] length Length of `encoded`.
     * @param[out] decoded Decoded data.
     * @param[in] alphabet Alphabet to be used.
     * @return `true` if successfully decoded, otherwise, `false`.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L2 bool Base64Decode(const char *encoded, const std::size_t &length, ReturnType &decoded,
                                         const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap) noexcept;

    /**
     * @ingroup cronz_crypto_base64
     * @brief Decodes a Base64 encoded string.
     * @tparam ReturnType Output data type.
     * @param[in] encoded Base64 encoded string.
     * @param[out] decoded Decoded data.
     * @param[in] alphabet Alphabet to be used.
     * @return `true` if successfully decoded, otherwise, `false`.
     */
    template <typename ReturnType = std::string>
        requires Base64DecodeReturnTypeRequirement<ReturnType>
    CRONZ_NODISCARD_L2 bool Base64Decode(const std::string &encoded, ReturnType &decoded,
                                         const Base64IndicesMapType &alphabet = Base64AlphabetIndicesMap) noexcept;

    /** @} */

CRONZ_END_MODULE_NAMESPACE

#include "cronz/crypto/impl/base64.ipp"

#endif // CRONZ_CRYPTO_BASE64_HPP
