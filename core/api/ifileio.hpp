#ifndef IFILEIO_HPP
#define IFILEIO_HPP

#include <document.hpp>
#include <string>

namespace Yate::Core::Api {
class IFileReader {
public:
    IFileReader() = default;
    virtual ~IFileReader() = default;
    virtual Document read(const std::string& filepath);
};

class IFileWriter {
public:
    IFileWriter() = default;
    virtual ~IFileWriter() = default;
    virtual void write(const std::string& filepath, const Document& document);
};

} // end namespace Yate::Core::Api
//static_assert( is_trivially_copyable_v<Yate::Core::Api::IFileReader>);

#endif
