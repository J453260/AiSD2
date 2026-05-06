#include <iostream>
#include <cassert>
#include <vector>
#include "MnozenieMacierzy.hpp"
#include "graph.hpp"

int main()
{
    const int n = 10;
    const int INF = 1e9;

    Graph g(n, true);

    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 1);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 3, 5);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 5, 2);
    g.add_edge(5, 6, 1);
    g.add_edge(6, 7, 7);
    g.add_edge(7, 8, 1);
    g.add_edge(8, 9, 2);
    g.add_edge(1, 9, 20);
    g.add_edge(2, 8, 10);

    std::vector<std::vector<int>> W(n, std::vector<int>(n, INF));

    for (int i = 0; i < n; i++)
    {
        W[i][i] = 0;

        for (int j = 0; j < n; j++)
        {
            if (g.has_edge(i, j))
            {
                W[i][j] = static_cast<int>(g.weight(i, j));
            }
        }
    }

    assert(W.size() == n);
    for (const auto& row : W)
    {
        assert(row.size() == n);
    }

    std::vector<std::vector<int>> dist = SlowAllPairsShortestPaths(W);

    assert(dist.size() == n);
    for (const auto& row : dist)
    {
        assert(row.size() == n);
    }

    std::cout << "Macierz najkrotszych odleglosci:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(dist[i][j] >= INF)
            {
                std::cout << "INF ";
            }
            else
            {
                if(dist[i][j] >= 0 && dist[i][j] <= 9)
                {
                    std::cout << dist[i][j] << "   ";
                }

                if(dist[i][j] >= 10)
                {
                    std::cout << dist[i][j] << "  ";
                }
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Wszystkie testy przeszly poprawnie." << std::endl;

    return 0;
}
