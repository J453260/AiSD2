#ifndef TOPSORT_HPP
#define TOPSORT_HPP

#include <vector>
#include <stack>
#include <unordered_map>

template<typename T, typename G>
void dfs_visit(const T& u,
               G& graph,
               std::unordered_map<T, bool>& visited,
               std::stack<T>& st)
{
    visited[u] = true;

    for (const T& v : graph[u]) {
        if (!visited[v]) {
            dfs_visit(v, graph, visited, st);
        }
    }
  
    st.push(u);
}

template<typename T, typename G>
std::vector<T> topsort_dfs(G& graph)
{
    std::unordered_map<T, bool> visited;
    std::stack<T> st;

    // inicjalizacja visited
    for (const auto& [u, _] : graph) {
        visited[u] = false;
    }

    // DFS dla wszystkich wierzchołków
    for (const auto& [u, _] : graph) {
        if (!visited[u]) {
            dfs_visit(u, graph, visited, st);
        }
    }

    // budowanie wyniku (odwrócenie przez stos)
    std::vector<T> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

#endif // TOPSORT_HPP
