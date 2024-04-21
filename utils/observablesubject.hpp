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

    bool operator==(const Event& other) const {
        return name == other.name &&
               arguments.size() == other.arguments.size();
    }
};

class Observer {
public:
    virtual ~Observer() = default;
};

class ObservableSubject {
public:
    using ObserverFunction = std::function<void(const Event&)>;
    ObservableSubject() = default;
    virtual ~ObservableSubject() = default;


    template<typename ObjectType>
    void register_observer(const std::string& eventName, void (ObjectType::*memberFunction)(const Event&), std::shared_ptr<ObjectType> object) {
        std::lock_guard<std::mutex> lock(m_mutex);
        Observer* observer = static_cast<Observer*>(object.get());
        if(!observer) {
            log(Log_t::ERROR, eventName, "Could not register callback, observer has to be of type Observer\n");
            return;
        }
        m_observers[eventName].emplace_back(std::make_pair(std::bind(memberFunction, object, std::placeholders::_1), observer));
    }

    template<typename ObjectType>
    void unregister_observer(const std::string& eventName, std::shared_ptr<ObjectType> object) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_observers.find(eventName) == m_observers.end()){
            log(Log_t::ERROR, eventName, "Could not deregister callback, callback not found\n");
            return;
        }
        Observer* observer = static_cast<Observer*>(object.get());
        if(!observer) {
            log(Log_t::ERROR, eventName, "Could not deregister callback, observer has to be of type 'Observer'\n");
            return;
        }

        auto& observers = m_observers[eventName];

        auto it = find_if(
            observers.begin(), observers.end(), [&](const auto& pair){
                return pair.second == object.get();
            }
        );

        if(it != observers.end()){
            observers.erase(it);
        }
    }

protected:
    template<typename... Args>
    void emit_event(const std::string& eventName, Args&&... args) {
        Event event(eventName, std::forward<Args>(args)...);
        notify_observers(eventName, event);
    }

private:
    std::vector<std::future<void>> m_notifications_in_execution;

    std::map<std::string, std::list<std::pair<ObserverFunction, Observer*>>> m_observers;
    std::mutex m_mutex;

    void clear_notifications();
    void notify_observers(const std::string& eventName, const Event& event);
};

} // end namespace Yate::Utils
#endif
