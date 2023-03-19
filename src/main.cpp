// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "parser.h"
#include "wordgraph.h"
#include "solver.h"
#include "output.h"

int main(int argc, char* argv[])
{
    try
    {
        Parser parser;
        parser.parse(argc - 1, argv + 1);
        WordGraph graph(parser.get_words(), parser.get_config());
        Solver solver(graph, parser.get_config());
        std::vector<std::string> ans;
        solver.solve(ans);
        write_to_solution_txt(ans, parser.get_config().type);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
 
