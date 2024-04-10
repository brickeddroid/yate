#ifndef LOCALFILEIO_HPP
#define LOCALFILEIO_HPP
#include <ifileiofactory.hpp>
#include <document.hpp>

namespace Yate::Plugin {

class LocalFileReader : public Core::Api::IFileReader {
public:
    LocalFileReader() : Core::Api::IFileReader() {}
    //virtual ~LocalFileReader() = default;
    virtual Core::Document read(const std::string& filepath);
};

} // end namespace Yate::Plugin


#endif
