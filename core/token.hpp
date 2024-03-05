#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <vector>
#include <map>
#include <list>
#include <cstdint>
#include <string>

#include <ostream>
#include <iostream>

namespace YateCore {


/*
struct Flags {
   uint16_t is_keyword:1;
   uint16_t start_of_token:1;
   uint16_t end_of_token:1;
};
union UFlags {
   Flags f;
   uint16_t unified;
};
*/

/*
void add_keyword(YateCore::Token* token, const char* word){
    //for(int i = 0; i < len; i++){
    int i = 0;
    do {
        token = token->add_successor(word[i]);
        tree.add_node(token);
    } while(word[++i] != '\0');
    YateCore::Token::Flags f = { .is_keyword = 1 };
    token->set_flag(f);
}
*/

class Token {
public:
    enum Flag {
        IS_KEYWORD = 1,
        START_OF_TOKEN = 2,
        END_OF_TOKEN = 4
    };
    union Flags {
        struct {
            std::uint16_t start_of_token:1;
            std::uint16_t end_of_token:1;
            std::uint16_t is_primary_keyword:1;
            std::uint16_t is_secondary_keyword:1;
            std::uint16_t is_tertiary_keyword:1;
            std::uint16_t is_custom_keyword:1;
        };
        struct {
            std::uint16_t is_token:2;
            std::uint16_t is_keyword:4;
        };
        uint16_t fields;
    };

    Token(Token* predecessor = nullptr);

    Token* predecessor();

    std::string getChar();
    void set_flag(Flags f);
    void reset_flag(Flags f);
    bool is_flag_set(Flags f);
    bool search(const char *c);

    Token* add_successor(char c);
    Token* add_successor(std::string character);

    void remove_successor(std::string character);

    void print(int level);
private:
    Token* m_predecessor;
    std::string m_char;
    Flags m_flags;

    bool m_is_keyword;
    bool m_start_of_token;
    bool m_end_of_token;
    int m_count;
    std::vector<int> m_indices_appearance;
    std::map<std::string, Token*> m_successors;
};

struct CharToken {
    Token* token;
    Token* predecessor;
    Token* successor;

    CharToken* previous;
    CharToken* next;

    CharToken(Token* tok);
};

template <class T>
struct Node{
    Node* previous;
    Node* next;

    T data;

    Node(T dat);
};

template <class T>
struct LinkedList {
private:
    Node<T>* m_head;
    Node<T>* m_tail;

public:
    LinkedList();

    Node<T>* add_node(T t);
    Node<T>* head();
    Node<T>* tail();

    void print();
};

class CharTokenTree {
private:
    std::map<std::string, LinkedList<Token*>> m_tree;
public:
    //void add_successor(CharToken* current, CharToken* successor);
    void add_node(Token* token);
    void remove_node(Token* token);

    void print();
};


struct ComplexCharacterToken{
    enum Flag {
        START_OF_TOKEN    = (1 << 0),
        END_OF_TOKEN      = (1 << 1),
        PRIMARY_KEYWORD   = (1 << 2),
        SECONDARY_KEYWORD = (1 << 3),
        TERTIARY_KEYWORD  = (1 << 4),
        CUSTOM_KEYWORD    = (1 << 5),
        DELIMITER         = (0b0011 << 0),
        KEYWORD           = (0b1111 << 2)
    };
    union Flags {
        struct {
            std::uint16_t start_of_token:1;
            std::uint16_t end_of_token:1;
            std::uint16_t primary_keyword:1;
            std::uint16_t secondary_keyword:1;
            std::uint16_t tertiary_keyword:1;
            std::uint16_t custom_keyword:1;
        };
        struct {
            std::uint16_t delimiter:2;
            std::uint16_t keyword:4;
        };
        uint16_t fields;
    };

    std::vector<uint64_t> appearances;

    ComplexCharacterToken* predecessor;
    std::map<std::string, ComplexCharacterToken*> successor_dictionary;

    ComplexCharacterToken* prev_of_same;
    ComplexCharacterToken* next_of_same;

    ComplexCharacterToken* previous;
    ComplexCharacterToken* next;

    Flags flags;
    uint16_t count;
    std::string character;

    ComplexCharacterToken(std::string character, ComplexCharacterToken* _predecessor = nullptr);

    void set_flag(Flags f);
    void reset_flag(Flags f);
    bool is_flag_set(Flags f);
    ComplexCharacterToken* add_successor(const std::string& character);
};

struct ComplexCharacterContainer : public ComplexCharacterToken {
private:
    ComplexCharacterToken* m_head;
    ComplexCharacterToken* m_tail;

    std::map<std::string, ComplexCharacterToken*> same_type_dictionary;
    std::vector<ComplexCharacterToken*> m_characters;

public:
    ComplexCharacterContainer();

    void add_string(const std::string& str);
    ComplexCharacterToken* add_node(const std::string& character);
    ComplexCharacterToken* head();
    ComplexCharacterToken* tail();

    bool is_new_token(const std::string& character);
    bool is_delimiter(char c);
    void print();
};


template <class T>
struct ComplexNode {
    T data;

};

class TokenHandler {

};
} // endof namespace YateCore

#endif
