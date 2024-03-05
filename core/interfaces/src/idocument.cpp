#include "../idocument.hpp"
#include "../../../utils/log.hpp"

#include <fstream>

using namespace YateUtils;

namespace YateCore {

IDocument::IDocument(std::string filepath)
    : ICore("IDocument"),
      m_filepath(filepath)
{
}

const std::string& IDocument::get_raw()
{
    return m_content;
}

const std::string& IDocument::get_line(uint32_t indx)
{
    if(indx > m_content_lines.size()){
        return m_content_lines[0];
    }
    return m_content_lines[indx];
}

const std::vector<std::string>& IDocument::get_lines(){ return m_content_lines; }
const std::vector<std::string>& IDocument::get_lines(uint32_t start_indx){ return get_lines(); }
const std::vector<std::string>& IDocument::get_lines(uint32_t start_indx, uint32_t end_indx){ return get_lines(); }

const std::vector<std::string>& IDocument::get_keywords_table(KeywordType ktype)
{
    return m_keywords[ktype];
}

void IDocument::read_file()
{
    log(Log_t::DEBUG, "Begin reading file %s\n", m_filepath.c_str());
    std::ifstream file_handle(m_filepath, std::ios::in
                                 | std::ios::out
                                 | std::ios::binary
                                 | std::ios::ate);

    //file_handle.open(m_filepath, std::ios::binary | std::ios::in);

    const size_t sz = file_handle.tellg();
    if(sz <= 0){
        // throw error instead...
        log(Log_t::ERROR, "Could not get size %s\n", m_filepath.c_str());
        return;
    }

    m_content = std::string(sz, '\0');
    m_content_lines.clear();


    file_handle.seekg(0, std::ios::beg);
    if(!file_handle.is_open()){
        return;
    }
    file_handle.read(&m_content[0], sz);
    file_handle.seekg(0, std::ios::beg);
    std::string line;
    while(!file_handle.eof()){
        getline(file_handle, line);
        m_content_lines.push_back(line);
    }

    file_handle.close();

    log(Log_t::SILLY, "%s\n", m_content.c_str());

    //m_root_container.add_string(file_data);


/*
    Token* tok = &m_root_token;
    while(true){
        getline(file_handle, str);
        if(file_handle.fail()){
            log(Log_t::ERROR, "%s\n", str.c_str());
            break;
        }
        log(Log_t::SILLY, "%s\n", str.c_str());
    }

    file_handle.close();
*/
}

void IDocument::write(std::string doc){
}

void IDocument::write_line(std::string line, int rowIndx){
    if(rowIndx == -1){
        // indx = last => append at end of file
    }
}

void IDocument::write_char(char c, int rowIndx, int colIndx){

}

void IDocument::save(){

}

void IDocument::init_keywords() // virtual function
{
    // No keywords to register for the default document
}

void IDocument::add_keyword(const std::string& word, KeywordType ktype){
    m_keywords[ktype].push_back(word);
    //for(int i = 0; i < len; i++){
    /*
    int i = 0;
    Token* token = &m_root_token;

    for(auto character : word){
        token = token->add_successor(character);
    }
    /*
    do {
        token = token->add_successor(word[i]);
        //tree.add_node(token);
    } while(word[++i] != '\0');
    */
    /*
    Token::Flags f = { .is_keyword = ktype };
    token->set_flag(f);
    */
}
/*
void IDocument::add_delimiter(const std::string& character)
{

}
*/
} // end namespace YateCore
