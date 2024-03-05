#include <string>
#include <iostream>
#include <fstream>
#include <exception>

#include "core/documenthandler.hpp"
#include "plugins/document/documentfactory.hpp"
#include "plugins/ui/web/webui.hpp"
#include "utils/log.hpp"
#include "wrapper/json/jsonwrapper.hpp"

#include <sys/poll.h>
#include <termios.h>

using namespace YateUtils;

void set_term_quiet_input(){
    struct termios tc;
    tcgetattr(0, &tc);
    tc.c_lflag &= ~(ICANON | ECHO);
    tc.c_cc[VMIN] = 0;
    tc.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tc);
}
int main(int argc, char* argv[]){
    log(Log_t::INFO, "Welcome to YATE\n");
    YateDocument::DocumentFactory doc_factory;
    YateCore::DocumentHandler docHandle(&doc_factory);
    YatePlugin::WebUi ui_server("0.0.0.0", 8082);

    // Json wrapper needed for web frontend
    YateWrapper::JsonWrapper json_wrapper;
    json_wrapper.set_document_handler(&docHandle);
    ui_server.register_wrapper(&json_wrapper);


    try{
        ui_server.start();
    } catch(std::exception& e) {
        log(Log_t::ERROR, "%s\n", e.what());
    }

    if(argv[1]){
        log(Log_t::DEBUG, "%s\n", "Open file");
        std::string filename = argv[1];
        docHandle.open(filename);
        YateCore::IDocument* doc = docHandle.get_current_doc();
        if(doc){
            for(auto s : doc->get_lines()){
                log(Log_t::SILLY, "%s\n", s.c_str());
            }
        }

        //openFile(filename);
        log(Log_t::DEBUG, "%s\n", "File opened...");
        //std::cout << "File opened.." << std::endl;
    }

    struct pollfd pfd = { .fd = 0, .events = POLLIN };
    set_term_quiet_input();
    while(true){
        // Main loop
        if (poll(&pfd, 1, 0)>0) {
            int in = getchar();
            if(in == 8 || in == 127){
            } else if (in=='\n' || in == ' '){
            } else {
            }
        }
        usleep(100);
    }
	return 0;
}
