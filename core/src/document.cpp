#include "../document.hpp"
#include "../../utils/log.hpp"

namespace Yate::Core {
using namespace Utils;

constexpr const std::string DOMAIN = "YCORE::DOC";

DocumentChange::DocumentChange()
    :
    origin_id(0),
    timestamp(0),
    operation(Operation::NOP),
    cursor_position(0),
    length(0),
    data()
{

}

void DocumentChange::print(){
    const char* op = (operation == Operation::INSERT) ? "INSERT" : "DELETE";
    log(Log_t::DEBUG, DOMAIN, "DocumentChange: %u %u %s %u %u %s", origin_id, timestamp, op, cursor_position, length, data.c_str());
}

Document::Document(const std::string& filename)
    : Api::IObject(filename),
      m_encoding(encoding_t::ASCII)
{

}

void Document::enqueue_document_change(DocumentChange& document_change)
{
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
        log(Log_t::VERBOSE, DOMAIN, "Update history content of %s and notify observers.\n", name().c_str());
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
