#ifndef MNOZENIEMACIERZY_H
#define MNOZENIEMACIERZY_H

#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>

std::vector<std::vector<int>> multiply(const std::vector<std::vector<int>>& A,
                                       const std::vector<std::vector<int>>& B)
{
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

std::vector<std::vector<int>> ExtendedShortestPaths(
    const std::vector<std::vector<int>>& L,
    const std::vector<std::vector<int>>& W)
{
    int n = L.size();
    const int INF = 1e9;

    std::vector<std::vector<int>> newL(n, std::vector<int>(n, INF));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (L[i][k] < INF && W[k][j] < INF)
                {
                    newL[i][j] = std::min(newL[i][j],
                                          L[i][k] + W[k][j]);
                }
            }
        }
    }

    return newL;
}

std::vector<std::vector<int>> SlowAllPairsShortestPaths(
    const std::vector<std::vector<int>>& W)
{
    int n = W.size();

    std::vector<std::vector<int>> L = W;

    for (int m = 2; m <= n - 1; m++)
    {
        L = ExtendedShortestPaths(L, W);
    }

    // wykrywanie cykli ujemnych
    for (int i = 0; i < n; i++)
    {
        if (L[i][i] < 0)
        {
            throw std::runtime_error("negative cycle detected");
        }
    }

    return L;
}

#endif // MNOZENIEMACIERZY_H
