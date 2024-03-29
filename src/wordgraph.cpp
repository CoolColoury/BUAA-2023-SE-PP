#include "wordgraph.h"
#include <unordered_set>

inline void to_lower_string(std::string& word)
{
    for (char& c : word)
    {
        c = (char)tolower(c);
    }
}

WordGraph::WordGraph(const std::vector<std::string>& words, Config& config)
{
    // 初始化 m_word_graph
    for (int letter = 0; letter < NUM_NODE; letter++)
    {
        m_word_graph.insert(make_pair(letter, std::vector<Edge>()));
    }
    // 插入边
    std::unordered_set<std::string> vis;
    for (std::string word : words)
    {
        to_lower_string(word);
        if (vis.insert(word).second)
        {
            Edge edge = Edge(edge_num++, word, config.type);
            m_word_graph[edge.from].push_back(edge);
        }
    }
    // 根据config改变边的视图
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
            check_ring_exception();
        }
        make_topo_list();
        if (config.type != 'n')
        {
            simplify_dag(config.type);
        }
    }
    else 
    {
        make_graph2();
    }
}

void WordGraph::simplify_dag(char type)
{
    std::vector<std::string> new_words;
    for (int i = 0; i < NUM_NODE; i++) 
    {
        std::map<int, std::string> map;
        for (Edge e : get_edges(i))
        {
            if (map.count(e.to) != 0)
            {
                if (map[e.to].size() < e.word.size())
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
    for (int letter = 0; letter < NUM_NODE; letter++)
    {
        m_word_graph[letter].clear();
    }
    for (std::string word : new_words)
    {
        Edge edge = Edge(edge_num++, word, type);
        m_word_graph[edge.from].push_back(edge);
    }
}

void WordGraph::make_graph2()
{
    for (int from = 0; from < NUM_NODE; from++)
    {
        m_word_graph2.insert(make_pair(from, std::map<int, std::vector<Edge>>()));
        for (int to = 0; to < NUM_NODE; to++)
        {
            m_word_graph2[from].insert(make_pair(to, std::vector<Edge>()));
        }
        std::set<int> tos;
        for (Edge e : get_edges(from))
        {
            int to = e.to;
            m_word_graph2[from][to].push_back(e);
            tos.insert(to);
        }
        for (int to : tos) {
            std::sort(m_word_graph2[from][to].begin(), m_word_graph2[from][to].end(), cmp_edge);
        }
    }
}

bool cmp_edge(const Edge& e1, const Edge& e2)
{
    return e1.length > e2.length;
}

long long WordGraph::get_chains_num()
{
    std::vector<long long> cnt(26);
    std::vector<Edge const*> record_self_loop(26, nullptr);
    for (auto it = get_topo_list().rbegin(); it != get_topo_list().rend(); ++it)
    {
        int now = *it;
        for (const Edge& e : get_edges(now))
        {
            if (e.from == e.to)
            {
                record_self_loop[e.from] = &e;
            }
            else
            {
                cnt[e.from] += 1 + cnt[e.to];
            }
        }
        if (record_self_loop[now] != nullptr)
        {
            cnt[now] += cnt[now] + 1;
        }
    }
    long long sum = 0;
    for (int i = 0; i < 26; i++)
    {
        sum += cnt[i];
    }
    sum -= edge_num;
    return sum;
}
