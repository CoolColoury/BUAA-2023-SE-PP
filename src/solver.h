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
    virtual void solve(WordGraph& word_graph, Config& config, std::ostream& output) = 0;
    void print_vector(std::ostream& output, std::vector<std::string>& edges);
};

class GenChainsAllStrategy : public Strategy
{
    void dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& edges, WordGraph& word_graph, std::vector<std::string>& ans);
    void solve(WordGraph& word_graph, Config& config, std::ostream& output);
    void add_chain(std::vector<std::string>& ans, std::vector<std::string>& words);
};

class GenChainWordLengthStrategy : public Strategy
{
    void dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words,
        WordGraph& word_graph, Config& config, std::vector<std::string>& ans);
    void solve(WordGraph& word_graph, Config& config, std::ostream& output);
};

class GenChainLetterLengthStrategy : public Strategy
{
    void dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words,
        WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len);
    void solve(WordGraph& word_graph, Config& config, std::ostream& output);
};

class GenChainWordOnDFAStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config& config, std::ostream& output);
};

class GenChainCharOnDFAStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config& config, std::ostream& output);
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