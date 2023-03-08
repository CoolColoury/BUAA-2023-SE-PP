#pragma once
#include <exception>

#ifndef _ERROR
#define ERROR

class conflicted_argument : public std::exception
{
    const char* what() const { return "Confilicted Argument:"; }
};

class unexpected_argument : public std::exception
{
    const char* what() const { return "Unexpected Argument:"; }
};

class missing_argument : public std::exception
{
    const char* what() const { return "Missing Argument:"; }
};

class invalid_argument : public std::exception
{
    const char* what() const { return "Invalid Argument:"; }
};

class invalid_file : public std::exception
{
    const char* what() const { return "Invalid File:"; }
};

class missing_file : public std::exception
{
    const char* what() const { return "Missing File:"; }
};

class can_not_output : public std::exception
{
    const char* what() const { return "Can Not Output:"; }
};

void check_conflicted_argument(char origin)
{
    if (origin != 0)
    {
        throw new conflicted_argument();
    }
}

void check_conflicted_arguemnt(bool origin)
{
    if (origin)
    {
        throw new conflicted_argument();
    }
}

void check_config_valid(const Config& config)
{
    if (config.type == 'n')
    {
        if (config.head || config.tail || config.n_head || config.enable_loop)
        {
            throw new conflicted_argument();
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
    throw new invalid_file();
}

void check_bound(int index, int max)
{
    if (index >= max)
    {
        throw new missing_argument();
    }
}

void check_is_single_alpha(const char* arg)
{
    if (strlen(arg) != 1 || !isalpha(arg[0]))
    {
        throw new invalid_argument();
    }
}

void check_head_or_tail_args(char& origin, const char* arg)
{
    check_conflicted_arguemnt(origin);
    check_is_single_alpha(arg);
    origin = arg[0];
}

void check_unexcepted_argument()
{
    throw new unexpected_argument();
}

#endif