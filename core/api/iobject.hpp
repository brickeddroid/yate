#ifndef ICORE_HPP
#define ICORE_HPP

#include <string>

namespace YateCore {
class ICore {
private:
    std::string m_name;
public:
    ICore(std::string name = "ICoreObject");
};

}

#endif
