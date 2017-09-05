/*
 * HackerRank - Mr K marsh
 * https://www.hackerrank.com/challenges/mr-k-marsh
 * Author: Rafal Kozik
 */

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << std::endl

int create_index(
    std::vector<std::string>& grid, std::vector<std::vector<bool>>& visited,
    std::vector<std::vector<int>>& index, uint32_t i, int di, uint32_t j, int dj
) {
    if (i >= grid.size() || j >= grid[i].size() || grid[i][j] == 'x')
    {
        return 0;
    }
    visited[i][j] = true;
    auto measure = create_index(grid, visited, index, i + di, di, j + dj, dj);
    index[i][j] = measure;
    return measure + 1;
}

int main()
{
    int m, n;
    std::cin >> m >> n;
    std::vector<std::string> grid(m);
    std::vector<std::vector<bool>> h_visited(m, std::vector<bool>(n));
    std::vector<std::vector<bool>> v_visited(m, std::vector<bool>(n));
    std::vector<std::vector<int>> h_index(m, std::vector<int>(n));
    std::vector<std::vector<int>> v_index(m, std::vector<int>(n));
    for (int i = 0; i < m; ++i)
    {
        std::cin >> grid[i];
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!h_visited[i][j])
            {
                create_index(grid, h_visited, h_index, i, 0, j, 1);
            }
            if (!v_visited[i][j])
            {
                create_index(grid, v_visited, v_index, i, 1, j, 0);
            }
        }
    }
    int perimiter = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < h_index[i][j]; ++k)
            {
                int tl = j;
                int tr = j + k + 1;
                for (int l = std::min(v_index[i][tl], v_index[i][tr]); l > 0; --l)
                {
                    if (h_index[i + l][tl] >= tr - tl)
                    {
                        perimiter = std::max(perimiter, 2 * l + 2 * (k + 1));
                        break;
                    }
                }
            }
        }
    }
    if (perimiter > 0)
    {
        LOG(perimiter);
    }
    else
    {
        LOG("impossible");
    }
}

