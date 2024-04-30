#include <chrono>
#include <exception>

#include "utils/log.hpp"
#include "core/documenthandler.hpp"
#include "plugins/file/fileiofactory.hpp"
#include "plugins/ui/web/webui.hpp"
#include "wrapper/json/jsonwrapper.hpp"

using namespace std::chrono_literals;

using namespace Yate;
using namespace Utils;

using DocumentHandler = Core::DocumentHandler;
using IUiPlugin = Core::Api::IUiPlugin;
using IWrapper = Core::Api::IWrapper;
using JsonWrapper = Wrapper::JsonWrapper;
using WebUi = Plugin::WebUi;
using FileIOFactory = Plugin::FileIOFactory;


const std::string DOMAIN = "YMAIN";

int main(int argc, char* argv[]){
    Utils::LogLevel = Log_t::SILLY;

    log(Log_t::INFO, DOMAIN, "Welcome to YATE\n");

    FileIOFactory factory;
    std::shared_ptr<DocumentHandler> document_handler = std::make_shared<DocumentHandler>(factory);
    std::shared_ptr<IWrapper> json_wrapper = std::make_shared<JsonWrapper>();

    std::vector<std::shared_ptr<IUiPlugin>> ui_plugins {
        std::make_shared<WebUi>("0.0.0.0", 8082),
        std::make_shared<WebUi>("0.0.0.0", 8083)
    };


    // Connection between components through observer registration

    // DocumentHandler => IWrapper
    document_handler->register_observer("file_opened", &IWrapper::onFileOpened, json_wrapper);
    document_handler->register_observer("open_file_list_change", &IWrapper::onOpenFileListChange, json_wrapper);

    // IWrapper => DocumentHandler
    json_wrapper->register_observer("file_cmd_req", &DocumentHandler::onFileCommand, document_handler);
    json_wrapper->register_observer("cmd_document_change", &DocumentHandler::onDocumentChangeCommand, document_handler);


    for(auto& ui_plugin: ui_plugins){
        // IUiPlugin => IWrapper
        ui_plugin->register_observer("file_cmd_request", &IWrapper::onFileCommandRequest, json_wrapper);

        // IWrapper => IUiPlugin
        json_wrapper->register_observer("file_opened", &IUiPlugin::onCoreUpdateMessage, ui_plugin);
        json_wrapper->register_observer("open_file_list_change", &IUiPlugin::onCoreUpdateMessage, ui_plugin);

        try {
            ui_plugin->start_ui_thread();
        } catch(std::runtime_error& e) {
            log(Log_t::ERROR, "%s\n", e.what());
        }
    }

    // Main loop
    while(true){
        document_handler->update();
        std::this_thread::sleep_for(1ms);
    }
	return 0;
}
