#pragma once
#include "wordgraph.h"
#include "parser.h"
#include <iostream>
#ifndef _SOLVER

#define SOLVER

namespace solver
{
    class Strategy
    {
    public:
        virtual void solve(WordGraph word_graph, parser::config config, const std::ostream& output) = 0;
    };

    class GenChainAllStrategy : public Strategy
    {
        void solve(WordGraph word_graph, parser::config config, const std::ostream& output);
    };

    class GenChainWordLengthStrategy : public Strategy
    {
        void solve(WordGraph word_graph, parser::config config, const std::ostream& output);
    };

    class GenChainLetterLengthStrategy : public Strategy
    {
        void solve(WordGraph word_graph, parser::config config, const std::ostream& output);
    };

    class Solver
    {
    private:
        Strategy* m_stratege;
        WordGraph m_word_graph;

    public:
        void set_strategy(Strategy* strategy);
        void solve();

        ~Solver();
    };
}

#endif //_SOLVER