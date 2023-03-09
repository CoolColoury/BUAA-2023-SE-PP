#include "core.h"
#include "wordgraph.h"
#include "solver.h"
#include "config.h"
#include <sstream>
#include <cstring>
#include <string>

int gen_chains_all(const char* words[], int len, char* result[])
{
    std::vector<std::string> vector_words(words, words + len);
    WordGraph g(vector_words);
    Config config;
    config.type = 'n';

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);
    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        strcpy_s(result[i], length, vector_result[i].c_str());
    }
    return int(vector_result.size());
}

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop)
{
    std::vector<std::string> vector_words(words, words + len);
    WordGraph g(vector_words);
    Config config = { head, tail, n_head, 'c', enable_loop };

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);

    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        strcpy_s(result[i], length, vector_result[i].c_str()); // TODO£º²»·ûºÏ¹æ·¶£¿£¿£¿£¿£¿
    }
    return int(vector_result.size());
}

int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop)
{
    std::vector<std::string> vector_words(words, words + len);
    WordGraph g(vector_words);
    Config config = { head, tail, n_head, 'c', enable_loop };

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);

    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        strcpy_s(result[i], length, vector_result[i].c_str());
    }
    return int(vector_result.size());
}
