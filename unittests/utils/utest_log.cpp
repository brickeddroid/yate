#include <gtest/gtest.h>
#include <log.hpp>

TEST(UtilsTest, LogAssertion){
    // Log_t::NONE prints message without prefix (timestamp, domain, level)
    int result = Yate::Utils::log(Yate::Utils::Log_t::NONE, "DOMAIN", "Hello %s", "World");

    EXPECT_TRUE(result >= strlen("Hello World"));
}
