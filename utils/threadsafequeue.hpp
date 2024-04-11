#ifndef YTHREADSAFEQUEUE_HPP
#define YTHREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <optional>

/*
 * Source: https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/comment-page-1/
 *
 * Cite:
 * This is a more general approach to API design that holds, loosely:
 *      “Make interfaces easy to use right, and hard to use wrong”
 * (originally attributed to Martin Fowler)
 */

namespace Yate::Utils {

// Naive approach to create a threadsafe layer for std::queue
template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> m_queue;
    mutable std::mutex m_lock;

    bool empty(){
        std::lock_guard<std::mutex> lock(m_lock);
        return m_queue.empty();
    }

public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete ;
    ThreadSafeQueue& operator=(const ThreadSafeQueue<T> &) = delete ;

    ThreadSafeQueue(ThreadSafeQueue<T>&& other) {
        std::lock_guard<std::mutex> lock(m_lock);
        m_queue = std::move(other.m_queue);
    }

    virtual ~ThreadSafeQueue() { }

    unsigned long size(){
        std::lock_guard<std::mutex> lock(m_lock);
        return m_queue.size();
    }

    std::optional<T> pop(){
        std::lock_guard<std::mutex> lock(m_lock);
        if(m_queue.empty()) return {};
        T tmp = m_queue.front();
        m_queue.pop();
        return tmp;
    }

    void push(const T& item){
        std::lock_guard<std::mutex> lock(m_lock);
        m_queue.push(item);
    }
};

} // end namespace Yate::Utils

#endif
