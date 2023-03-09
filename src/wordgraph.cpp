#include "wordgraph.h"

WordGraph::WordGraph(const std::vector<std::string>& words)
{
    for (int letter = 0; letter < NUM_NODE; letter++)
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

bool WordGraph::contain_circle() const
{
    std::vector<bool> vis_node(NUM_NODE, false);
    // 处理自环
    for (int now = 0; now < NUM_NODE; now++)
    {
        int num_self_loop = 0;
        for (Edge e : get_edges(now))
        {
            if (e.from == e.to)
            {
                num_self_loop += 1;
            }
        }
        if (num_self_loop > 1)
        {
            return true;
        }
    }

    return find_circle_by_topo();
}

bool WordGraph::find_circle_by_topo() const
{
    std::vector<int> in_degree(NUM_NODE, 0);
    for (int node = 0; node < NUM_NODE; node++)
    {
        for (Edge e : get_edges(node))
        {
            if (e.from != e.to)
            {
                in_degree[e.to] += 1;
            }
        }
    }
    std::queue<int> q;
    for (int node = 0; node < NUM_NODE; node++)
    {
        if (in_degree[node] == 0)
        {
            q.push(node);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (Edge e : get_edges(node))
        {
            if (e.from != e.to)
            {
                in_degree[e.to] -= 1;
                if (in_degree[e.to] == 0)
                {
                    q.push(e.to);
                }
            }
        }
    }
    for (int node = 0; node < NUM_NODE; node++)
    {
        if (in_degree[node] != 0)
        {
            return true;
        }
    }
    return false;
}
