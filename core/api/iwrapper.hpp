#ifndef IWRAPPER_HPP
#define IWRAPPER_HPP

#include "iobject.hpp"
#include "../document.hpp"

namespace Yate::Core::Api {
struct CommandEventMessage {
    std::string cmd;
    std::string filename;
    std::string filerw;
};

class IWrapper : public IObject {
protected:
    // Plugin >> Wrapper >> Core
    virtual CommandEventMessage cmd_from_string(const std::string& msg) = 0;

    // Core >> Wrapper >> Plugin
    virtual std::string document_to_string(const Document& document) = 0;
    virtual std::string doc_list_to_string(const std::map<std::string, Document>& document) = 0;
    virtual std::string doc_change_to_string(const DocumentChange& doc_change) = 0;

public:
    IWrapper(const std::string& name = "IWrapper");
    virtual ~IWrapper() = default;

    // Event callbacks for DocumentHandler events
    void onOpenFileListChange(const Utils::Event&);
    void onFileOpened(const Utils::Event&);
    void onDocumentChange(const Utils::Event&);

    // Event callbacks for UiPlugin events
    void onCommandRequest(const Utils::Event& event);
};

} // end namespace Yate::Core::Api

#endif
