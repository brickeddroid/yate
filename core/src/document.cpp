#include "../document.hpp"
#include "../../utils/log.hpp"

namespace Yate::Core {
using namespace Utils;

constexpr const std::string DOMAIN = "YCORE::DOC";

void DocumentChange::print(){
    const char* op = (operation == Operation::INSERT) ? "INSERT" : "DELETE";
    log(Log_t::DEBUG, DOMAIN, "DocumentChange: %s", op);
}

Document::Document(std::string filename)
    : /*Utils::ObservableSubject<Document>(this),*/
      Api::IObject(filename)
{

}

void Document::enqueue_document_change(DocumentChange& document_change)
{
    //const std::lock_guard<std::mutex> lock(m_doc_mutex);
    m_change_queue.push(std::move(document_change));
}

void Document::update(){
    if(m_change_queue.empty()) return;
    while(!m_change_queue.empty()){
        m_change_history.emplace_back(m_change_queue.pop().value_or(DocumentChange()));
    }
    //publish("history");
    emit_event("history_change");
}

void Document::set_content(const std::string& content) {
    log(Log_t::DEBUG, DOMAIN, "Move content to %s and notify observers.\n", name().c_str());
    m_content = std::move(content);
    emit_event("content_change");
    log(Log_t::DEBUG, DOMAIN, "Content moved to %s and observers are notified.\n", name().c_str());
}

} // end namespace Yate::Core
