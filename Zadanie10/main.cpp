#include <iostream>
#include <vector>
#include <cassert>
#include "FloydWarshall.hpp"
#include "graph.hpp"
#include "TransitiveClosure.hpp"

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

    assert(g.v() == 10);
    assert(g.e() == 12);
    assert(g.is_directed() == true);

    // Zbierz krawędzie do transitive_closure
    std::vector<std::pair<int,int>> edges;
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
    {
        Edge<int> e = *it;
        edges.push_back({e.source, e.target});
    }

    auto T = transitive_closure(n, edges);

    // Każdy wierzchołek osiąga siebie
    for (int i = 0; i < n; i++)
    {
        assert(T[i][i] == 1);
    }

    // Bezpośrednie krawędzie → osiągalne
    assert(T[0][1] == 1);
    assert(T[0][3] == 1);
    assert(T[1][2] == 1);
    assert(T[3][4] == 1);
    assert(T[8][9] == 1);

    // Ścieżki wielokrokowe z wierzchołka 0
    assert(T[0][2] == 1);
    assert(T[0][4] == 1);
    assert(T[0][5] == 1);
    assert(T[0][6] == 1);
    assert(T[0][7] == 1);
    assert(T[0][8] == 1);
    assert(T[0][9] == 1);

    // Ścieżki z wierzchołka 3
    assert(T[3][5] == 1);
    assert(T[3][6] == 1);
    assert(T[3][7] == 1);
    assert(T[3][9] == 1);

    // Skrót 1→5
    assert(T[1][5] == 1);
    assert(T[1][6] == 1);
    assert(T[1][7] == 1);
    assert(T[1][8] == 1);
    assert(T[1][9] == 1);

    // Graf skierowany — brak krawędzi wstecznych
    assert(T[1][0] == 0);
    assert(T[2][0] == 0);
    assert(T[4][0] == 0);
    assert(T[9][0] == 0);
    assert(T[9][8] == 0);
    assert(T[5][3] == 0);
    assert(T[6][3] == 0);

    // Wierzchołek 9 jest liściem — nie osiąga nikogo poza sobą
    for (int j = 0; j < n; j++)
        if (j != 9) assert(T[9][j] == 0);

    // Wierzchołek 0 jest źródłem — osiąga wszystkich
    for (int j = 0; j < n; j++)
        assert(T[0][j] == 1);

    // Macierz domknięcia przechodniego
    std::cout << std::endl;
    std::cout << "Macierz domkniecia przechodniego T:" << std::endl;
    std::cout << "   ";
    for (int j = 0; j < n; j++)
    {
        std::cout << j << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << i << ": ";
        for (int j = 0; j < n; j++)
        {
            std::cout << T[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Wszystkie asserty przeszly pomyslnie." << std::endl;
    return 0;
}
