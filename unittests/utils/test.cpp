#include <gtest/gtest.h>
#include <threadsafequeue.hpp>

TEST(UtilsTest, QueueAssertions) {
    Yate::Utils::ThreadSafeQueue<int> q;
    q.push(5);
    q.push(9);

    EXPECT_EQ(5, q.pop().value_or(-1));
    EXPECT_EQ(9, q.pop().value_or(-1));
    EXPECT_EQ(-1, q.pop().value_or(-1));
}
