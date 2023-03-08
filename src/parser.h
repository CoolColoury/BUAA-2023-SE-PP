#pragma once

#include <vector>
#include <string>
#include <iostream>

#ifndef _PARSER

#define _PARSER

namespace parser
{
    struct config
    {
        char head = 0;
        char tail = 0;
        char n_head = 0;
        bool enable_loop = false;
    };

    class Parser
    {
    private:
        std::vector<std::string> m_words;
        config m_config;

        void parse_arg(int argc, char* argv[]);
        void parse_words(const std::istream& input);
        void handle_error(); // TODO

    public:
        void parse(int argc, char* argv[]);
    };
}


#endif // _PARSER
