#include <SFML/Graphics.hpp>
#include "constants/MainConstants.h"
#include "components/Maze.cpp"

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML window");

  // Generate a maze
  MazeGenerator maze(rows, cols);
  maze.generateMaze();
  vector<vector<int>> generatedMaze = maze.getMaze();

  // Start the game loop
  while (window.isOpen())
  {
    // Process events
    while (const std::optional event = window.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // Clear screen
    window.clear(sf::Color::White);

    int showMaze = 1;
    // Drawing a maze
    if ( showMaze == 1 ) {
      for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= cols; j++) {
          if (generatedMaze[i][j] == 1) {
            sf::RectangleShape wall(sf::Vector2f(cellSize, cellSize));
            wall.setFillColor(sf::Color::Black);
            wall.setPosition(sf::Vector2f(j * cellSize, i * cellSize));
            window.draw(wall);
          }
        }
      }
    }

    // Update the window
    window.display();
  }
}