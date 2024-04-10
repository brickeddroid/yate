/*
#include <string>
#include <iostream>
#include <fstream>
*/
#include <thread>
#include <chrono>

#include <exception>
#include "utils/log.hpp"
#include "core/documenthandler.hpp"
//#include "plugins/document/documentfactory.hpp"
#include "plugins/file/fileiofactory.hpp"
#include "plugins/ui/web/webui.hpp"
#include "wrapper/json/jsonwrapper.hpp"
/*
#include <sys/poll.h>
#include <termios.h>
*/
using namespace Yate;
using namespace Utils;

const std::string DOMAIN = "YMAIN";
/*
void set_term_quiet_input(){
    struct termios tc;
    tcgetattr(0, &tc);
    tc.c_lflag &= ~(ICANON | ECHO);
    tc.c_cc[VMIN] = 0;
    tc.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tc);
}
*/
int main(int argc, char* argv[]){
    Utils::LogLevel = Log_t::INFO;

    log(Log_t::INFO, DOMAIN, "Welcome to YATE\n");
    Plugin::FileIOFactory factory;
    Core::DocumentHandler document_handler(factory);
    Plugin::WebUi webui_plugin("0.0.0.0", 8082);

    // Make connection between core and outer ui plugin
    Wrapper::JsonWrapper json_wrapper(document_handler, webui_plugin);
    //webui_plugin.register_wrapper(&json_wrapper);


    try {
        webui_plugin.start();
    } catch(std::exception& e) {
        log(Log_t::ERROR, "%s\n", e.what());
    }
/*
    if(argv[1]){
        log(Log_t::DEBUG, DOMAIN, "Open file\n");
        std::string filename = argv[1];
        document_handle.open(filename);
        Yate::Core::IDocument* document = document_handle.get_current_document();
        if(document){
            for(auto s : document->get_lines()){
                log(Log_t::SILLY, DOMAIN, "%s\n", s.c_str());
            }
        }
        log(Log_t::DEBUG, DOMAIN, "File opened\n");
    }
*/
    //set_term_quiet_input();
    using namespace std::chrono_literals;
    while(true){
        // Main loop
        std::this_thread::sleep_for(1ms);
    }
	return 0;
}
