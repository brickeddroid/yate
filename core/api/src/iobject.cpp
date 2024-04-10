#include "../icore.hpp"
#include "../../../utils/log.hpp"

using namespace YateUtils;

namespace YateCore {
ICore::ICore(std::string name)
    : m_name(name)
{
    log(Log_t::INFO, "%s created\n", name.c_str());
}

}
