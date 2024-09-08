/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#include <cronz/url.hpp>

#include <cronz.hpp>

#include <gtest/gtest.h>

#include <vector>

TEST(URL, Scheme) {
    // Schemes, Canonical, Validity
    const std::vector<std::tuple<std::vector<std::string>, std::string, bool>> schemes = {
            {{"http", "HTTP", "Http", "hTtp", "htTp", "httP"}, "http", true},
            {{" https", "https://"}, "", false},
            {{"FTP"}, "ftp", true},
            {{"file"}, "file", true},
            {{"mailto"}, "mailto", true},
            {{"tel"}, "tel", true},
            {{"UnKnown"}, "unknown", true},
            {{"one+two-three.four"}, "one+two-three.four", true},
            {{"+hello"}, "", false},
            {{""}, "", true}
    };

    Cronz::URL::Scheme scheme;
    for (const auto &entry : schemes) {
        const auto &list = std::get<0>(entry);

        if (std::get<2>(entry)) {
            for (const std::string &s : list) {
                EXPECT_TRUE(scheme.setValue(s));
                EXPECT_EQ(scheme.getValue(), std::get<1>(entry));
            }
        }
        else {
            for (const std::string &s : list) {
                EXPECT_FALSE(scheme.setValue(s));
            }
        }
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
