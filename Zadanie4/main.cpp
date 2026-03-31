#include <iostream>
#include <cassert>
#include "graph.hpp"

int main()
{
    Graph g(5, false);

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    g.display();

    assert(g.has_edge(0, 1) == 1);
    std::cout << "has_edge(0,1): " << g.has_edge(0, 1) << std::endl; // 1
    assert(g.has_edge(0, 4) == 0);
    std::cout << "has_edge(0,4): " << g.has_edge(0, 4) << std::endl; // 0

    assert(g.degree(3) == 3);
    std::cout << "degree(3):    " << g.degree(3)    << std::endl; // 3
    assert(g.indegree(3) == 3);
    std::cout << "indegree(3):  " << g.indegree(3)  << std::endl; // 3
    assert(g.outdegree(3) == 3);
    std::cout << "outdegree(3): " << g.outdegree(3) << std::endl; // 3



    std::cout << "Sasiedzi 0: ";
    for (auto it = g.adj_begin(0); it != g.adj_end(0); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;



    std::cout << "Krawedzie: ";
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
    {
        std::cout << "(" << (*it).source << "," << (*it).target << ") ";
    }
    std::cout << std::endl;


    g.del_edge(0, 1);
    std::cout << "Po usunieciu (0,1): " << std::endl;
    g.display();

    std::cout << std::endl;
    std::cout<<"Wszystkie testy przeszly";
    return 0;
}
