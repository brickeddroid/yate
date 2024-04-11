#include "../iwrapper.hpp"

namespace Yate::Core::Api {
IWrapper::IWrapper(DocumentHandler& document_handler, IUiPlugin& uiplugin, const std::string& name)
    : IObject(name),
      m_document_handler(document_handler)
{
    // DocumentHandler registration
    document_handler.register_observer("file_opened", &IWrapper::onFileOpened, this);
    document_handler.register_observer("open_file_list_change", &IWrapper::onOpenFileListChange, this);

    register_observer("cmd_open_file", &DocumentHandler::onOpenFileCommand, &document_handler);
    register_observer("cmd_close_file", &DocumentHandler::onCloseFileCommand, &document_handler);
    register_observer("cmd_document_change", &DocumentHandler::onDocumentChangeCommand, &document_handler);


    // IUiPlugin registration
    uiplugin.register_observer("cmd_request", &IWrapper::onCommandRequest, this);

    register_observer("file_opened", &IUiPlugin::onCoreUpdateMessage, &uiplugin);
    register_observer("open_file_list_change", &IUiPlugin::onCoreUpdateMessage, &uiplugin);
}

} // end namespace Yate::Core::Api
