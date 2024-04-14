#ifndef IFILEIOFACTORY_HPP
#define IFILEIOFACTORY_HPP

#include <ifileio.hpp>
#include <string>
#include <map>

namespace Yate::Core::Api {

class IFileIOFactory {
private:
    std::map<std::string, std::shared_ptr<IFileReader>> m_readers;
    std::map<std::string, std::shared_ptr<IFileWriter>> m_writers;
protected:
    void add_reader(const std::string& name, std::shared_ptr<IFileReader> reader);
    void add_writer(const std::string& name, std::shared_ptr<IFileWriter> writer);
public:
    IFileIOFactory();
    virtual ~IFileIOFactory() = default;

    std::shared_ptr<IFileReader> const get_reader(const std::string& name);
    std::shared_ptr<IFileWriter> get_writer(const std::string& name);
};

} // end namespace Yate::Core::Api

#endif
