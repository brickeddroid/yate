#ifndef IFILEIOFACTORY_HPP
#define IFILEIOFACTORY_HPP

#include <fileio.hpp>
#include <string>
#include <map>

namespace Yate::Core::Api {

class IFileIOFactory {
private:
    //std::map<std::string, std::shared_ptr<IFileReader>> m_readers;
    //std::map<std::string, std::shared_ptr<IFileWriter>> m_writers;
protected:
public:
    //IFileIOFactory();
    virtual ~IFileIOFactory() = default;

    virtual std::unique_ptr<FileReader> create_reader(const std::string& type) const = 0;
    virtual std::unique_ptr<FileWriter> create_writer(const std::string& type) const = 0;

    //std::shared_ptr<IFileReader> const get_reader(const std::string& name);
    //std::shared_ptr<IFileWriter> get_writer(const std::string& name);
};

} // end namespace Yate::Core::Api

#endif
