#pragma once
#include <vector>
#include <queue>
#include <algorithm>

class PathFinder {
public:
  static std::vector<std::pair<int, int>> bfsFindPath(const std::vector<std::vector<int>>& maze, int startRow, int startCol) {
    int rows = maze.size();
    int cols = maze[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

    std::queue<std::pair<int, int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    std::pair<int, int> endCell = {-1, -1};

    while (!q.empty()) {
      auto [r, c] = q.front(); q.pop();

      if (c == cols - 1 && maze[r][c] == 0) {
        endCell = {r, c};
        break;
      }

      for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
            !visited[nr][nc] && maze[nr][nc] == 0) {
          visited[nr][nc] = true;
          parent[nr][nc] = {r, c};
          q.push({nr, nc});
            }
      }
    }

    std::vector<std::pair<int, int>> path;
    if (endCell.first != -1) {
      for (auto at = endCell; at != std::make_pair(-1, -1); at = parent[at.first][at.second]) {
        path.push_back(at);
      }
      std::reverse(path.begin(), path.end());
    }

    return path;
  }
};