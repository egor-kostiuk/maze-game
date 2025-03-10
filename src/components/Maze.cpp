#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

class MazeGenerator {
public:
  MazeGenerator(int rows, int cols) : rows(rows), cols(cols) {
    // Initialize the maze
    maze = vector<vector<int>>(rows, vector<int>(cols, 1));
    srand(time(0));
  }

  // Function for generating the maze
  void generateMaze() {
    generateMazeRecursively(0, 0);
  }

  // Function to get the maze
  vector<vector<int>> getMaze() {
    return maze;
  }

private:
  int rows, cols;
  vector<vector<int>> maze;

  // Directions for DFS (up, down, left, right)
  const int dx[4] = { -1, 1, 0, 0 };
  const int dy[4] = { 0, 0, -1, 1 };

  // Recursive maze generator function
  void generateMazeRecursively(int x, int y) {
    maze[x][y] = 0;

    // Shuffle directions for randomness
    vector<int> directions = { 0, 1, 2, 3 };

    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g);

    for (int i = 0; i < 4; ++i) {
      int newX = x + dx[directions[i]] * 2;
      int newY = y + dy[directions[i]] * 2;

      // Check if the new cell is within the maze
      if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] == 1) {
        maze[x + dx[directions[i]]][y + dy[directions[i]]] = 0;
        generateMazeRecursively(newX, newY);
      }
    }
  }
};
