#include "../cpp_doc.hpp"

namespace YateDocument {

CppDocument::CppDocument(const std::string& filepath)
    : YateCore::IDocument(filepath)
{
}

void CppDocument::init_keywords()
{
    KeywordType ktype = KeywordType::PRIMARY;
    add_keyword("class", ktype);
    add_keyword("struct", ktype);
    add_keyword("if", ktype);
    add_keyword("else", ktype);
    add_keyword("for", ktype);
    add_keyword("while", ktype);

    ktype = KeywordType::SECONDARY;
    add_keyword("int", ktype);
    add_keyword("bool", ktype);
    add_keyword("double", ktype);
    add_keyword("float", ktype);
    add_keyword("char", ktype);
    add_keyword("byte", ktype);

    // ...

}

}
