#include "output.h"

void write_to_solution_txt(std::vector<std::string> ans, char type)
{
    std::ofstream fout;
    fout.open("solution.txt");
    if (!fout.is_open())
    {
        throw can_not_output();
    }
    if (type == 'n')
    {
        fout << ans.size() << "\n";
    }
    for (const std::string& line: ans)
    {
        fout << line << "\n";
    }
    fout.flush();
    fout.close();
}
