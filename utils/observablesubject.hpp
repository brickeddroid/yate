#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>
#include <functional>

class Observer;

namespace YateUtils {

template <class T>
class Subject {
public:
    typedef std::function<void(T const&)> observer_callback_t;
    void attach_observer(observer_callback_t observer){
        m_observers.emplace_back(std::move(&observer));
    }
    void detach_observer(observer_callback_t observer){
        m_observers.erase(&observer);
    }
protected:
    void notify();

private:
    std::vector<observer_callback_t*> m_observers;
};

} // endof namespace YateUtils

#endif
