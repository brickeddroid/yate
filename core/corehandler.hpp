#ifndef COREHANDLER_HPP
#define COREHANDLER_HPP

#include "documenthandler.hpp"
#include "interfaces/iplugin.hpp"

namespace YateCore {
class CoreHandler {
public:
    void register_plugin(IPlugin* plugin);
    void update();

private:
    DocumentHandler m_doc_handle;
    std::vector<IPlugin*> m_plugins;
};

} // endof namespace YateCore


#endif
