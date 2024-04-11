#include "../iuiplugin.hpp"
#include "../../../utils/log.hpp"

using namespace Yate::Utils;

namespace Yate::Core::Api {

const std::string DOMAIN = "YCOREAPI";

IUiPlugin::IUiPlugin(std::string name)
    : IObject(name),
      m_running(false),
      m_status(Status::STOPPED)
{}

void IUiPlugin::set_status(Status status) {
    m_status = status;
}

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

} // end namespace Yate::Core::Api
