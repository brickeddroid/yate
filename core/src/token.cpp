#include "../token.hpp"

#include "../../utils/log.hpp"

using namespace YateUtils;

namespace YateCore {

Token::Token(Token* predecessor)
    : m_predecessor(predecessor)
{}

Token* Token::predecessor(){
    return m_predecessor;
}

std::string Token::getChar(){
    return m_char;
}

void Token::set_flag(Flags f) {
    m_flags.fields |= f.fields;
}

void Token::reset_flag(Flags f) {
    m_flags.fields &= ~f.fields;
}

bool Token::is_flag_set(Flags f) {
    return ((m_flags.fields & f.fields) == f.fields);
}

bool Token::search(const char *c){

    log(Log_t::DEBUG, "Searching '%s' CC: '%s'\n", c, m_char.c_str());
    std::string character = " ";
    character[0] = c[0];
    if(m_successors.find(character) != m_successors.end()){
        if(c[1] != 0){
            return m_successors[character]->search(c+1);
        }
        return true;
    } else {
        for(auto successor : m_successors){
            log(Log_t::DEBUG, "%s\n", successor.first.c_str());
            auto tc = successor.second->m_successors.find(character);
            if(tc != m_successors.end()){
                return (*tc).second->search(c+1);
            } else {
                return successor.second->search(c);
            }
        }
        return false;
    }
}

Token* Token::add_successor(char c){
    std::string character = " ";
    character[0] = c;
    return add_successor(character);
    /*
    if(!m_children[character]){
        m_children[character] = new Token(this);
    }
    m_children[character]->m_count++;
    if(m_children[character]->m_is_keyword){
        log(Log_t::INFO, "%s %s\n", "[INFO]", "Keyword detected");
    }
    return m_children[character];
    */
}

Token* Token::add_successor(std::string character){
    if(!m_successors[character]){
        m_successors[character] = new Token(this);
        m_successors[character]->m_char = character;
    }
    m_successors[character]->m_count++;
    if(m_successors[character]->m_flags.is_keyword){
        log(Log_t::INFO, "%s\n", "Keyword detected");
    }
    return m_successors[character];
}

void Token::remove_successor(std::string character){
    if(m_successors.find(character) == m_successors.end()){ return; }
    log(Log_t::INFO, "Delete %s\n", character.c_str());
    --m_successors[character]->m_count;
    if(m_successors[character]->m_count == 0){
        m_successors.insert(m_successors[character]->m_successors.begin(), m_successors[character]->m_successors.end());
        delete m_successors[character];
        m_successors[character] = nullptr;
        m_successors.erase(character);
    }
}

void Token::print(int level){
    std::string lvl = std::string(level, '\t');
    //char lvl[level] = {'\t'};
    for(auto successor : m_successors){
        log(Log_t::INFO, "%s %s%s %d %d\n", "[TREE]", lvl.c_str(), successor.first.c_str(), successor.second->m_count, successor.second->m_flags.is_keyword);
        successor.second->print(level+1);
    }
}


template <class T>
Node<T>::Node(T dat)
    : previous(nullptr),
      next(nullptr),
      data(dat)
{}

template <class T>
LinkedList<T>::LinkedList()
    : m_head(nullptr),
      m_tail(nullptr)
{}

template <class T>
Node<T>* LinkedList<T>::add_node(T t){

    log(Log_t::INFO, "%s Node added\n", "[CCTREE]");
    Node<T>* node = new Node(t);
    if(m_head == nullptr){
        m_head = node;
        m_tail = node;
    } else {
        m_tail->next = node;
        m_tail = node;
    }
    return node;
}

template <class T>
Node<T>* LinkedList<T>::head(){
    return m_head;
}

template <class T>
Node<T>* LinkedList<T>::tail(){
    return m_head;
}

template <class T>
void LinkedList<T>::print(){
    Node<T>* current = m_head;
    log(Log_t::INFO, "%s PRINT\n", "[CCTREE]");
    while(current != nullptr){
        log(Log_t::INFO, "%s %d\n", "[CCTREE]", current->data);
        current = current->next;
    }
}
template class LinkedList<Token*>;
template class LinkedList<int>;

CharToken::CharToken(Token* tok)
    : token(tok)
{
    predecessor = tok->predecessor();
    successor = nullptr;
}
/*
void CharTokenTree::add_successor(CharToken* current, CharToken* successor){
    current->successor = successor;
    successor->predecessor = current;
}
*/
void CharTokenTree::add_node(Token* token)
{
    LinkedList list = m_tree[token->getChar()];
    list.add_node(token);
    //CharToken *prev = nullptr;
    /*
    if(tok){
        while(tok){
            prev = tok;
            tok = tok->next;
        }
    }
    tok = new CharToken(token);
    tok->previous = prev;
    tok->next = nullptr;
    */
}

void CharTokenTree::remove_node(Token* token){
    if(m_tree.find(token->getChar()) == m_tree.end()){
        log(Log_t::INFO, "%s Not found: '%s'\n", "[CTOK_TREE]", token->getChar().c_str());
        return;
    }
    LinkedList ct = m_tree[token->getChar()];
    ct.print();
    /*
    while(ct){
        if(ct->token == token){
            break;
        }
    }
    if(ct == nullptr){
        log(Log_t::ERROR, "%s Token not found: '%s'\n", "[ERROR][CTOK_TREE]", token->getChar().c_str());
        return;
    }

    if(ct->previous){
        ct->previous->next = ct->next;
    }
    if(ct->next){
        ct->next->previous = ct->previous;
    }
    delete ct;
    ct = nullptr;
    */
}

void CharTokenTree::print(){

    log(Log_t::INFO, "%s", "[CTOK_TREE]\n");
    for(auto element : m_tree){
        log(Log_t::INFO, "%s\n", element.first.c_str());
        Node<Token*>* node = element.second.head();
        bool element_found = false;
        while(node != nullptr){
            log(Log_t::INFO, "'%s'\n, ", node->data->getChar().c_str());
            node = node->next;
            element_found = true;
        }
        if(!element_found){
            log(Log_t::INFO, "Empty\n");
        }
        /*
        log(Log_t::INFO, "%s '%s': \n", "[CTOK_TREE]", tok->token->getChar().c_str());
        while(tok){
            if(tok->predecessor){
                log(Log_t::INFO, "'%s', ", tok->predecessor->token->getChar().c_str());
            }
            tok = tok->next;
        }
        */
    }
}


ComplexCharacterToken::ComplexCharacterToken(std::string _character, ComplexCharacterToken* _predecessor)
    : predecessor(_predecessor),
      prev_of_same(nullptr),
      next_of_same(nullptr),
      previous(nullptr),
      next(nullptr),
      character(_character)
{}


void ComplexCharacterToken::set_flag(Flags f) {
    flags.fields |= f.fields;
}

void ComplexCharacterToken::reset_flag(Flags f) {
    flags.fields &= ~f.fields;
}

bool ComplexCharacterToken::is_flag_set(Flags f) {
    return ((flags.fields & f.fields) == f.fields);
}

ComplexCharacterToken* ComplexCharacterToken::add_successor(const std::string& character)
{
    if(!successor_dictionary[character]){
        successor_dictionary[character] = new ComplexCharacterToken(this);
        successor_dictionary[character]->character = character;
    }
    successor_dictionary[character]->count++;
    if(successor_dictionary[character]->flags.is_keyword){
        log(Log_t::INFO, "%s\n", "Keyword detected");
    }

    this->next->previous = this;
    this->next = successor_dictionary[character];

    return successor_dictionary[character];
}

ComplexCharacterContainer::ComplexCharacterContainer()
    : ComplexCharacterToken()
      m_head(nullptr),
      m_tail(nullptr)
{}

void ComplexCharacterContainer::add_string(const std::string& str)
{
    ComplexCharacterToken* token = this;
    uint64_t indx = 0;
    for(char& c: str){
        bool is_delimit = is_delimiter(c);
        if(is_delimit){
            ComplexCharacterToken::Flags f = { .end_of_token = 1 };
            token->set_flag(f);
            token = this;
        }
        if(token->successor_dictionary.find(c) == token->successor_dictionary.end()){
            token->successor_dictionary[c] = new ComplexCharacterToken(c, token);
            if(is_delimit)
            {
                ComplexCharacterToken::Flags f = { .delimiter = 3 };
                token->successor_dictionary[c]->set_flag(f);
            }
            if(same_type_dictionary.find(c) == same_type_dictionary.end())
            {
                same_type_dictionary[c] = token->successor_dictionary[c];
            }
        }
        token = token->successor_dictionary[c];
        token->appearances.push_back(indx);

        m_characters.push_back(token);

        ComplexCharacterToken* current = same_type_dictionary[c];
        while(current->next_of_same != nullptr){
           current = current->next_of_same;
        }
        current->next_of_same = token;
        token->prev_of_same = current;
        ++indx;
    }
}

ComplexCharacterToken* ComplexCharacterContainer::add_node(std::string character){
    ComplexCharacterToken* tmp_token = new ComplexCharacterToken(character);
    m_current_token->next = tmp_token;
    tmp_token->previous = m_current_token;
    ComplexCharacterToken::Flags f = { .end_of_token = 1 };
    if(is_new_token(character))
    {
        m_current_dictionary_token.set_flag(f);
        m_current_dictionary_token = &m_root_token;
    }
    m_current_dictionary_token = m_current_dictionary_token->add_successor(tmp_token);
    f.fields = 0;
    f.start_of_token = 1;
    m_current_dictionary_token->set_flag(f);
    ComplexCharacterToken* dic_tok = same_type_dictionary[character];
    while(dic_tok->next_of_same != nullptr){
        dic_tok = dic_tok->next_of_same;
    }
    dic_tok->next_of_same = tmp_token;
    tmp_tok->prev_of_same = dic_tok;

    if(!same_type_dictionary[character]){
        same_type_dictionary[character] = tmp_token;
    } else {
        ComplexCharacterToken* dic_tok = same_type_dictionary[character];

    }

    /*
    if(m_head == nullptr){
        m_head = tmp_token;
        m_tail = tmp_token;
    } else {
        m_tail->next = tmp_token;
        m_tail = tmp_token;
    }*/
    log(Log_t::INFO, "%s Node added: '%s'\n", "[CCTREE]", character.c_str());
    return tmp_token;
}

ComplexCharacterToken* ComplexCharacterContainer::head(){
    return m_head;
}

ComplexCharacterToken* ComplexCharacterContainer::tail(){
    return m_head;
}

bool ComplexCharacterContainer::is_new_token(const std::string& character){
    //m_root_token
    //if()
    return false;
}

bool ComplexCharacterContainer::is_delimiter(char c)
{
    return (c == ' ' || c == '\n' || c == '\r' || c == ';' || c == '{' || c == '}' || c == '(' || c == ')' || c == '"');
}

void ComplexCharacterContainer::print(){
    ComplexCharacterToken* current = m_head;
    log(Log_t::INFO, "%s PRINT\n", "[CCTREE]");
    while(current != nullptr){
        log(Log_t::INFO, "%s %d\n", "[CCTREE]", current->data);
        current = current->next;
    }
}
//template class ComplexContainer<Token*>;
//template class ComplexContainer<int>;

} // end namespace YateCore
