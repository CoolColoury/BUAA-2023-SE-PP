#include "solver.h"
#include <sstream>

void GenChainAllStrategy::solve(WordGraph& word_graph, Config config, const std::ostream& output)
{

}

void GenChainWordLengthStrategy::solve(WordGraph& word_graph, Config config, const std::ostream& output)
{

}

void GenChainLetterLengthStrategy::solve(WordGraph& word_graph, Config config, const std::ostream& output)
{

}

Solver::Solver(WordGraph& word_graph, Config& config) : m_word_graph(word_graph), m_config(config)
{
    if (config.type == 'n')
    {
        this->m_strategy = new GenChainAllStrategy();
    }
    else if (config.type == 'w')
    {
        this->m_strategy = new GenChainWordLengthStrategy();
    }
    else if (config.type == 'c')
    {
        this->m_strategy = new GenChainLetterLengthStrategy();
    }
    else
    {
        this->m_strategy = nullptr;
    }
}

void Solver::solve(std::ostream& output)
{
    
}

void Solver::solve(std::vector<std::string>& output)
{
    std::ostringstream oss;
    solve(oss);
    std::istringstream iss(oss.str());
    std::string word;
    while (iss >> word)
    {
        output.push_back(word);
    }

}

Solver::~Solver()
{
    if (this->m_strategy != nullptr)
    {
        delete this->m_strategy;
    }
}

void Strategy::solve(WordGraph& word_graph, Config config, const std::ostream& output)
{
}
