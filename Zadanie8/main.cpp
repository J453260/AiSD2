#include <iostream>
#include <cassert>
#include <limits>
#include "graph.hpp"
#include "dijkstra.hpp"

int main()
{
    // Graf skierowany z 10 wierzcholkami
    Graph G(10, true);

    // Krawedzie z wagami (u, v, waga)
    G.add_edge(0, 1, 2.0f);
    G.add_edge(0, 2, 5.0f);
    G.add_edge(1, 2, 1.0f);
    G.add_edge(1, 3, 7.0f);
    G.add_edge(2, 3, 2.0f);
    G.add_edge(2, 4, 3.0f);
    G.add_edge(3, 5, 1.0f);
    G.add_edge(4, 5, 4.0f);
    G.add_edge(4, 6, 2.0f);
    G.add_edge(5, 7, 3.0f);
    G.add_edge(6, 7, 5.0f);
    G.add_edge(6, 8, 1.0f);
    G.add_edge(7, 9, 2.0f);
    G.add_edge(8, 9, 4.0f);

    // Uruchomienie Dijkstry od wierzcholka 0
    Dijkstra<int, Graph> dijkstra(G);
    dijkstra.run(0);

    // Wyswietlenie wynikow
    std::cout << "Najkrotsze sciezki od wierzcholka 0:\n";
    for (int i = 0; i < 10; i++)
        std::cout << "0 -> " << i << " : " << dijkstra.distance[i] << "\n";

    // Asserty — recznie zweryfikowane najkrotsze sciezki
    // 0->0 = 0
    assert(dijkstra.distance[0] == 0.0f);

    // 0->1 = 2 (bezposrednio)
    assert(dijkstra.distance[1] == 2.0f);

    // 0->2 = 3 (0->1->2 = 2+1)
    assert(dijkstra.distance[2] == 3.0f);

    // 0->3 = 5 (0->1->2->3 = 2+1+2)
    assert(dijkstra.distance[3] == 5.0f);

    // 0->4 = 6 (0->1->2->4 = 2+1+3)
    assert(dijkstra.distance[4] == 6.0f);

    // 0->5 = 6 (0->1->2->3->5 = 2+1+2+1)
    assert(dijkstra.distance[5] == 6.0f);

    // 0->6 = 8 (0->1->2->4->6 = 2+1+3+2)
    assert(dijkstra.distance[6] == 8.0f);

    // 0->7 = 9 (0->1->2->3->5->7 = 2+1+2+1+3)
    assert(dijkstra.distance[7] == 9.0f);

    // 0->8 = 9 (0->1->2->4->6->8 = 2+1+3+2+1)
    assert(dijkstra.distance[8] == 9.0f);

    // 0->9 = 11 (0->1->2->3->5->7->9 = 2+1+2+1+3+2)
    assert(dijkstra.distance[9] == 11.0f);

    // Asserty na parent — weryfikacja drzewa najkrotszych sciezek
    assert(dijkstra.parent[1] == 0);
    assert(dijkstra.parent[2] == 1);
    assert(dijkstra.parent[3] == 2);
    assert(dijkstra.parent[4] == 2);
    assert(dijkstra.parent[5] == 3);
    assert(dijkstra.parent[6] == 4);
    assert(dijkstra.parent[7] == 5);
    assert(dijkstra.parent[9] == 7);

    std::cout << "Wszystkie asserty przeszly pomyslnie!\n";
    return 0;
}
