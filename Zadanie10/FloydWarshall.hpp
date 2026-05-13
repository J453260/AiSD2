#ifndef FLOYDWARSHALL_HPP
#define FLOYDWARSHALL_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <tuple>
#include <algorithm>

constexpr double INF = std::numeric_limits<double>::infinity();

struct FloydWarshallResult
{
    std::vector<std::vector<double>> D;
    std::vector<std::vector<int>>    Parent;
    bool has_negative_cycle = false;
};

// Buduje macierz D^(0) z listy krawędzi
std::vector<std::vector<double>> make_weight_matrix(
                                  int n,
                                  const std::vector<std::tuple<int,int,double>>& edges)
{
    std::vector<std::vector<double>> W(n, std::vector<double>(n, INF));
    for (int i = 0; i < n; i++)
    {
        W[i][i] = 0.0;
    }
    for (auto& [i, j, w] : edges)
    {
        W[i][j] = w;
    }
    return W;
}

FloydWarshallResult floyd_warshall(
    int n,
    const std::vector<std::vector<double>>& Weight)
{
    FloydWarshallResult result;
    auto& D      = result.D;
    auto& Parent = result.Parent;

    // D^(0) = Weight
    D      = Weight;
    Parent.assign(n, std::vector<int>(n, -1));

    // Inicjalizacja Parent dla istniejących krawędzi
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && D[i][j] != INF)
                Parent[i][j] = i;

    // Główna pętla: k = 1..n  (indeksy 0-based: 0..n-1)
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (D[i][k] != INF && D[k][j] != INF)
                    if (D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j]      = D[i][k] + D[k][j];
                        Parent[i][j] = Parent[k][j];
                    }

    // Wykrywanie ujemnych cykli
    for (int i = 0; i < n; i++)
        if (D[i][i] < 0)
        {
            result.has_negative_cycle = true;
            break;
        }

    return result;
}

std::vector<int> print_shortest_path(
    const std::vector<std::vector<double>>& D,
    const std::vector<std::vector<int>>&    Parent,
    int s, int t)
{
    if (D[s][t] == INF)
        return {};   // brak ścieżki

    std::vector<int> path;
    path.push_back(t);
    int current = t;
    while (Parent[s][current] != -1 && Parent[s][current] != s)
    {
        current = Parent[s][current];
        path.push_back(current);
    }
    path.push_back(s);
    std::reverse(path.begin(), path.end());
    return path;
}

#endif
