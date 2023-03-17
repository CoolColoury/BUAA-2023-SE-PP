#include "core.h"

int gen_chains_all(const char* words[], int len, char* result[])
{
    std::vector<std::string> vector_words(words, words + len);
    Config config;
    config.type = 'n';
    std::vector<std::string> vector_result;
    int total = 0;
    try
    {
        WordGraph g(vector_words, config);
        total = g.get_chains_num();
        Solver solver(g, config);
        solver.solve(vector_result);
    }
    catch (const std::exception& e)
    {
        copy_error_message(e.what());
        throw e;
    }

    for (int i = 0; i < vector_result.size(); i++)
    {
        size_t length = vector_result[i].size() + 1;
        result[i] = (char*)malloc(length);
        if (result[i])
        {
            strcpy_s(result[i], length, vector_result[i].c_str());
        }
    }
    return total;
}

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop)
{
    std::vector<std::string> vector_words(words, words + len);
    Config config = { head, tail, n_head, 'w', enable_loop };
    std::vector<std::string> vector_result;

    try
    {
        WordGraph g(vector_words, config);
        Solver solver(g, config);
        solver.solve(vector_result);
    }
    catch (const std::exception& e)
    {
        copy_error_message(e.what());
        throw e;
    }

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
    std::vector<std::string> vector_result;

    try
    {
        WordGraph g(vector_words, config);
        Solver solver(g, config);
        solver.solve(vector_result);
    }
    catch (const std::exception& e)
    {
        copy_error_message(e.what());
        throw e;
    }

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

extern char* ERROR_MESSAGE = nullptr;

char* get_error_message()
{
    return ERROR_MESSAGE;
}

void copy_error_message(const char* error_message)
{
    if (ERROR_MESSAGE)
    {
        free(ERROR_MESSAGE);
    }
    size_t length = strlen(error_message) + 1;
    ERROR_MESSAGE = (char*)malloc(length);
    if (ERROR_MESSAGE)
    {
        strcpy_s(ERROR_MESSAGE, length, error_message);
    }
}
