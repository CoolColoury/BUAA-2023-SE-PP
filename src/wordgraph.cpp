#include "wordgraph.h"

WordGraph::WordGraph(const std::vector<std::string>& words)
{
    for (int letter = 0; letter < 26; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    for (std::string word : words)
    {
        // TODO释放edge，需要析构函数
        Edge edge = Edge(edge_num++, word);
        m_word_graph[edge.from].push_back(edge);
    }
}

bool WordGraph::contain_circle()
{
    std::vector<bool> vis(26, false);
    for (int now = 0; now < 26; now++)
    {
        if (dfs_circle(now, vis))
        {
            return true;
        }
    }
    return false;
}

bool WordGraph::dfs_circle(int now, std::vector<bool>& vis)
{
    vis[now] = true;
    for (Edge e : get_edges(now))
    {
        const int to = e.to;
        if (vis[to] || dfs_circle(to, vis))
        {
            return true;
        }
    }
    vis[now] = false;
    return false;
}
