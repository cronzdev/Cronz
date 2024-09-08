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

#include <bit>
#include <string>
#include <tuple>

TEST(IPv6Address, Parsing_and_Stringification_Valid) {
    // Representations, decimal, canonical, stringified
    std::vector<std::tuple<std::vector<std::string>, std::array<std::uint16_t, static_cast<std::size_t>(8)>, std::string
                           , std::string>> addresses = {
            {
                    {"2001:4860:4001:803::1011"}, {8193, 18528, 16385, 2051, 0, 0, 0, 4113},
                    "2001:4860:4001:0803:0000:0000:0000:1011", "2001:4860:4001:803::1011"
            },
            {
                    {"2608::3:5"}, {9736, 0, 0, 0, 0, 0, 3, 5},
                    "2608:0000:0000:0000:0000:0000:0003:0005", "2608::3:5"
            },
            {
                    {"::", "0::0"}, {0, 0, 0, 0, 0, 0, 0, 0},
                    "0000:0000:0000:0000:0000:0000:0000:0000", "::"
            },
            {
                    {"::1", "0:0:0::1"}, {0, 0, 0, 0, 0, 0, 0, 1},
                    "0000:0000:0000:0000:0000:0000:0000:0001", "::1"
            },
            {
                    {"1::"}, {1, 0, 0, 0, 0, 0, 0, 0},
                    "0001:0000:0000:0000:0000:0000:0000:0000", "1::"
            },
            {
                    {"1::1"}, {1, 0, 0, 0, 0, 0, 0, 1},
                    "0001:0000:0000:0000:0000:0000:0000:0001", "1::1"
            },
    };

    for (const auto &address : addresses) {
        const auto &representations = std::get<0>(address);
        const auto &decimal = std::get<1>(address);
        const auto &canonical = std::get<2>(address);
        const auto &minified = std::get<3>(address);

        Cronz::IP::IPv6Address ipv6;
        for (const std::string &representation : representations) {
            EXPECT_TRUE(ipv6.parse(representation));

            if constexpr (std::endian::big == std::endian::native) {
                EXPECT_EQ(ipv6.groups, decimal);
            }
            else if constexpr (std::endian::little == std::endian::native) {
                for (auto i = static_cast<std::size_t>(0); i < ipv6.bytes.size(); i += static_cast<std::size_t>(2))
                    std::swap(ipv6.bytes[i], ipv6.bytes[i + static_cast<std::size_t>(1)]);

                EXPECT_EQ(ipv6.groups, decimal);

                for (auto i = static_cast<std::size_t>(0); i < ipv6.bytes.size(); i += static_cast<std::size_t>(2))
                    std::swap(ipv6.bytes[i], ipv6.bytes[i + static_cast<std::size_t>(1)]);
            }
            else {
                GTEST_FAIL() << "Unsupported endianness";
            }

            EXPECT_EQ(ipv6.length<false>(), canonical.length());
            EXPECT_EQ(ipv6.length<true>(), minified.length());

            EXPECT_EQ(ipv6.stringify<false>(), canonical);
            EXPECT_EQ(ipv6.stringify<true>(), minified);
        }
    }
}

TEST(IPv6Address, Parsing_and_Stringification_Invalid) {
    const std::vector<std::string> representations = {"", ":", "0:1:2:3:"};

    Cronz::IP::IPv6Address ipv6;

    for (const std::string &representation : representations) {
        EXPECT_FALSE(ipv6.parse(representation));
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
