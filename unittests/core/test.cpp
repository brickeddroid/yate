#include <gtest/gtest.h>
#include <document.hpp>

TEST(CoreTest, DocumentAssertions) {
    Yate::Core::Document d("hello.txt");
    d.set_content("Hello world");

    EXPECT_STREQ("hello.txt", d.name().c_str());
    EXPECT_STREQ("Hello world", d.content().c_str());
}
