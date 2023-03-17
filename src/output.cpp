#include "output.h"

inline void stream_write_line_no_flush(std::ostream& f, std::string const& line)
{
    f << line << "\n";
}

inline void write_to_solution_txt(std::vector<std::string> ans)
{
    std::ofstream fout;
    fout.open("solution.txt");
    if (!fout.is_open())
    {
        throw new missing_file();
    }
    for (const std::string& line: ans)
    {
        stream_write_line_no_flush(fout, line);
    }
    fout.flush();
    fout.close();
}
