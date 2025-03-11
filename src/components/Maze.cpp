#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

class MazeGenerator {
public:
  MazeGenerator(int rows, int cols) : rows(rows + 2), cols(cols + 2) {
    // Initialize the maze
    maze = vector<vector<int>>(this->rows, vector<int>(this->cols, 1));
    random_device rd;
    rng = mt19937(rd());
  }

  // Function for generating the maze
  void generateMaze() {
    generateMazeRecursively(1, 1);
    addBordersAndExit();
  }

  // Function to get the maze
  vector<vector<int>> getMaze() {
    return maze;
  }

private:
  int rows, cols;
  vector<vector<int>> maze;
  mt19937 rng;

  // Directions for DFS (up, down, left, right)
  const int dx[4] = {-1, 1, 0, 0};
  const int dy[4] = {0, 0, -1, 1};

  // Recursive maze generator function
  void generateMazeRecursively(int x, int y) {
    maze[x][y] = 0;

    // Shuffle directions for randomness
    vector<int> directions = {0, 1, 2, 3};
    shuffle(directions.begin(), directions.end(), rng);

    for (int i = 0; i < 4; ++i) {
      int newX = x + dx[directions[i]] * 2;
      int newY = y + dy[directions[i]] * 2;

      if (newX > 0 && newX < rows - 1 && newY > 0 && newY < cols - 1 && maze[newX][newY] == 1) {
        maze[x + dx[directions[i]]][y + dy[directions[i]]] = 0;
        generateMazeRecursively(newX, newY);
      }
    }
  }

  void addBordersAndExit() {
    // Walls around the maze
    for (int i = 0; i < rows; ++i) {
      maze[i][0] = maze[i][cols - 1] = 1;
    }
    for (int j = 0; j < cols; ++j) {
      maze[0][j] = maze[rows - 1][j] = 1;
    }

    // Start (1,0)
    maze[1][0] = 0;

    // End
    vector<int> possibleExits;
    for (int i = 1; i < rows - 1; i++) {
      if (maze[i][cols - 2] == 0 && maze[i][cols - 3] == 0) {
        possibleExits.push_back(i);
      }
    }

    if (!possibleExits.empty()) {
      random_device rd;
      mt19937 rng(rd());
      uniform_int_distribution<int> dist(0, possibleExits.size() - 1);
      int exitRow = possibleExits[dist(rng)];
      maze[exitRow][cols - 1] = 0;
    } else {
      int forcedExitRow = rows / 2;
      maze[forcedExitRow][cols - 3] = 0;
      maze[forcedExitRow][cols - 2] = 0;
      maze[forcedExitRow][cols - 1] = 0;
    }
  }

};
