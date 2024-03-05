#ifndef UIPLUGIN_HPP
#define UIPLUGIN_HPP

#include "../../core/interfaces/iplugin.hpp"
#include <vector>

namespace YatePlugin {
class UiPlugin : public YateCore::IPlugin {
    private:
        static std::vector<UiPlugin*> s_registered;

    public:
        inline static std::vector<UiPlugin*> get_registered_plugins() { return s_registered; }

        UiPlugin(std::string name = "UiPlugin");

        //virtual void render() = 0;
};
}

#endif
