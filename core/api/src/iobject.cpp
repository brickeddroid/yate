#include "../iobject.hpp"
#include "../../../utils/log.hpp"

using namespace Yate::Utils;

namespace Yate::Core::Api {
const std::string DOMAIN = "YCOREAPI";
IObject::IObject(const std::string& name)
    : m_name(std::move(name))
{
    log(Log_t::VERBOSE, DOMAIN, "%s::IObject created\n", m_name.c_str());
}
IObject::~IObject(){
    log(Log_t::VERBOSE, DOMAIN, "%s::IObject destroyed\n", m_name.c_str());
}

} // end namespace Yate::Core::Api
