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
};

class WordGraph
{
private:
    std::map<char, std::vector<Edge>> m_word_graph;

public:
    WordGraph(std::vector<std::string> words);

};


#endif //_WORDGRAPH