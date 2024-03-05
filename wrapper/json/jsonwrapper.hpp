#ifndef JSONWRAPPER_HPP
#define JSONWRAPPER_HPP
#include "../../core/interfaces/iwrapper.hpp"

namespace YateWrapper {
class JsonWrapper : public YateCore::IWrapper {
public:
    virtual std::string get_updated_data();
    virtual void update_data(const std::string& json_data);

    virtual void wrap_document(YateCore::IDocument* const doc, std::string& result);
};

}

#endif
