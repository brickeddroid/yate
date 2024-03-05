#ifndef CPP_DOC_HPP
#define CPP_DOC_HPP

#include <string>

#include "../../../core/interfaces/idocument.hpp"
namespace YateDocument {
class CppDocument : public YateCore::IDocument {
public:
    CppDocument(const std::string& filepath);
protected:
    virtual void init_keywords();
};

} //endof namespace YateDocument

#endif
