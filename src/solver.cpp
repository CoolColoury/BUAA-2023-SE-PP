#include "solver.h"
#include <sstream>
#include <thread>

void GenChainsAllStrategy::dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words, WordGraph& word_graph, std::vector<std::string>& ans)
{
    for (Edge e : word_graph.get_edges(now))
    {
        if (!vis[e.id])
        {
            words.push_back(e.word);
            add_chain(ans, words);
            // check_too_much_result(ans.size()); // 20000+“Ï≥£
            vis[e.id] = true;
            dfs_circle(e.to, vis, words, word_graph, ans);
            vis[e.id] = false;
            words.pop_back();
        }
    }
}

void GenChainsAllStrategy::solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans)
{
    int num_node = 26;
    std::vector<bool> vis(word_graph.get_edge_num(), false);
    ans.push_back(std::to_string(0));
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
    ans[0] = std::to_string(ans.size() - 1);
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

void Solver::print_vector(std::ostream& output, std::vector<std::string>& ans)
{
    for (auto it = ans.begin(); it != ans.end(); ++it)
    {
        output << *it << '\n';
    }
}

Solver::Solver(WordGraph& word_graph, Config& config) : m_word_graph(word_graph), m_config(config)
{
    if (config.type == 'n')
    {
        this->m_strategy = new GenChainsAllStrategy();
    }
    else if (config.type == 'w')
    {
        if (config.enable_loop)
        {
            this->m_strategy = new GenChainMaxOnMDGThreadStrategy();
        }
        else
        {
            this->m_strategy = new GenChainMaxOnDFAStrategy();
        }
    }
    else if (config.type == 'c')
    {
        if (config.enable_loop)
        {
            this->m_strategy = new GenChainMaxOnMDGThreadStrategy();
        }
        else
        {
            this->m_strategy = new GenChainMaxOnDFAStrategy();
        }
    }
    else
    {
        this->m_strategy = nullptr;
    }
}

void Solver::solve(std::ostream& output)
{
    std::vector<std::string> ans;
    m_strategy->solve(m_word_graph, m_config, ans);
    print_vector(output, ans);
}

void Solver::solve(std::vector<std::string>& output)
{
    m_strategy->solve(m_word_graph, m_config, output);
}

Solver::~Solver()
{
    if (this->m_strategy != nullptr)
    {
        delete this->m_strategy;
    }
}

void GenChainMaxOnDFAStrategy::solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans)
{
    std::vector<int> dp(26, 0);
    std::vector<Edge const*> record(26, nullptr);
    std::vector<Edge const*> record_self_loop(26, nullptr);
    for (auto it = word_graph.get_topo_list().rbegin(); it != word_graph.get_topo_list().rend(); ++it)
    {
        int now = *it;
        if (config.n_head == now + 'a')
        {
            continue;
        }
        for (const Edge& e : word_graph.get_edges(now))
        {
            if (e.from == e.to)
            {
                record_self_loop[e.from] = &e;
            }
            if (config.tail != 0 && !((e.to + 'a' == config.tail) || dp[e.to] != 0))
            {
                continue;
            }
            else if (dp[e.from] < dp[e.to] + e.length)
            {
                dp[e.from] = dp[e.to] + e.length;
                record[e.from] = &e;
            }
        }
        if (record_self_loop[now] != nullptr && (config.tail == 0 || ((now + 'a' == config.tail) || dp[now] != 0)))
        {
            dp[now] = dp[now] + record_self_loop[now]->length;
        }
    }
    int begin = -1;
    int max_length = 0;
    for (int i = 0; i < 26; i++)
    {
        if (max_length < dp[i])
        {
            begin = i;
            max_length = dp[i];
        }
    }
    if (config.head != 0)
    {
        begin = config.head - 'a';
    }
    if (begin != -1)
    {
        Edge const* e = record[begin];
        while (e != nullptr)
        {
            if (record_self_loop[e->from] != nullptr)
            {
                ans.push_back(record_self_loop[e->from]->word);
            }
            ans.push_back(e->word);
            e = record[e->to];
        }
    }
}

void GenChainMaxOnMDGStrategy::dfs_circle(int now, std::vector<bool>& vis, std::vector<std::string>& words, WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len)
{
    bool dfs_self_loop = false;
    for (Edge e : word_graph.get_edges(now, now)) {
        if (!vis[e.id])
        {
            words.push_back(e.word);
            if ((config.tail == 0) || (config.tail == (e.to + 'a')))
            {
                if (words.size() > 1 && ans_len < words_len + e.length)
                {
                    ans = words;
                    ans_len = words_len + e.length;
                }
            }
            vis[e.id] = true;
            dfs_circle(e.to, vis, words, word_graph, config, ans, words_len + e.length, ans_len);
            vis[e.id] = false;
            words.pop_back();
            dfs_self_loop = true;
            break;
        }
    }
    if (!dfs_self_loop) {
        int num_node = 26;
        for (int to = 0; to < num_node; to++) {
            if (to == now)
            {
                continue;
            }
            for (Edge e : word_graph.get_edges(now, to))
            {
                if (!vis[e.id])
                {
                    words.push_back(e.word);
                    if ((config.tail == 0) || (config.tail == (e.to + 'a')))
                    {
                        if (ans_len < words_len + e.length)
                        {
                            ans = words;
                            ans_len = words_len + e.length;
                        }
                    }
                    if (e.to != config.n_head + 'a')
                    {
                        vis[e.id] = true;
                        dfs_circle(to, vis, words, word_graph, config, ans, words_len + e.length, ans_len);
                        vis[e.id] = false;
                    }
                    
                    words.pop_back();
                    break;
                }
            }
        }
    }
}

void GenChainMaxOnMDGStrategy::solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans)
{
    int num_node = 26;
    std::vector<bool> vis(word_graph.get_edge_num(), false);
    int ans_len = 0;
    for (int start = 0; start < num_node; start++)
    {
        // guard
        if (config.n_head == (start + 'a'))
        {
            continue;
        }
        else if (config.head != 0 && config.head != (start + 'a'))
        {
            continue;
        }
        std::vector<std::string> edges;
        dfs_circle(start, vis, edges, word_graph, config, ans, 0, ans_len);
    }
    if (ans.size() == 1)
    {
        ans.clear();
    }
}

void dfs_by_thread(int now, std::vector<bool>& vis, std::vector<std::string>& words,
    WordGraph& word_graph, Config& config, std::vector<std::string>& ans, int words_len, int& ans_len)
{
    bool dfs_self_loop = false;
    for (Edge e : word_graph.get_edges(now, now)) {
        if (!vis[e.id])
        {
            words.push_back(e.word);
            if ((config.tail == 0) || (config.tail == (e.to + 'a')))
            {
                if (words.size() > 1 && ans_len < words_len + e.length)
                {
                    ans = words;
                    ans_len = words_len + e.length;
                }
            }
            vis[e.id] = true;
            dfs_by_thread(e.to, vis, words, word_graph, config, ans, words_len + e.length, ans_len);
            vis[e.id] = false;
            words.pop_back();
            dfs_self_loop = true;
            break;
        }
    }
    if (!dfs_self_loop) {
        int num_node = 26;
        for (int to = 0; to < num_node; to++) {
            if (to == now)
            {
                continue;
            }
            for (Edge e : word_graph.get_edges(now, to))
            {
                if (!vis[e.id])
                {
                    words.push_back(e.word);
                    if ((config.tail == 0) || (config.tail == (e.to + 'a')))
                    {
                        if (ans_len < words_len + e.length)
                        {
                            ans = words;
                            ans_len = words_len + e.length;
                        }
                    }
                    if (e.to != config.n_head + 'a')
                    {
                        vis[e.id] = true;
                        dfs_by_thread(to, vis, words, word_graph, config, ans, words_len + e.length, ans_len);
                        vis[e.id] = false;
                    }

                    words.pop_back();
                    break;
                }
            }
        }
    }
}

void GenChainMaxOnMDGThreadStrategy::solve(WordGraph& word_graph, Config& config, std::vector<std::string>& ans)
{
    const int num_node = 26;
    int c_ans_len[26] = { 0 };
    using std::vector;
    vector<std::string> c_ans[26];
    std::thread threads[26];
    vector<std::string> edges[26];
    vector<vector<bool>> vis(26, vector<bool>(word_graph.get_edge_num(), false));
    for (int i = 0; i < num_node; i++)
    {
        // guard
        if (config.n_head == (i + 'a'))
        {
            continue;
        }
        else if (config.head != 0 && config.head != (i + 'a'))
        {
            continue;
        }
        using std::ref;
        if (!word_graph.get_edges(i).empty())
        {
            threads[i] = std::thread(dfs_by_thread, i, ref(vis[i]), ref(edges[i]), ref(word_graph), ref(config), ref(c_ans[i]), 0, ref(c_ans_len[i]));
        }
    }
    for (int i = 0; i < num_node; i++) 
    {
        if (!word_graph.get_edges(i).empty())
        {
            threads[i].join();
        }
    }
    int ans_len = 0;
    int id = -1;
    for (int start = 0; start < num_node; start++) {
        if (c_ans[start].size() > 1 && ans_len < c_ans_len[start])
        {
            ans_len = c_ans_len[start];
            id = start;
        }
    }
    if (id != -1)
    {
        ans = c_ans[id];
    }
}
