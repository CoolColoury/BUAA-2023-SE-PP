#include "solver.h"
#include <sstream>

void GenChainsAllStrategy::dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words, WordGraph& word_graph, std::vector<std::string>& ans)
{
    for (Edge e : word_graph.get_edges(now))
    {
        if (!vis[e.id])
        {
            words.push_back(e.word);
            add_chain(ans, words);
            vis[e.id] = true;
            dfs_circle(e.to, vis, words, word_graph, ans);
            vis[e.id] = false;
            words.pop_back();
        }
    }
}

void GenChainsAllStrategy::solve(WordGraph& word_graph, Config& config, std::ostream& output)
{
    int num_node = 26;
    std::vector<bool> vis(word_graph.get_edge_num(), false);
    std::vector<std::string> ans;
    for (int node = 0; node < num_node; node++)
    {
        for (Edge e : word_graph.get_edges(node))
        {
            std::vector<std::string> edges;
            edges.push_back(e.word);
            vis[e.id] = true;
            dfs_circle(e.to, vis, edges, word_graph, ans);
            vis[e.id] = false;
            edges.pop_back();
        }
    }
    output << ans.size() << '\n';
    print_vector(output, ans);
}

void GenChainsAllStrategy::add_chain(std::vector<std::string>& ans, std::vector<std::string>& words)
{
    std::string res;
    std::vector<std::string>::iterator it = words.begin();
    res.append(*it);
    ++it;
    while (it != words.end())
    {
        res.append(" ");
        res.append(*it);
        ++it;
    }
    ans.push_back(res);
}

void GenChainWordLengthStrategy::dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words, WordGraph& word_graph, Config& config, std::vector<std::string>& ans)
{
    for (Edge e : word_graph.get_edges(now))
    {
        if (!vis[e.id])
        {
            if (config.n_head == (e.from + 'a'))
            {
                continue;
            }
            words.push_back(e.word);
            if ((config.tail == 0) || (config.tail == (e.to + 'a')))
            {
                if (ans.size() < words.size())
                {
                    ans = words;
                }
            }
            vis[e.id] = true;
            dfs_circle(e.to, vis, words, word_graph, config, ans);
            vis[e.id] = false;
            words.pop_back();
        }
    }
}

void GenChainWordLengthStrategy::solve(WordGraph& word_graph, Config& config, std::ostream& output)
{
    int num_node = 26;
    std::vector<bool> vis(word_graph.get_edge_num(), false);
    std::vector<std::string> ans;
    for (int node = 0; node < num_node; node++)
    {
        // guard
        if (config.n_head == (node + 'a'))
        {
            continue;
        }
        else if (config.head != 0 && config.head != (node + 'a'))
        {
            continue;
        }
        for (Edge e : word_graph.get_edges(node))
        {
            std::vector<std::string> edges;
            edges.push_back(e.word);
            vis[e.id] = true;
            dfs_circle(e.to, vis, edges, word_graph, config, ans);
            vis[e.id] = false;
            edges.pop_back();
        }
    }
    print_vector(output, ans);
}

void GenChainLetterLengthStrategy::dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words, WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len)
{
    for (Edge e : word_graph.get_edges(now))
    {
        if (!vis[e.id])
        {
            if (config.n_head == (e.from + 'a'))
            {
                continue;
            }
            words.push_back(e.word);
            if ((config.tail == 0) || (config.tail == (e.to + 'a')))
            {
                if (ans_len < words_len + e.length)
                {
                    ans = words;
                    ans_len = words_len + e.length;
                }
            }
            vis[e.id] = true;
            dfs_circle(e.to, vis, words, word_graph, config, ans, words_len + e.length, ans_len);
            vis[e.id] = false;
            words.pop_back();
        }
    }
}

void GenChainLetterLengthStrategy::solve(WordGraph& word_graph, Config& config, std::ostream& output)
{
    int num_node = 26;
    std::vector<bool> vis(word_graph.get_edge_num(), false);
    std::vector<std::string> ans;
    int ans_len = 0;
    for (int node = 0; node < num_node; node++)
    {
        // guard
        if (config.n_head == (node + 'a'))
        {
            continue;
        }
        else if (config.head != 0 && config.head != (node + 'a'))
        {
            continue;
        }
        for (Edge e : word_graph.get_edges(node))
        {
            std::vector<std::string> edges;
            edges.push_back(e.word);
            vis[e.id] = true;
            dfs_circle(e.to, vis, edges, word_graph, config, ans, e.length, ans_len);
            vis[e.id] = false;
            edges.pop_back();
        }
    }
    print_vector(output, ans);
}

Solver::Solver(WordGraph& word_graph, Config& config) : m_word_graph(word_graph), m_config(config)
{
    if (config.type == 'n')
    {
        this->m_strategy = new GenChainsAllStrategy();
    }
    else if (config.type == 'w')
    {
        this->m_strategy = new GenChainWordLengthStrategy();
    }
    else if (config.type == 'c')
    {
        this->m_strategy = new GenChainLetterLengthStrategy();
    }
    else
    {
        this->m_strategy = nullptr;
    }
}

void Solver::solve(std::ostream& output)
{
    m_strategy->solve(m_word_graph, m_config, output);
}

void Solver::solve(std::vector<std::string>& output)
{
    std::ostringstream oss;
    solve(oss);
    std::istringstream iss(oss.str());
    std::string word;
    while (getline(iss, word))
    {
        output.push_back(word);
    }
}

Solver::~Solver()
{
    if (this->m_strategy != nullptr)
    {
        delete this->m_strategy;
    }
}

void Strategy::print_vector(std::ostream& output, std::vector<std::string>& edges)
{
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        output << *it << '\n';
    }
}