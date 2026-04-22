#include <iostream>
#include <cassert>
#include "connected.hpp"
#include "graph.hpp"

int main()
{
    Graph<int> G;

    // dodaj wierzchołki
    for (int i = 0; i < 10; i++)
    {
        G.add_node(i);
    }

    // składowa 1
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G.add_edge(2, 3);

    // składowa 2
    G.add_edge(4, 5);
    G.add_edge(5, 6);

    // składowa 3
    G.add_edge(7, 8);
    G.add_edge(8, 9);

    // uruchom algorytm
    ConnectedComponents<int, Graph<int>> cc(G);
    cc.run();


    // 1. liczba składowych
    assert(cc.ncc == 3);

    // 2. spójność wewnątrz składowych
    assert(cc.component[0] == cc.component[1]);
    assert(cc.component[1] == cc.component[2]);
    assert(cc.component[2] == cc.component[3]);

    assert(cc.component[4] == cc.component[5]);
    assert(cc.component[5] == cc.component[6]);

    assert(cc.component[7] == cc.component[8]);
    assert(cc.component[8] == cc.component[9]);

    // 3. różne składowe są różne
    assert(cc.component[0] != cc.component[4]);
    assert(cc.component[0] != cc.component[7]);
    assert(cc.component[4] != cc.component[7]);

    // wypisz wynik
    for (auto& pair : cc.component)
    {
        std::cout << pair.first << " -> component " << pair.second << std::endl;
    }

    std::cout << "Total components: " << cc.ncc << std::endl;

    return 0;
}
