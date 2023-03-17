#include "output.h"

void write_to_solution_txt(std::vector<std::string> ans)
{
    std::ofstream fout;
    fout.open("solution.txt");
    if (!fout.is_open())
    {
        throw new missing_file();
    }
    for (const std::string& line: ans)
    {
        fout << line << "\n";
    }
    fout.flush();
    fout.close();
}
