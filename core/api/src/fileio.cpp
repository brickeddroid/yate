#include "../fileio.hpp"

namespace Yate::Core::Api {

Document FileReader::read(const std::string& filepath) {
    return Document(filepath);
}

void FileWriter::write(const std::string& filepath, const Document& document)
{

}

} // end namespace Yate::Core::Api
