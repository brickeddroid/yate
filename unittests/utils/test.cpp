#include <gtest/gtest.h>
#include <log.hpp>
#include <threadsafequeue.hpp>

TEST(UtilsTest, LogAssertion){
    // Log_t::NONE prints message without prefix (timestamp, domain, level)
    int result = Yate::Utils::log(Yate::Utils::Log_t::NONE, "DOMAIN", "Hello %s", "World");

    EXPECT_EQ(strlen("Hello World"), result);
}

TEST(UtilsTest, QueueAssertions) {
    Yate::Utils::ThreadSafeQueue<int> q;
    q.push(5);
    q.push(9);

    EXPECT_EQ(5, q.pop().value_or(-1));
    EXPECT_EQ(9, q.pop().value_or(-1));
    EXPECT_EQ(-1, q.pop().value_or(-1));
}
