#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <list>
#include <vector>

template<typename T>
class Graph
{
    std::unordered_map<T, std::list<T>> adj;

public:
    Graph() = default;
    ~Graph() = default;

    // dodanie wierzchołka
    void add_node(T v)
    {
        adj[v]; // tworzy pustą listę jeśli nie istnieje
    }

    // dodanie krawędzi (graf nieskierowany)
    void add_edge(T u, T v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // czy graf jest skierowany
    bool is_directed() const
    {
        return false;
    }

    // iteratory po wierzchołkach
    auto node_begin()
    {
        return adj.begin();
    }

    auto node_end()
    {
        return adj.end();
    }

    // sąsiedzi wierzchołka
    std::vector<T> neighbors(T u)
    {
        return std::vector<T>(adj[u].begin(), adj[u].end());
    }
};

#endif // GRAPH_HPP
