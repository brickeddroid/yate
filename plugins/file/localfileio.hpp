#ifndef LOCALFILEIO_HPP
#define LOCALFILEIO_HPP
#include <ifileiofactory.hpp>
#include <document.hpp>

namespace Yate::Plugin {

class LocalFileReader : public Core::Api::FileReader {
public:
    //LocalFileReader() = default;
    LocalFileReader() : Core::Api::FileReader() {}
    //virtual ~LocalFileReader() = default;
    virtual Core::Document read(const std::string& filepath) override;
};

class LocalFileWriter : public Core::Api::FileWriter {
public:
    LocalFileWriter() : Core::Api::FileWriter() {}
    //virtual ~LocalFileReader() = default;
    virtual void write(const std::string& filepath, const Core::Document& document) override;
};

} // end namespace Yate::Plugin


#endif
