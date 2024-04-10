#ifndef FILEIOFACTORY_HPP
#define FILEIOFACTORY_HPP

#include <ifileiofactory.hpp>

namespace Yate::Plugin {

class FileIOFactory : public Core::Api::IFileIOFactory {
    public:
        FileIOFactory();
        //virtual ~FileIOFactory() = default;

        //virtual Core::Api::IFileReader get_reader(const std::string& name) override;
        //virtual Core::Api::IFileWriter get_writer(const std::string& name) override;
};

} // end namespace Yate::Plugin

#endif
