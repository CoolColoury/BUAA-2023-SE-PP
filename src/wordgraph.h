#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include "config.h"
#include "error.h"

#ifndef _WORDGRAPH
#define WORDGRAPH

struct Edge
{
    int id;
    std::string word;
    int length;
    int from;
    int to;

    Edge(int id, std::string word, char type) :id(id), word(word)
    {
        length = type == 'w' ? 1 : int(word.size());
        from = tolower(word.front()) - 'a';
        to = tolower(word.back()) - 'a';
    }
};

bool cmp_edge(const Edge& e1, const Edge& e2);

class WordGraph
{
private:
    int edge_num = 0;
    std::map<int, std::vector<Edge>> m_word_graph;
    std::map<int, std::map<int, std::vector<Edge>>> m_word_graph2;
    static const int NUM_NODE = 26;
    std::vector<int> topo_list;


public:
    WordGraph(const std::vector<std::string>& words, Config& config);
    int get_edge_num() const { return edge_num; }
    bool contain_circle();
    bool make_topo_list();
    void parseConfig(Config& config);

    const std::vector<Edge>& get_edges(int node) const { return m_word_graph.at(node); }
    const std::vector<Edge>& get_edges(int from, int to) const { return m_word_graph2.at(from).at(to); }
    const std::vector<int>& get_topo_list() const { return topo_list; };
    
    // ÎÞ»·Í¼¼ò»¯
    void simplify_dag(char type);

    void make_graph2(char type);
};


#endif //_WORDGRAPH