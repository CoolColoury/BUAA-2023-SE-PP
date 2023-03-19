#pragma once
#include <exception>
#include "config.h"

#ifndef _ERROR
#define _ERROR

class unexpected_argument : public std::exception
{
    const char* what() const { return "Unexpected Argument:"; }
};

class missing_file : public std::exception
{
    const char* what() const { return "Missing File: input file cannot open"; }
};

class can_not_output : public std::exception
{
    const char* what() const { return "Can Not Output: solution.txt"; }
};

class ring_check_exception : public std::exception
{
    const char* what() const { return "Ring Check Exception: there is a loop in words"; }
};

void check_conflicted_argument(char origin);
void check_conflicted_argument(bool origin);
void check_config_valid(const Config& config);
void check_filename(char* filename);
void check_bound(int index, int max, const char* arg);
void check_is_single_alpha(const char* arg);
void check_unexcepted_argument(const char* arg);

void check_too_much_result(long long len);
void check_ring_exception();

#endif // !_ERROR