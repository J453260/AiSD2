#ifndef BORUVKA_HPP
#define BORUVKA_HPP

#include <vector>
#include <tuple>
#include <limits>
#include <set>
#include "graph.hpp"


struct UnionFind
{
    std::vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool unite(int x, int y)
    {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
};


std::vector<std::tuple<float, int, int>> BoruvkaMST(Graph& g)
{
    const int n = g.v();
    const double infinity = std::numeric_limits<double>::infinity();
    UnionFind uf(n);
    std::vector<std::tuple<float, int, int>> T;

    std::set<int> forest;
    for (int i = 0; i < n; i++)
    {
        forest.insert(i);
    }

    int new_len = forest.size();
    int old_len = new_len + 1;

    while(old_len > new_len)
    {
        old_len = new_len;
        std::vector<std::tuple<double, double, double>> MinEdge(n, {infinity, -1, -1});

        for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
        {
            Edge<int> e = *it;
            int s  = e.source;
            int t  = e.target;
            float w = e.weight;

            int s2 = uf.find(s);
            int t2 = uf.find(t);

            if (s2 != t2)
            {
                if (w < std::get<0>(MinEdge[s2]))
                {
                    MinEdge[s2] = {w, s, t};
                }

                if (w < std::get<0>(MinEdge[t2]))
                {
                    MinEdge[t2] = {w, s, t};
                }
            }
        }


        for (int u : forest)
        {
            auto [edge_weight, s, t] = MinEdge[u];

            if (edge_weight == infinity)  // graf niespójny
            {
                continue;
            }

            int s2 = uf.find(s);
            int t2 = uf.find(t);

            if (s2 != t2)
            {
                uf.unite(s, t);
                T.push_back({edge_weight, s, t});
            }
        }

        std::set<int> new_forest;
        for (int v : forest)
        {
            new_forest.insert(uf.find(v));
        }
        forest = new_forest;

        new_len = forest.size();

        if (new_len == 1)
        {
            break;
        }
    }

    return T;
}

#endif // BORUVKA_HPP
