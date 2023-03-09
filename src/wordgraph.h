#pragma once
#include <string>
#include <map>
#include <vector>
#include <queue>

#ifndef _WORDGRAPH
#define WORDGRAPH

struct Edge
{
    int id;
    std::string word;
    int length;
    int from;
    int to;

    Edge(int id, std::string word) :id(id), word(word)
    {
        length = int(word.size());
        from = tolower(word.front()) - 'a';
        to = tolower(word.back()) - 'a';
    }
};

class WordGraph
{
private:
    int edge_num = 0;
    std::map<int, std::vector<Edge>> m_word_graph;
    static const int NUM_NODE = 26;

    bool find_circle_by_topo() const;

public:
    WordGraph(const std::vector<std::string>& words);
    const std::vector<Edge>& get_edges(int node) const { return m_word_graph.at(node); }
    bool contain_circle() const;
};


#endif //_WORDGRAPH