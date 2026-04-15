#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <unordered_map>
#include <cassert>
#include "dfs.hpp"
#include "graph.hpp"

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

    // Drzewo rozpinające ma dokładnie n-1 krawędzi
    assert(edges.size() == n - 1);

    // Dodatkowe krawędzie
    std::uniform_int_distribution<int> nodeDist(0, n - 1);
    for (int k = 0; k < 5; ++k)
    {
        int u = nodeDist(rng);
        int v = nodeDist(rng);
        if (u != v) edges.insert({std::min(u,v), std::max(u,v)});
    }

    // Graf ma co najmniej n-1 krawędzi
    assert(edges.size() >= n - 1);

    // Graf nie przekracza maksymalnej liczby krawędzi
    assert(edges.size() <= n * (n - 1) / 2);

    // Budujemy graf
    Graph g;
    for (int i = 0; i < n; ++i) g.add_node(i);
    for (auto& [u, v] : edges)  g.add_edge(u, v);

    // Wypisujemy krawędzie
    std::cout << "Krawędzie grafu (" << edges.size() << "):"<<std::endl;
    for (auto& [u, v] : edges)
        std::cout << u << " -- " << v << "\n";

    // DFS
    DFS<int, Graph> dfs(g);
    dfs.run();

    // DFS odwiedził wszystkie wierzchołki (graf jest spójny)
    assert(dfs.preorder.size() == n);

    // Każdy wierzchołek odwiedzony dokładnie raz w preorder
    std::set<int> unique_pre(dfs.preorder.begin(), dfs.preorder.end());
    assert(unique_pre.size() == n);

    // Każdy wierzchołek odwiedzony dokładnie raz w postorder
    std::set<int> unique_post(dfs.postorder.begin(), dfs.postorder.end());
    assert(unique_post.size() == n);

    // preorder i postorder mają tę samą liczbę elementów
    assert(dfs.preorder.size() == dfs.postorder.size());

    // preorder i postorder zawierają te same wierzchołki
    assert(unique_pre == unique_post);

    // Pierwszy wierzchołek preorder != pierwszy wierzchołek postorder
    // (w DFS najpierw wychodzimy z liści, nie z korzenia)
    assert(dfs.preorder.front() != dfs.postorder.front());

    // Pierwszy wierzchołek preorder == ostatni wierzchołek postorder
    // (korzeń jest odkryty pierwszy i opuszczony ostatni)
    assert(dfs.preorder.front() == dfs.postorder.back());

    // Wypisujemy wyniki
    std::cout<<std::endl<< "Kolejność odkrywania wierzchołków (preorder):"<<std::endl;
    for (int v : dfs.preorder)
    {
        std::cout << v << " ";
    }

    std::cout<<std::endl << "Kolejność zakończenia wierzchołków (postorder):"<<std::endl;
    for (int v : dfs.postorder)
    {
        std::cout << v << " ";
    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Wszystkie asserty przeszły pomyślnie!"<<std::endl;

    return 0;
}
