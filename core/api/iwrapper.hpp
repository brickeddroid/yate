#ifndef IWRAPPER_HPP
#define IWRAPPER_HPP

#include "iobject.hpp"
#include "iuiplugin.hpp"
#include "../documenthandler.hpp"
#include "../document.hpp"

namespace Yate::Core::Api {
class IWrapper : public IObject {
protected:
    DocumentHandler& m_document_handler;
public:
    IWrapper(DocumentHandler& document_handler,
             IUiPlugin& uiplugin,
             const std::string& name = "WrapperObject"
    );
    IWrapper() = default;
    virtual ~IWrapper() = default;

    // Event callbacks for DocumentHandler events
    virtual void onOpenFileListChange(const Utils::Event&) = 0;
    virtual void onFileOpened(const Utils::Event&) = 0;
    virtual void onDocumentChange(const Utils::Event&) = 0;

    // Event callbacks for UiPlugin events
    virtual void onCommandRequest(const Utils::Event& event) = 0;
/*
    virtual std::string wrap_document_content(const std::string& content) = 0;
    virtual std::string wrap_document_history(const std::vector<DocumentChange>& history) = 0;

    virtual std::string wrap_open_document_list(const std::map<std::string, Document>& document_list) = 0;
*/
    //virtual std::string process_incoming_message(const std::string& msg) = 0;
    //virtual void update_document(const std::string& input, Document& document) = 0;
};

} // end namespace Yate::Core::Api

#endif
