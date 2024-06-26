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

    IUiPlugin(const std::string& name = "PluginObject");
    virtual ~IUiPlugin() = default;

    void start_ui_thread();
    void stop_ui_thread();

    inline bool is_running() const { return m_status == Status::RUNNING; }


    void onCoreUpdateMessage(const Utils::Event& event);
protected:
    void set_status(Status status);

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void notify_frontend(const std::string& event, const std::string& msg) = 0;


private:
    std::thread m_thread;
    Status m_status;
};

} // end namespace Yate::Core::Api


#endif
