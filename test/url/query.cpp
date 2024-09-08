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

TEST(URL, QueryField) {
    Cronz::URL::QueryField<true> field;

    const std::string e1 = "";
    EXPECT_EQ(field.value(), e1);
    EXPECT_FALSE(field.isArray());

    const std::string e2 = ",hello";
    EXPECT_TRUE(field.addValue("hello"));
    EXPECT_EQ(field.value(), e2);
    EXPECT_TRUE(field.isArray());

    EXPECT_TRUE(field.removeValueAt(0));
    EXPECT_FALSE(field.isArray());

    const std::string e3 = "hello,world";
    EXPECT_TRUE(field.addValue("world"));
    EXPECT_EQ(field.value(), e3);
    EXPECT_TRUE(field.isArray());

    const std::string e4 = "hello,world,third";
    EXPECT_TRUE(field.addValue("third"));
    EXPECT_EQ(field.value(), e4);
    EXPECT_TRUE(field.isArray());

    const std::string e5 = "hello,world,third,last";
    EXPECT_TRUE(field.addValue("last"));
    EXPECT_EQ(field.value(), e5);
    EXPECT_TRUE(field.isArray());

    const std::string e6 = "world,third,last";
    EXPECT_TRUE(field.removeValueAt(0));
    EXPECT_EQ(field.value(), e6);
    EXPECT_TRUE(field.isArray());

    const std::string e7 = "world,last";
    EXPECT_TRUE(field.removeValueAt(1));
    EXPECT_EQ(field.value(), e7);
    EXPECT_TRUE(field.isArray());

    EXPECT_FALSE(field.removeValueAt(3));
    EXPECT_EQ(field.value(), e7);
    EXPECT_TRUE(field.isArray());

    field.clearValues();
    EXPECT_EQ(field.value(), e1);
    EXPECT_FALSE(field.isArray());

    const std::string a = "a";
    const std::string b = "b";
    const std::string c = "c";
    const std::string d = "d";
    EXPECT_TRUE(field.addValue(a));
    EXPECT_TRUE(field.addValue(b));
    EXPECT_TRUE(field.addValue(c));
    EXPECT_TRUE(field.addValue(d));
    EXPECT_TRUE(field.isArray());

    std::string v;
    EXPECT_TRUE(field.getValueAt(1, v));
    EXPECT_EQ(a, v);
    EXPECT_TRUE(field.getValueAt(2, v));
    EXPECT_EQ(b, v);
    EXPECT_TRUE(field.getValueAt(3, v));
    EXPECT_EQ(c, v);
    EXPECT_TRUE(field.getValueAt(4, v));
    EXPECT_EQ(d, v);

    const std::string e = "e";
    EXPECT_TRUE(field.setValueAt(0, e));
    EXPECT_TRUE(field.getValueAt(0, v));
    EXPECT_EQ(e, v);

    const std::string e9 = "hello";
    EXPECT_TRUE(field.setValue("hello"));
    EXPECT_EQ(field.value(), e9);
    EXPECT_FALSE(field.isArray());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
