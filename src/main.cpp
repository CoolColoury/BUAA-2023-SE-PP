// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "parser.h"
#include "wordgraph.h"
#include "solver.h"

int main(int argc, char* argv[])
{
    Parser parser;
    parser.parse(argc - 1, argv + 1);
    WordGraph graph(parser.get_words(), parser.get_config());
    Solver solver(graph, parser.get_config());
    solver.solve(std::cout);

    return 0;
}
 
