#include "../observablesubject.hpp"

#include <future>

namespace Yate::Utils {

void ObservableSubject::clear_notifications() {
    log(Log_t::DEBUG, "SUBJECT", "Clear notifications\n");
    std::vector<std::future<void>>::iterator it = m_notifications_in_execution.begin();
    int count = 0;
    while (it != m_notifications_in_execution.end()) {
        auto status = (*it).wait_for(std::chrono::milliseconds(0));
        if (status == std::future_status::ready) {
            it = m_notifications_in_execution.erase(it);
            ++count;
        }
        else {
            log(Log_t::DEBUG, "SUBJECT", "Executor not ready yet\n");
            ++it;
        }
    }
    log(Log_t::DEBUG, "SUBJECT", "Cleared %d notifications\n", count);
}

void ObservableSubject::notify_observers(const std::string& eventName, const Event& event) {
    std::lock_guard<std::mutex> lock(m_mutex);
    int count = 0;
    log(Log_t::DEBUG, "SUBJECT", "Notify observers of event '%s' \n", eventName.c_str());
    try {
    auto it = m_observers.find(eventName);
    if (it != m_observers.end()) {
        for (auto& observer : it->second) {
            m_notifications_in_execution.emplace_back(std::async(std::launch::async, observer, event));
            ++count;
        }
    }
    } catch(std::exception& e) {
        log(Log_t::ERROR, "%s\n", e.what());
    }
    log(Log_t::DEBUG, "SUBJECT", "%d observers of event '%s' notified.\n", count, eventName.c_str());
    clear_notifications();
}

} // end namespace Yate::Utils
