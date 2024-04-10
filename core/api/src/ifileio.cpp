#include "../ifileio.hpp"

namespace Yate::Core::Api {

Document IFileReader::read(const std::string& filepath) {
    return Document(filepath);
}

void IFileWriter::write(const std::string& filepath, const Document& document)
{}

} // end namespace Yate::Core::Api
