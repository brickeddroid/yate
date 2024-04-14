#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "../utils/threadsafequeue.hpp"
#include "api/iobject.hpp"

#include <vector>
#include <mutex>
#include <string>

namespace Yate::Core {

enum encoding_t {
    ASCII,
    ISO_8859,
    UTF_7,
    UTF_8,
    UTF_16
};

struct DocumentChange {
    enum Operation {
        NOP,
        INSERT,
        DELETE
    };
    unsigned long origin_id;
    unsigned long timestamp;
    Operation operation;
    size_t cursor_position;
    size_t length;
    std::string data;

    DocumentChange();

    bool operator==(const DocumentChange& other){
        return(
            origin_id == other.origin_id
            && timestamp == other.timestamp
            && operation == other.operation
            && cursor_position == other.cursor_position
            && length == other.length
            && data == other.data
            );
    }


    void print();
    /*
    DocumentChange(const DocumentChange& other){
        origin = other.origin;
        timestamp = other.timestamp;
        operation = other.operation;
        cursor_position = other.cursor_position;
        length = other.length;
        data = other.data;

    }
    */
};


class Document : public Api::IObject {
private:
    std::mutex m_doc_mutex;

    std::string m_content;
    encoding_t m_encoding;

    std::vector<DocumentChange> m_change_history;
    Utils::ThreadSafeQueue<DocumentChange> m_change_queue;
public:
    explicit Document(const std::string& filename = "Document");
    Document(const Document& other) :
        m_content(other.m_content),
        m_encoding(other.m_encoding)
    {}

    Document& operator=(Document&& other){
        if(this == &other) {
            return *this;
        }
        if(content() == other.content()){
            return *this;
        }

        m_content = other.m_content;
        m_encoding = other.m_encoding;

        return *this;
    }



    void update_history();
    const std::string& content() const { return m_content; }
    void set_content(const std::string& content);

    const std::vector<DocumentChange>& history() const { return m_change_history; }

    void enqueue_document_change(DocumentChange& change);
};

} // end namespace Yate::Core


template <> struct std::hash<Yate::Core::DocumentChange>
{
    size_t operator()(const Yate::Core::DocumentChange& d){
        return (
            (std::hash<unsigned long>{}(d.origin_id))
            ^ ((std::hash<unsigned long>{}(d.timestamp)) << 1) >> 1
            ^ ((std::hash<Yate::Core::DocumentChange::Operation>{}(d.operation)) << 2) >> 2
            ^ ((std::hash<size_t>{}(d.cursor_position)) << 3) >> 3
            ^ ((std::hash<size_t>{}(d.length)) << 4) >> 4
            ^ ((std::hash<std::string>{}(d.data)) << 5) >> 5
        );
    }
};


#endif
