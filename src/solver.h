#pragma once

#include "wordgraph.h"
#include "config.h"
#include <iostream>

#ifndef _SOLVER
#define _SOLVER

class Strategy
{
public:
    virtual void solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans) = 0;

    virtual ~Strategy() = 0;
};

class GenChainsAllStrategy : public Strategy
{
    void dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& edges, WordGraph& word_graph, std::vector<std::string>& ans);
    void solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans);
    void add_chain(std::vector<std::string>& ans, std::vector<std::string>& words);
};

class GenChainMaxOnDFAStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans);
};

//class GenChainMaxOnMDGStrategy : public Strategy
//{
//public:
//    void dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words,
//        WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len);
//    void solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans);
//};

class GenChainMaxOnMDGThreadStrategy : public Strategy
{
    void solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans);
};

class Solver
{
private:
    Strategy* m_strategy;
    WordGraph m_word_graph;
    Config m_config;

public:
    Solver(WordGraph& word_graph, Config& config);
    void solve(std::vector<std::string>& output);

    ~Solver();
};
void dfs_by_thread(int now, std::vector<bool>& vis, std::vector<std::string>& words,
    WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len);

#endif //_SOLVER