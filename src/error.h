#pragma once
#include <exception>
#include "config.h"

#ifndef _ERROR
#define _ERROR

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

class ring_check_exception : public std::exception
{
    const char* what() const { return "Ring Check Exception:"; }
};

class too_much_result : public std::exception
{
    const char* what() const { return "Too Much Result:"; }
};

void check_conflicted_argument(char origin);
void check_conflicted_arguemnt(bool origin);
void check_config_valid(const Config& config);
void check_filename(char* filename);
void check_bound(int index, int max);
void check_is_single_alpha(const char* arg);
void check_head_or_tail_args(char& origin, const char* arg);
void check_unexcepted_argument();

void check_too_much_result(size_t len);
void check_ring_exception();

#endif // !_ERROR