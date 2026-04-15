#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include "bfs.hpp"
#include <cassert>

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
        adj[v].push_back(u);
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


int main()
{
    const int n = 10;
    std::mt19937 rng(std::random_device{}());

    std::vector<int> nodes(n);
    std::iota(nodes.begin(), nodes.end(), 0);
    std::shuffle(nodes.begin(), nodes.end(), rng);

    std::set<std::pair<int,int>> edges;

    // Drzewo rozpinające
    for (int i = 1; i < n; ++i)
    {
        std::uniform_int_distribution<int> dist(0, i - 1);
        int j = dist(rng);
        int u = std::min(nodes[i], nodes[j]);
        int v = std::max(nodes[i], nodes[j]);
        edges.insert({u, v});
    }

    assert(edges.size() == n - 1);

    // Dodatkowe krawędzie
    std::uniform_int_distribution<int> nodeDist(0, n - 1);
    for (int k = 0; k < 5; ++k)
    {
        int u = nodeDist(rng);
        int v = nodeDist(rng);
        if (u != v) edges.insert({std::min(u,v), std::max(u,v)});
    }

    assert(edges.size() >= n - 1);
    assert(edges.size() <= n * (n - 1) / 2);

    // Budujemy graf
    Graph g;
    for (int i = 0; i < n; ++i) g.add_node(i);
    for (auto& [u, v] : edges)  g.add_edge(u, v);

    // Wypisujemy krawędzie
    std::cout << "Krawędzie grafu (" << edges.size() << "):\n";
    for (auto& [u, v] : edges)
        std::cout << u << " -- " << v << "\n";

    // BFS
    BFS<int, Graph> bfs(g);
    bfs.run();

    assert(bfs.preorder.size() == n);//czy wszystkie wierzchołki odwiedzone
    assert(bfs.preorder.size() == bfs.postorder.size());

    std::cout << "\nKolejność odkrywania wierzchołków (preorder):\n";
    for (int v : bfs.preorder)
    {
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout<<std::endl;

    std::cout<<"Wszystkie testy zaliczone"<<std::endl;

    return 0;
}
