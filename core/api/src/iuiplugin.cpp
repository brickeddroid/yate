#include "../iuiplugin.hpp"
#include "../../../utils/log.hpp"

using namespace Yate::Utils;

namespace Yate::Core::Api {

const std::string DOMAIN = "YCAPI::IUIP";

IUiPlugin::IUiPlugin(const std::string& name)
    : IObject(name),
      m_running(false),
      m_status(Status::STOPPED)
{}

void IUiPlugin::start(){
    if(m_status != Status::STOPPED){
        return;
    }
    log(Log_t::INFO, DOMAIN, "Starting %s\n", name().c_str());
    set_status(Status::STARTING);
    m_thread = std::thread(&IUiPlugin::start_plugin, this);
    set_status(Status::RUNNING);
    log(Log_t::INFO, DOMAIN, "%s started\n", name().c_str());
}

void IUiPlugin::stop(){
    stop_plugin();
    m_thread.join();
    set_status(Status::STOPPED);
}

void IUiPlugin::onCoreUpdateMessage(const Utils::Event& event) {
    log(Log_t::INFO, DOMAIN, "onCoreUpdateMessage Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            auto msg = std::any_cast<const std::string&>(arguments[0]);
            log(Log_t::VERBOSE, DOMAIN, "Event %s data casted.\n", event.name.c_str());
            notify_frontend(event.name, msg);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s", e.what());
        }
    }
    log(Log_t::DEBUG, DOMAIN, "Event %s emitted.\n", event.name.c_str());
}

void IUiPlugin::set_status(Status status) {
    m_status = status;
}

} // end namespace Yate::Core::Api
