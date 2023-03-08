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
    char from;
    char to;

    Edge(int id, std::string word) :id(id), word(word)
    {
        length = int(word.size());
        from = tolower(word.front());
        to = tolower(word.back());
    }
};

class WordGraph
{
private:
    int edge_num = 0;
    std::map<char, std::vector<Edge>> m_word_graph;

public:
    WordGraph(std::vector<std::string> words);
    const std::vector<Edge>& get_edges(char node) const { return m_word_graph.at(node); }

};


#endif //_WORDGRAPH