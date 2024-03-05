#ifndef IDOCUMENT_HPP
#define IDOCUMENT_HPP

#include "icore.hpp"
//#include "../token.hpp"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdint>

namespace YateCore {
class IDocument : public ICore {
public:
    enum KeywordType {
        PRIMARY   = (1 << 0),
        SECONDARY = (1 << 1),
        TERTIARY  = (1 << 2),
        CUSTOM    = (1 << 3)
    };
    IDocument(std::string filepath);

    inline const std::string& get_path() { return m_filepath; }
    const std::string& get_raw();
    const std::string& get_line(uint32_t indx);
    const std::vector<std::string>& get_lines();
    const std::vector<std::string>& get_lines(uint32_t start_indx);
    const std::vector<std::string>& get_lines(uint32_t start_indx, uint32_t end_indx);
    const std::vector<std::string>& get_keywords_table(KeywordType ktype);

    void read_file();

    void write(std::string doc);

    void write_line(std::string line, int rowIndx = -1);

    void write_char(char c, int rowIndx, int colIndx);

    void save();

    virtual void init_keywords();
protected:
    void add_keyword(const std::string& keyword, KeywordType ktype);


private:
    std::string m_filepath;
    std::string m_project;

    std::string m_content;
    std::vector<std::string> m_content_lines;

    std::map<KeywordType, std::vector<std::string>> m_keywords;
    /*
    std::vector<std::string> m_keywords_primary;
    std::vector<std::string> m_keywords_secondary;
    std::vector<std::string> m_keywords_tertiary;
    std::vector<std::string> m_keywords_custom;
    */
    //ComplexCharacterContainer m_root_container;
};

} // end namespace YateCore

#endif
