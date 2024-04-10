#ifndef YQUEUE_HPP
#define YQUEUE_HPP

#include <queue>
#include <mutex>
#include <optional>

namespace Yate::Utils {

// Naive approach to create a threadsafe layer for std::queue
template <typename T>
class Queue {
private:
    std::queue<T> m_queue;
    mutable std::mutex m_lock;

public:
    Queue() = default;
    virtual ~Queue() = default;

    bool empty(){
        std::lock_guard<std::mutex> lock(m_lock);
        return m_queue.empty();
    }

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
