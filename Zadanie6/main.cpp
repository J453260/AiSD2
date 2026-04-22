#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include "topsort.hpp"

int main()
{
    std::unordered_map<int, std::vector<int>> graph =
    {
        {0, {1, 2}},
        {1, {3, 4}},
        {2, {5}},
        {3, {6}},
        {4, {6, 7}},
        {5, {7}},
        {6, {8}},
        {7, {8, 9}},
        {8, {}},
        {9, {}}
    };

    // wywołanie sortowania topologicznego
    std::vector<int> result = topsort_dfs<int>(graph);

    // wypisanie wyniku
    std::cout << "Sortowanie topologiczne:\n";
    for (int v : result)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;


    std::unordered_map<int, int> position;
    for (int i = 0; i < result.size(); i++)
    {
        position[result[i]] = i;
    }

    assert(result.size() == graph.size());

    for (const auto& [u, neighbors] : graph)
    {
        for (int v : neighbors)
        {
            // u musi być przed v
            assert(position[u] < position[v]);
        }
    }

    std::cout << std::endl;

    std::cout << "Wszystkie testy przeszly poprawnie"<<std::endl;

    return 0;
}
