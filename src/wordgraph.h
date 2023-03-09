#pragma once
#include <string>
#include <map>
#include <vector>

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
    bool dfs_circle(int now, std::vector<bool>& vis);

public:
    WordGraph(const std::vector<std::string>& words);
    const std::vector<Edge>& get_edges(int node) const { return m_word_graph.at(node); }
    bool contain_circle();
    int get_edge_num() const { return edge_num; }
};


#endif //_WORDGRAPH