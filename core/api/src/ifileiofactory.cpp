#include "../ifileiofactory.hpp"

namespace Yate::Core::Api {

IFileIOFactory::IFileIOFactory(){
    add_reader("default", std::make_shared<IFileReader>());
    add_writer("default", std::make_shared<IFileWriter>());
}
/*
IFileIOFactory::~IFileIOFactory(){
    for()
}
*/
void IFileIOFactory::add_reader(const std::string& name, std::shared_ptr<IFileReader> reader)
{
    //if(m_readers.find(name) != m_readers.end()) delete m_readers[name];
    m_readers[name] = std::move(reader);
}

void IFileIOFactory::add_writer(const std::string& name, std::shared_ptr<IFileWriter> writer)
{
    //if(m_writers.find(name) != m_writers.end()) delete m_writers[name];
    m_writers[name] = std::move(writer);
}

std::shared_ptr<IFileReader> const IFileIOFactory::get_reader(const std::string& name){
    if(m_readers.find(name) == m_readers.end()) return m_readers["default"];
    return m_readers[name];
}

std::shared_ptr<IFileWriter> IFileIOFactory::get_writer(const std::string& name){
    if(m_writers.find(name) == m_writers.end()) return m_writers["default"];
    return m_writers[name];
}

} // end namespace Yate::Core::Api
