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

#include <gtest/gtest.h>

#include <tuple>
#include <vector>

// Authority, User Information, User, Password, Host, Port
const std::tuple<std::string, std::string, std::string, std::string> authorityDatum = {

};

TEST(URL, AuthorityUser) {
    Cronz::URL::UserInformation userInformation;
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
