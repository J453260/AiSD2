#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>
#include "graph.hpp"
#include "Boruvka.hpp"

int main()
{
    const int n = 6;
    Graph g(n, false);  // false = nieskierowany (MST wymaga nieskierowanego)

    g.add_edge(0, 1, 2.0f);
    g.add_edge(0, 2, 4.0f);
    g.add_edge(1, 2, 1.0f);
    g.add_edge(1, 3, 5.0f);
    g.add_edge(2, 3, 3.0f);
    g.add_edge(3, 4, 7.0f);
    g.add_edge(3, 5, 6.0f);
    g.add_edge(4, 5, 8.0f);

    std::vector<std::tuple<float, int, int>> mst = BoruvkaMST(g);

    assert(mst.size() == n - 1);

    float total = 0.0f;

    for (auto& [w, s, t] : mst)
    {
        total += w;
    }
    assert(total == 19.0f);

    // Każda krawędź MST istnieje w grafie
    for (auto& [w, s, t] : mst)
    {
        assert(g.has_edge(s, t) || g.has_edge(t, s));
        assert(g.weight(s, t) == w || g.weight(t, s) == w);
    }

    // Żadna krawędź MST nie jest pętlą własną
    for (auto& [w, s, t] : mst)
    {
        assert(s != t);
    }

    // Wszystkie wagi MST są dodatnie
    for (auto& [w, s, t] : mst)
    {
        assert(w > 0.0f);
    }

    std::cout << "Wszystkie asserty przeszly pomyslnie." << std::endl;

    return 0;
}
