#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <string>
#include "../../utils/observablesubject.hpp"



namespace Yate::Core::Api {

class IObject : public Utils::ObservableSubject {
private:
    std::string m_name;
protected:
    inline void set_name(const std::string& name) { m_name = name; }
public:
    IObject(std::string name = "IObject");
    virtual ~IObject();

    inline const std::string& name() { return m_name; }
};



} // end namespace Yate::Core::Api

#endif
