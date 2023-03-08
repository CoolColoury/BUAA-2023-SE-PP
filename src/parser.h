#pragma once

#include <vector>
#include <string>
#include <iostream>

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

    void parse_arg(int argc, char* argv[]);
    void parse_words(const std::istream& input);
    void handle_error(); // TODO

public:
    void parse(int argc, char* argv[]);
    std::vector<std::string>& get_words()
    {
        return m_words;
    }
    Config& get_config()
    {
        return m_config;
    }
};


#endif // _PARSER
