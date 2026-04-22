// connected.hpp
#ifndef CONNECTED_HPP
#define CONNECTED_HPP

#include <unordered_map>
#include <cassert>

template<typename T, typename G>
class ConnectedComponents
{
    G& graph;
    std::unordered_map<T, bool> visited;

public:
    std::unordered_map<T, int> component;
    int ncc;

    ConnectedComponents(G& g) : graph(g), ncc(0)
    {
        assert(!graph.is_directed());
        for (auto n_it = graph.node_begin();
             n_it != graph.node_end();
             ++n_it)
        {
            visited[n_it->first] = false;
        }
    }

    void run()
    {
        for (auto n_it = graph.node_begin();
             n_it != graph.node_end();
             ++n_it)
        {
            T u = n_it->first;

            if (!visited[u])
            {
                visit(u);
                ncc++;
            }
        }
    }

    void visit(T u)
    {
        visited[u] = true;
        component[u] = ncc;

        for (auto v : graph.neighbors(u))
        {
            if (!visited[v])
            {
                visit(v);
            }
        }
    }
};

#endif
// Usage:
// auto algorithm = ConnectedComponents<int,Graph>(G); // macierz sąsiedztwa
// auto algorithm = ConnectedComponents<char,Graph<char>>(G); // lista sąsiedztwa
// algorithm.run();
// for (auto pair : algorithm.component)
//     std::cout << pair.first << " component " << pair.second << std::endl;
// std::cout << "total components " << algorithm.ncc << std::endl;
