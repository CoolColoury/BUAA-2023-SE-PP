#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "error.h"

#ifndef _OUTPUT
#define _OUTPUT

inline void stream_write_line_no_flush(std::ostream& f,std::string const& line);
inline void write_to_solution_txt(std::vector<std::string> ans);

#endif // !_OUTPUT
