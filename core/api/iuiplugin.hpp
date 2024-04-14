#ifndef IPLUGIN_HPP
#define IPLUGIN_HPP

#include "iobject.hpp"
#include <cstdint>
#include <thread>



namespace Yate::Core::Api {

class IUiPlugin : public IObject {
public:
    enum Status {
        STARTING,
        RUNNING,
        STOPPED
    };

    void start();
    void stop();

    inline bool is_running() const { return m_status == Status::RUNNING; }

    IUiPlugin(std::string name = "PluginObject");

    void onCoreUpdateMessage(const Utils::Event& event);
protected:
    void set_status(Status status);

    virtual void start_plugin() = 0;
    virtual void stop_plugin() = 0;

    virtual void notify_frontend(const std::string& event, const std::string& msg) = 0;


private:
    std::thread m_thread;

    bool m_running;
    Status m_status;

    std::string m_name;
};

} // end namespace Yate::Core::Api


#endif
