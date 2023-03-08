#include "wordgraph.h"

WordGraph::WordGraph(std::vector<std::string> words)
{
    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    for (std::string word : words)
    {
        // TODO�ͷ�edge����Ҫ��������
        Edge* edge = new Edge(edge_num++, word);
        m_word_graph[edge->from].push_back(*edge);
    }
}
