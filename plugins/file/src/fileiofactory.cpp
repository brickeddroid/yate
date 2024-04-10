#include "../fileiofactory.hpp"

#include "../localfileio.hpp"
#include "../../../utils/log.hpp"

namespace Yate::Plugin {

using namespace Utils;

constexpr const char* DOMAIN = "YPLUGIN::FILE";

FileIOFactory::FileIOFactory() : Core::Api::IFileIOFactory()
{
    add_reader("local", std::make_shared<LocalFileReader>());
}

} //end namespace Yate::Plugin
