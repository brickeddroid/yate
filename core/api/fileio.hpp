#ifndef IFILEIO_HPP
#define IFILEIO_HPP

#include <document.hpp>
#include <string>

namespace Yate::Core::Api {
class FileReader {
public:
    FileReader() = default;
    virtual ~FileReader() = default;
    virtual Document read(const std::string& filepath);
};

class FileWriter {
public:
    FileWriter() = default;
    virtual ~FileWriter() = default;
    virtual void write(const std::string& filepath, const Document& document);
};

} // end namespace Yate::Core::Api

#endif
