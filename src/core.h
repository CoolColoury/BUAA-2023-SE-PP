#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include "config.h"
#include "wordgraph.h"
#include "solver.h"
#include "config.h"

#ifndef _CORE
#define _CORE

int gen_chains_all(const char* words[], int len, char* result[]);
int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop);
int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char n_head, bool enable_loop);

#endif // !_CORE
