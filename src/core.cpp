#include "core.h"

int gen_chains_all(const char* words[], int len, char* result[])
{
    std::vector<std::string> vector_words(words, words + len);
    Config config;
    config.type = 'n';
    WordGraph g(vector_words, config);

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);
    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        if (result[i])
        {
            strcpy_s(result[i], length, vector_result[i].c_str());
        }
    }
    return g.get_chains_num() + 1;
}

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop)
{
    std::vector<std::string> vector_words(words, words + len);
    Config config = { head, tail, n_head, 'w', enable_loop };
    WordGraph g(vector_words, config);

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);

    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        if (result[i])
        {
            strcpy_s(result[i], length, vector_result[i].c_str());
        }
    }
    return int(vector_result.size());
}

int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop)
{
    std::vector<std::string> vector_words(words, words + len);
    Config config = { head, tail, n_head, 'c', enable_loop };
    WordGraph g(vector_words, config);

    Solver solver(g, config);
    std::vector<std::string> vector_result;
    solver.solve(vector_result);

    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        if (result[i])
        {
            strcpy_s(result[i], length, vector_result[i].c_str());
        }
    }
    return int(vector_result.size());
}
