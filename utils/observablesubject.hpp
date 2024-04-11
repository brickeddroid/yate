#ifndef OBSERVABLESUBJECT_HPP
#define OBSERVABLESUBJECT_HPP

#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <map>
#include <list>
#include <future>
#include <mutex>
#include <any>
#include <exception>

#include "log.hpp"

namespace Yate::Utils {

class Event {
public:
    std::string name;
    std::vector<std::any> arguments;

    template<typename... Args>
    Event(const std::string& name_, Args&&... args) : name(name_) {
        arguments.reserve(sizeof...(Args));
        (arguments.emplace_back(std::any(args)), ...);
    }
};

class ObservableSubject {
public:
    using ObserverFunction = std::function<void(const Event&)>;

    template<typename ObjectType>
    void register_observer(const std::string& eventName, void (ObjectType::*memberFunction)(const Event&), ObjectType* object) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_observers[eventName].emplace_back(std::bind(memberFunction, object, std::placeholders::_1));
    }

    template<typename... Args>
    void emit_event(const std::string& eventName, Args&&... args) {
        Event event(eventName, std::forward<Args>(args)...);
        notify_observers(eventName, event);
    }

private:
    std::vector<std::future<void>> m_notifications_in_execution;

    std::map<std::string, std::list<ObserverFunction>> m_observers;
    std::mutex m_mutex;

    void clear_notifications();
    void notify_observers(const std::string& eventName, const Event& event);
};

} // end namespace Yate::Utils
#endif
