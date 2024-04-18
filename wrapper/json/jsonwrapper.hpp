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
    virtual ~JsonWrapper() = default;
};

} // end namespace Yate::Wrapper

#endif
