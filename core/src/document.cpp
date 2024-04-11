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

void Document::update_history(){
    const std::lock_guard<std::mutex> lock(m_doc_mutex);
    int count = 0;
    auto change = m_change_queue.pop();
    while(change){
        m_change_history.emplace_back(*change);
        change = m_change_queue.pop();
        ++count;
        // TODO
    }

    if(count > 0){
        emit_event("history_change");
    }
}

void Document::set_content(const std::string& content) {
    const std::lock_guard<std::mutex> lock(m_doc_mutex);
    log(Log_t::DEBUG, DOMAIN, "Move content to %s and notify observers.\n", name().c_str());
    m_content = std::move(content);
    emit_event("content_change");
    log(Log_t::DEBUG, DOMAIN, "Content moved to %s and observers are notified.\n", name().c_str());
}

} // end namespace Yate::Core
