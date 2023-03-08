#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#ifndef _PARSER

#define _PARSER

struct Config
{
    char head = 0;
    char tail = 0;
    char n_head = 0;
    char type; // 'n' 'w' 'c'
    bool enable_loop = false;
};

class Parser
{
private:
    std::vector<std::string> m_words;
    Config m_config;
    char* m_filename;

    void parse_arg(int argc, char* argv[]);
    void check_args_error(int argc, char* argv[]);

public:
    void parse(int argc, char* argv[]);
    void parse_words(std::istream& f);

    std::vector<std::string>& get_words()
    {
        return m_words;
    }
    Config& get_config()
    {
        return m_config;
    }
};

// ¶ÁÈëº¯Êý
void stream_read_string_reverse(std::istream& f, std::string& result);


#endif // _PARSER
