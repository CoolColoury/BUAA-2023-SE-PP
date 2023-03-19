#include "error.h"
#include <cstring>
#include <cctype>
#include <stdexcept>
#include <string>

void check_conflicted_argument(char origin)
{
    if (origin != 0)
    {
        throw std::logic_error(std::string("Conflicted Argument: -") + origin);
    }
}

void check_conflicted_argument(bool origin)
{
    if (origin)
    {
        throw std::logic_error(std::string("Conflicted Argument: -r"));
    }
}

void check_config_valid(const Config& config)
{
    if (config.type == 0)
    {
        throw std::logic_error("Missing Argument: no valid argument");
    }
    if (config.type == 'n')
    {
        if (config.head || config.tail || config.n_head || config.enable_loop)
        {
            throw std::logic_error("Conflicted Argument: -n");
        }
    }
}

void check_filename(char* filename)
{
    const char* extension = ".txt";
    size_t filename_len = strlen(filename);
    size_t extension_len = strlen(extension);
    if (filename_len >= extension_len)
    {
        if (strcmp(filename + filename_len - extension_len, extension) == 0)
        {
            return;
        }
    }
    throw std::logic_error(std::string("Invalid File: you need end with .txt"));
}

void check_bound(int index, int max, const char* arg)
{
    if (index >= max)
    {
        throw std::logic_error("Missing Argument: you need give an argument after " + std::string(arg));
    }
}

void check_is_single_alpha(const char* arg)
{
    if (strlen(arg) != 1 || !isalpha(arg[0]))
    {
        throw std::invalid_argument("Invalid Argument: please give a single alpha instead of " + std::string(arg));
    }
}

void check_unexcepted_argument(const char* arg)
{
    throw std::logic_error("Unexpected Argument: " + std::string(arg));
}

void check_ring_exception()
{
    throw ring_check_exception();
}

void check_too_much_result(long long len)
{
    if (len > 20000)
    {
        throw std::logic_error("Too Much Result: " + std::to_string(len));
    }
}