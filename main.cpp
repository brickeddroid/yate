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

using DocumentHandler = Core::DocumentHandler;
using IUiPlugin = Core::Api::IUiPlugin;
using IWrapper = Core::Api::IWrapper;
using JsonWrapper = Wrapper::JsonWrapper;
using WebUi = Plugin::WebUi;
using FileIOFactory = Plugin::FileIOFactory;


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
    Utils::LogLevel = Log_t::SILLY;

    log(Log_t::INFO, DOMAIN, "Welcome to YATE\n");

    FileIOFactory factory;
    DocumentHandler document_handler(factory);
    JsonWrapper json_wrapper;
    WebUi webui_plugin("0.0.0.0", 8082);

    IWrapper* wrapper = &json_wrapper;
    IUiPlugin* uiplugin = &webui_plugin;
    // Connection between components through observer registration

    // DocumentHandler => IWrapper
    document_handler.register_observer("file_opened", &IWrapper::onFileOpened, wrapper);
    document_handler.register_observer("open_file_list_change", &IWrapper::onOpenFileListChange, wrapper);

    // IWrapper => DocumentHandler
    json_wrapper.register_observer("cmd_open_file", &DocumentHandler::onOpenFileCommand, &document_handler);
    json_wrapper.register_observer("cmd_close_file", &DocumentHandler::onCloseFileCommand, &document_handler);
    json_wrapper.register_observer("cmd_document_change", &DocumentHandler::onDocumentChangeCommand, &document_handler);


    // IUiPlugin => IWrapper
    webui_plugin.register_observer("cmd_request", &IWrapper::onCommandRequest, wrapper);

    // IWrapper => IUiPlugin
    json_wrapper.register_observer("file_opened", &IUiPlugin::onCoreUpdateMessage, uiplugin);
    json_wrapper.register_observer("open_file_list_change", &IUiPlugin::onCoreUpdateMessage, uiplugin);


    try {
        webui_plugin.start();
    } catch(std::runtime_error& e) {
        log(Log_t::ERROR, "%s\n", e.what());
        throw;
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
