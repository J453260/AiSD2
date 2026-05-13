#include <iostream>
#include <vector>
#include <cassert>
#include "FloydWarshall.hpp"
#include "graph.hpp"

std::vector<std::vector<int>> transitive_closure(int n, const std::vector<std::pair<int,int>>& edges)
{
    std::vector<std::vector<int>> T(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        T[i][i] = 1;
    }

    for (auto& [i, j] : edges)
    {
        T[i][j] = 1;
    }

    // T^(k): czy istnieje ścieżka z i do j przez wierzchołki {0..k}
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
            }
        }
    }

    return T;
}


int main()
{
    const int n = 10;
    Graph g(n, true);

    g.add_edge(0, 1, 1.0f);
    g.add_edge(0, 3, 1.0f);
    g.add_edge(1, 2, 1.0f);
    g.add_edge(2, 4, 1.0f);
    g.add_edge(3, 4, 1.0f);
    g.add_edge(4, 5, 1.0f);
    g.add_edge(5, 6, 1.0f);
    g.add_edge(6, 7, 1.0f);
    g.add_edge(7, 8, 1.0f);
    g.add_edge(8, 9, 1.0f);
    g.add_edge(3, 6, 1.0f);
    g.add_edge(1, 5, 1.0f);


    std::cout << "Liczba wierzcholkow: " << g.v() << std::endl;
    std::cout << "Liczba krawedzi:     " << g.e() << std::endl;

    // Podstawowe właściwości grafu
    assert(g.v() == 10);
    assert(g.e() == 12);
    assert(g.is_directed() == true);


    std::cout << std::endl;
    std::cout << "has_edge(0,1): " << g.has_edge(0,1) << std::endl;
    std::cout << "has_edge(1,0): " << g.has_edge(1,0) << std::endl;
    std::cout << "has_edge(0,9): " << g.has_edge(0,9) << std::endl;
    std::cout << "has_edge(8,9): " << g.has_edge(8,9) << std::endl;
    std::cout << std::endl;

    // Has_edge
    assert(g.has_edge(0, 1) == true);
    assert(g.has_edge(1, 0) == false);  // skierowany - brak krawędzi zwrotnej
    assert(g.has_edge(0, 9) == false);
    assert(g.has_edge(8, 9) == true);

    // Wagi
    assert(g.weight(0, 1) == 1.0f);
    assert(g.weight(0, 9) == 0.0f);  // brak krawędzi -> waga 0


    std::cout << "Stopnie wierzcholkow" << std::endl;
    for (int u = 0; u < n; u++)
    {
        std::cout << "  v" << u << "  indegree=" << g.indegree(u) << "  outdegree=" << g.outdegree(u) << std::endl;
    }

    // Stopnie
    assert(g.outdegree(0) == 2);  // 0->1, 0->3
    assert(g.indegree(0)  == 0);  // nic nie wchodzi do 0
    assert(g.outdegree(4) == 1);  // 4->5
    assert(g.indegree(4)  == 2);  // 2->4, 3->4
    assert(g.outdegree(9) == 0);  // 9 nie ma wychodzących
    assert(g.indegree(9)  == 1);  // 8->9


    std::cout << std::endl;
    std::cout << "Sprawdzanie wierzcholkow";
    std::cout << "has_node(0):  " << g.has_node(0)  << std::endl;
    std::cout << "has_node(9):  " << g.has_node(9)  << std::endl;
    std::cout << "has_node(10): " << g.has_node(10) << std::endl;

    // Has_node
    assert(g.has_node(0)  == true);
    assert(g.has_node(9)  == true);
    assert(g.has_node(10) == false);

    // NodeIterator — przejdź przez wszystkie wierzchołki
    int node_count = 0;
    std::cout << "NodeIterator, wierzcholki: ";
    for (auto it = g.node_begin(); it != g.node_end(); ++it)
    {
        std::cout << *it << " ";
        assert(g.has_node(*it));
        node_count++;
    }
    std::cout << std::endl;
    std::cout << "Liczba wierzcholkow: " << node_count << std::endl;
    assert(node_count == n);

    // EdgeIterator — przejdź przez wszystkie krawędzie
    int edge_count = 0;
    std::cout << std::endl;
    std::cout << "EdgeIterator, krawedzie:" << std::endl;
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
    {
        assert(g.has_edge(*it));
        edge_count++;
    }
    assert(edge_count == g.e());

    // AdjacentIterator — sąsiedzi wierzchołka 0
    std::vector<int> adj0;
    for (auto it = g.adj_begin(0); it != g.adj_end(0); ++it)
    {
        adj0.push_back(*it);
    }

    std::cout << std::endl;
    std::cout << "AdjacentIterator";
    std::cout << std::endl;
    for (int u = 0; u < n; u++)
    {
        std::cout << "  Sasiedzi v" << u << ": ";
        for (auto it = g.adj_begin(u); it != g.adj_end(u); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    assert(adj0.size() == 2);
    assert(std::find(adj0.begin(), adj0.end(), 1) != adj0.end());
    assert(std::find(adj0.begin(), adj0.end(), 3) != adj0.end());

    // Asserty: del_edge
    g.del_edge(0, 1);
    assert(g.has_edge(0, 1) == false);
    assert(g.e() == 11);

    // Del_node (zeruje wiersze i kolumny)
    g.del_node(9);
    assert(g.has_edge(8, 9) == false);

    // Asserty: clear
    g.clear();
    assert(g.e() == 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            assert(g.has_edge(i, j) == false);
        }
    }

    std::cout << std::endl;
    std::cout << "Wszystkie asserty przeszly pomyslnie." << std::endl;
    return 0;
}
