#ifndef FILEIOFACTORY_HPP
#define FILEIOFACTORY_HPP

#include <ifileiofactory.hpp>

namespace Yate::Plugin {

class FileIOFactory : public Core::Api::IFileIOFactory {
    public:
        FileIOFactory() = default;
        //virtual ~FileIOFactory() = default;

        virtual std::unique_ptr<Core::Api::FileReader> create_reader(const std::string& type) const override;
        virtual std::unique_ptr<Core::Api::FileWriter> create_writer(const std::string& type) const override;
};

} // end namespace Yate::Plugin

#endif
