#include "wordgraph.h"

WordGraph::WordGraph(std::vector<std::string> words)
{
    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    int edgeId = 0;
    for (std::string word : words)
    {
        // TODO释放edge，需要析构函数
        Edge* edge = new Edge();
        edge->id = edgeId++;
        edge->word = word;
        edge->length = int(word.size());
        m_word_graph[tolower(word[0])].push_back(*edge);
    }
}
