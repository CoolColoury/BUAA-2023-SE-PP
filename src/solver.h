#pragma once
#pragma once
#include "wordgraph.h"
#include "config.h"
#include <iostream>
#ifndef _SOLVER

#define SOLVER


class Strategy
{
public:
    virtual void solve(WordGraph& word_graph, Config config, const std::ostream& output) = 0;
};

class GenChainAllStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config config, const std::ostream& output);
};

class GenChainWordLengthStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config config, const std::ostream& output);
};

class GenChainLetterLengthStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config config, const std::ostream& output);
};

class Solver
{
private:
    Strategy* m_strategy;
    WordGraph m_word_graph;
    Config m_config;

public:
    Solver(WordGraph& word_graph, Config& config);
    void solve(std::ostream& output);
    void solve(std::vector<std::string>& output);

    ~Solver();
};

#endif //_SOLVER