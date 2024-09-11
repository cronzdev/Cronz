/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#include <cronz/crypto/base64.hpp>

#include <gtest/gtest.h>

TEST(Crypto, Base64) {
    // String to be encoded, Base64 encoded string, Base64 encoded string (padded)
    // https://datatracker.ietf.org/doc/html/rfc4648#section-10
    const std::vector<std::tuple<std::string, std::string, std::string>> Cases = {
            {"", "", ""},
            {"f", "Zg", "Zg=="},
            {"fo", "Zm8", "Zm8="},
            {"foo", "Zm9v", "Zm9v"},
            {"foob", "Zm9vYg", "Zm9vYg=="},
            {"fooba", "Zm9vYmE", "Zm9vYmE="},
            {"foobar", "Zm9vYmFy", "Zm9vYmFy"}
    };

    for (const auto &Case : Cases) {
        const std::string &str = std::get<0>(Case);
        const std::string &encoded = std::get<1>(Case);
        const std::string &encodedPadded = std::get<2>(Case);

        std::string b64encoded;
        EXPECT_EQ(encoded.length(), Cronz::Crypto::CalculateBase64EncodedLength<false>(str.length()));
        EXPECT_TRUE(Cronz::Crypto::Base64Encode<false>(str, b64encoded, Cronz::Crypto::Base64Alphabet));
        EXPECT_EQ(encoded, b64encoded);

        std::string b64encodedPadded;
        EXPECT_EQ(encodedPadded.length(), Cronz::Crypto::CalculateBase64EncodedLength<true>(str.length()));
        EXPECT_TRUE(Cronz::Crypto::Base64Encode<true>(str, b64encodedPadded, Cronz::Crypto::Base64Alphabet));
        EXPECT_EQ(encodedPadded, b64encodedPadded);

        std::string b64decoded;
        EXPECT_TRUE(Cronz::Crypto::Base64Decode<std::string>(encoded, b64decoded, Cronz::Crypto::Base64AlphabetIndicesMap));
        EXPECT_EQ(str, b64decoded);

        std::string b64decodedPadded;
        EXPECT_TRUE(Cronz::Crypto::Base64Decode<std::string>(encodedPadded, b64decodedPadded, Cronz::Crypto::Base64AlphabetIndicesMap));
        EXPECT_EQ(str, b64decodedPadded);
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
