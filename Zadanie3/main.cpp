#include <iostream>
#include <cassert>
//#include "edge.hpp"
//#include "basegraph.hpp"
#include "graph.hpp"
//#include "iterator.hpp"

int main()
{
    std::cout << "Graf nieskierowany" << std::endl;
    Graph g(5, false); // 5 wierzcholkow, nieskierowany

    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 0);
    g.add_edge(1, 3);

    assert(g.v() == 5);
    std::cout << "Liczba wierzcholkow: " << g.v() << std::endl; // 5
    assert(g.e() == 6);
    std::cout << "Liczba krawedzi: " << g.e() << std::endl;     // 6

    g.del_edge(1, 3);
    assert(g.e() == 5);
    std::cout << "Po usunieciu (1,3), liczba krawedzi: " << g.e() << std::endl; // 5

    g.del_node(0);
    assert(g.e() == 3);
    std::cout << "Po usunieciu wierzcholka 0, liczba krawedzi: " << g.e() << std::endl;//3

    g.display();




    std::cout << "Graf skierowany" << std::endl;
    Graph dg(4, true); // 4 wierzcholki, skierowany

    dg.add_edge(0, 1);
    dg.add_edge(1, 2);
    dg.add_edge(2, 3);
    dg.add_edge(3, 0);
    dg.add_edge(0, 2);

    assert(dg.e() == 5);
    std::cout << "Liczba krawedzi: " << dg.e() << std::endl; // 5

    assert(dg.outdegree(0) == 2);
    std::cout << "Outdegree wierzcholka 0: " << dg.outdegree(0) << std::endl; // 2
    assert(dg.indegree(0) == 1);
    std::cout << "Indegree wierzcholka 0: "  << dg.indegree(0)  << std::endl; // 1
    assert(dg.degree(0) == 3);
    std::cout << "Degree wierzcholka 0: "    << dg.degree(0)    << std::endl; // 3

    assert(dg.has_edge(0, 1) == 1);
    std::cout << "Krawedz (0,1): " << dg.has_edge(0, 1) << std::endl; // 1
    assert(dg.has_edge(1, 0) == 0);
    std::cout << "Krawedz (1,0): " << dg.has_edge(1, 0) << std::endl; // 0


    dg.display();
    dg.clear();

    std::cout<<std::endl;
    std::cout<<"Wszystkie testy zostaly zaliczone"<<std::endl;
    return 0;
}
