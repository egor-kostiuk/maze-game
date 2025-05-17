#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "constants/MainConstants.h"
#include "components/Maze.cpp"
#include <iostream>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML window");

  // Generate a maze
  MazeGenerator maze(rows, cols);
  maze.generateMaze();
  vector<vector<int>> generatedMaze = maze.getMaze();

  // Гравець
  sf::CircleShape player(cellSize / 3.0f);
  player.setFillColor(sf::Color::Blue);

  // Початкова позиція (центр клітинки [1][0])
  sf::Vector2f playerPosition(0 * cellSize + cellSize / 5.0f, 1 * cellSize + cellSize / 5.0f);
  player.setPosition(playerPosition);

  // move
  const float moveStep = cellSize;

  // Start the game loop
  while (window.isOpen())
  {
    // Process events
    while (const std::optional event = window.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
          window.close();
        }

        // Поточна позиція гравця
        sf::Vector2f pos = player.getPosition();
        int currentRow = static_cast<int>((pos.y + cellSize / 2) / cellSize);
        int currentCol = static_cast<int>((pos.x + cellSize / 2) / cellSize);

        // Обробка руху з колізіями
        switch (keyPressed->scancode) {
          case sf::Keyboard::Scancode::W: {
            int targetRow = currentRow - 1;
            if (targetRow >= 0 && generatedMaze[targetRow][currentCol] != 1)
              player.move(sf::Vector2f(0, -moveStep));
            break;
          }
          case sf::Keyboard::Scancode::S: {
            int targetRow = currentRow + 1;
            if (targetRow < rows && generatedMaze[targetRow][currentCol] != 1)
              player.move(sf::Vector2f(0, moveStep));
            break;
          }
          case sf::Keyboard::Scancode::A: {
            int targetCol = currentCol - 1;
            if (targetCol >= 0 && generatedMaze[currentRow][targetCol] != 1)
              player.move(sf::Vector2f(-moveStep, 0));
            break;
          }
          case sf::Keyboard::Scancode::D: {
            int targetCol = currentCol + 1;
            if (targetCol < cols && generatedMaze[currentRow][targetCol] != 1)
              player.move(sf::Vector2f(moveStep, 0));
            break;
          }
          default:
            break;
        }
      }

    }

    // Clear screen
    window.clear(sf::Color::White);

    int showMaze = 1;
    // Drawing a maze
    if ( showMaze == 1 ) {
      for (int i = 0; i < generatedMaze.size(); i++) {
        for (int j = 0; j < generatedMaze[i].size(); j++) {
          sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
          if (i == 1 && j == 0) {
            cell.setFillColor(sf::Color::Green);
          }
          else if (i == 16 && j == 30) {
            cell.setFillColor(sf::Color::Red);
          }
          else if (generatedMaze[i][j] == 1) {
            cell.setFillColor(sf::Color::Black);
          }
          else {
            cell.setFillColor(sf::Color::White);
          }
          cell.setPosition(sf::Vector2f(j * cellSize, i * cellSize));
          window.draw(cell);
        }
      }
    }

    // Display player
    window.draw(player);

    // Update the window
    window.display();
  }
}