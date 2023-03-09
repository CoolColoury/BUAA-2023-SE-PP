#pragma once

#ifndef _CONFIG
#define _CONFIG

struct Config
{
    char head = 0;
    char tail = 0;
    char n_head = 0;
    char type = 0; // 'n' 'w' 'c'
    bool enable_loop = false;
};

#endif // !_CONFIG

