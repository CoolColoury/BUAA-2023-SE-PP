#pragma once
#include <string>
#include <map>
#include <vector>

#ifndef _WORDGRAPH
#define WORDGRAPH

struct edge
{
    int id;
    std::string word;
    int length;
};

class WordGraph
{
private:
    std::map<char, std::vector<edge>> m_word_graph;


public:
    WordGraph(std::vector<std::string> words);

};


#endif //_WORDGRAPH