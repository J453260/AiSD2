#ifndef TRANSITIVECLOSURE
#define TRANSITIVECLOSURE

std::vector<std::vector<int>> transitive_closure(int n, const std::vector<std::pair<int,int>>& edges)
{
    std::vector<std::vector<int>> T(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        T[i][i] = 1;
    }

    for (auto& [i, j] : edges)
    {
        T[i][j] = 1;
    }

    // T^(k): czy istnieje ścieżka z i do j przez wierzchołki {0..k}
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
            }
        }
    }

    return T;
}

#endif // TRANSITIVECLOSURE
