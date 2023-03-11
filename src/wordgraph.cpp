#include "wordgraph.h"

WordGraph::WordGraph(const std::vector<std::string>& words)
{
    for (int letter = 0; letter < NUM_NODE; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    for (std::string word : words)
    {
        Edge edge = Edge(edge_num++, word);
        m_word_graph[edge.from].push_back(edge);
    }
}

WordGraph::WordGraph(const std::vector<std::string>& words, Config& config)
{
    for (int letter = 0; letter < NUM_NODE; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    for (std::string word : words)
    {
        Edge edge = Edge(edge_num++, word);
        m_word_graph[edge.from].push_back(edge);
    }
    parseConfig(config);
}

// 将会生成topo_list
bool WordGraph::contain_circle()
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

    return !make_topo_list();
}

bool WordGraph::make_topo_list()
{
    if (!topo_list.empty())
    {
        return true;
    }
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
        topo_list.push_back(node);
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
            topo_list.clear();
            return false;
        }
    }
    return true;
}

void WordGraph::parseConfig(Config& config)
{
    if (!config.enable_loop)
    {
        if (contain_circle())
        {
            throw new invalid_argument();
        }
        make_topo_list();
    }
}

void WordGraph::simplify_dag()
{
    std::vector<std::string> new_words;
    for (int i = 0; i < NUM_NODE; i++) 
    {
        std::map<int, std::string> map;
        for (Edge e : get_edges(i))
        {
            if (map.count(e.to) != 0)
            {
                if (map[e.to].size() < e.length)
                {
                    map[e.to] = e.word;
                }
            }
            else
            {
                map[e.to] = e.word;
            }
        }
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            new_words.push_back(it->second);
        }
    }

    edge_num = 0;
    m_word_graph.clear();
    for (int letter = 0; letter < NUM_NODE; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    for (std::string word : new_words)
    {
        Edge edge = Edge(edge_num++, word);
        m_word_graph[edge.from].push_back(edge);
    }
}
