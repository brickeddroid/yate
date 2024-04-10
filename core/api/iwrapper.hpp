#ifndef IWRAPPER_HPP
#define IWRAPPER_HPP

#include "icore.hpp"
#include "../documenthandler.hpp"

namespace YateCore {
class IWrapper : public ICore {
private:
    std::string m_data;

    DocumentHandler* m_document_handler;
protected:
    virtual void wrap_document(IDocument* const doc, std::string& result) = 0;
public:
    IWrapper(const std::string& name = "WrapperObject");

    void set_document_handler(DocumentHandler* const doc_handler);

    virtual std::string get_updated_data() = 0;
    virtual void update_data(const std::string& data) = 0;

    const std::string& get_document(const std::string& file_path);
};

} // endof namespace YateCore


#endif
