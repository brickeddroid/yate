#include "../idocumentfactory.hpp"

#include <fstream>
#include "../../../utils/log.hpp"

using namespace YateUtils;

namespace YateCore {

IDocument* const IDocumentFactory::createDocument(const std::string& filepath)
{
    return new YateCore::IDocument(filepath);
}

} //endof namespace YateCore
