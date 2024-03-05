#include "../iplugin.hpp"

namespace YateCore{

IPlugin::IPlugin(std::string name)
    : ICore(name)
{}

void IPlugin::set_status(STATUS status) {
    m_status = status;
}
void IPlugin::register_wrapper(IWrapper* const wrapper) {
    m_wrapper = wrapper;
}

} // end namespace YateCore
