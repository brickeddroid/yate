#ifndef IPLUGIN_HPP
#define IPLUGIN_HPP

#include "icore.hpp"
#include "iwrapper.hpp"

#include <cstdint>

namespace YateCore {

class IPlugin : public ICore {
public:
    enum STATUS {
        STARTING,
        RUNNING,
        STOPPED
    };
    virtual void start() = 0;
    virtual void stop() = 0;

    inline bool is_running() const { return m_status == STATUS::RUNNING; }

    void register_wrapper(IWrapper* const wrapper);

    IPlugin(std::string name = "PluginObject");
protected:
    IWrapper* m_wrapper;

    void set_status(STATUS status);
private:
    bool m_running;
    STATUS m_status;

    std::string m_name;

};

} // end namespace YateCore


#endif
