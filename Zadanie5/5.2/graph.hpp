// graph.hpp
#pragma once
#include <unordered_map>
#include <vector>

class Graph
{
    std::unordered_map<int, std::vector<int>> adj;
    std::vector<int> nodes_list;
public:
    void add_node(int u)
    {
        if (adj.find(u) == adj.end())
        {
            adj[u] = {};
            nodes_list.push_back(u);
        }
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // graf nieskierowany
    }
    std::vector<int>::iterator node_begin()
    {
        return nodes_list.begin();
    }
    std::vector<int>::iterator node_end()
    {
        return nodes_list.end();
    }
    std::vector<int>& neighbors(int u)
    {
        return adj[u];
    }
};
