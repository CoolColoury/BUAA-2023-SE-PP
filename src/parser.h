#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

#ifndef _PARSER

#define _PARSER

class Parser
{
private:
    std::vector<std::string> m_words;
    Config m_config;
    char* m_filename = nullptr;

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
