#ifndef JSONWRAPPER_HPP
#define JSONWRAPPER_HPP
#include <iwrapper.hpp>

namespace Yate::Wrapper {
class JsonWrapper : public Core::Api::IWrapper {
protected:

    virtual Core::Api::CommandEventMessage cmd_from_string(const std::string& msg) override;

    virtual std::string document_to_string(const Core::Document& document) override;
    virtual std::string doc_list_to_string(const std::map<std::string, Core::Document>& document) override;
    virtual std::string doc_change_to_string(const Core::DocumentChange& doc_change) override;
public:
    JsonWrapper();
    /*
    virtual void onOpenFileListChange(const Utils::Event & event) override;
    virtual void onFileOpened(const Utils::Event & event) override;
    virtual void onDocumentChange(const Utils::Event&) override;

    virtual void onCommandRequest(const Utils::Event& event) override;
/*
    virtual std::string wrap_document_content(const std::string& content) override;
    virtual std::string wrap_document_history(const std::vector<Core::DocumentChange>& history) override;
    virtual std::string wrap_open_document_list(const std::map<std::string, Core::Document>& document_list) override;
*/
    //virtual std::string process_incoming_message(const std::string& msg) override;

};

} // end namespace Yate::Wrapper

#endif
