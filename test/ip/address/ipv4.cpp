/*
 * Cronz - https://lib.cronz.dev
 *
 * Copyright (c) 2024 - present. All rights reserved.
 * Tuğrul Güngör - https://tugrulgungor.me
 *
 * Distributed under the MIT License.
 * https://opensource.org/license/mit/
 */

#include <cronz/ip/address.hpp>

#include <gtest/gtest.h>

TEST(IPv4Address, Parsing_and_Stringification) {
    // Representation, bytes, validity
    const std::vector<std::tuple<std::string, std::array<std::uint8_t, static_cast<std::size_t>(4)>, bool>> addresses =
    {
            {"0.0.0.0", {0, 0, 0, 0}, true},
            {"127.0.0.1", {127, 0, 0, 1}, true},
            {"255.255.255.255", {255, 255, 255, 255}, true},
            {"255.255.255", {0, 0, 0, 0}, false},
            {"localhost", {0, 0, 0, 0}, false},
            {"192.168.1.256", {0, 0, 0, 0}, false},
    };

    for (const auto &address : addresses) {
        const auto &addr = std::get<0>(address);
        const auto &bytes = std::get<1>(address);
        const auto &isValid = std::get<2>(address);

        Cronz::IP::IPv4Address ipv4;

        if (isValid) {
            EXPECT_TRUE(ipv4.parse(addr));
            EXPECT_EQ(bytes, ipv4.bytes);
            EXPECT_EQ(addr, ipv4.stringify());
        }
        else {
            EXPECT_FALSE(ipv4.parse(addr));
        }
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
