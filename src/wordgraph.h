#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include "config.h"
#include "error.h"

#ifndef _WORDGRAPH
#define _WORDGRAPH

struct Edge
{
    int id;
    int length;
    int from;
    int to;
    std::string word;

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
    static const int NUM_NODE = 26;
    int edge_num = 0;
    std::map<int, std::vector<Edge>> m_word_graph;
    std::map<int, std::map<int, std::vector<Edge>>> m_word_graph2;
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
    
    // �޻�ͼ��
    void simplify_dag(char type);

    void make_graph2();
    int get_chains_num();
};


#endif //_WORDGRAPH