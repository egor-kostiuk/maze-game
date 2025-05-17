#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "constants/MainConstants.h"
#include "components/Maze.cpp"
#include "components/PathFinder.cpp"
#include <iostream>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML window");

  // Generate a maze
  MazeGenerator maze(rows, cols);
  maze.generateMaze();
  vector<vector<int>> generatedMaze = maze.getMaze();

  // Find path
  bool showPath = false;
  std::vector<std::pair<int,int>> pathToExit;
  pathToExit = PathFinder::bfsFindPath(generatedMaze, 1, 0);

  // Player size
  sf::CircleShape player(cellSize / 3.0f);
  player.setFillColor(sf::Color::Blue);

  // Start
  sf::Vector2f playerPosition(0 * cellSize + cellSize / 5.0f, 1 * cellSize + cellSize / 5.0f);
  player.setPosition(playerPosition);

  // Step size
  const float moveStep = cellSize;

  // Modal window winner
  bool showCongrats = false;

  // Font
  sf::Font font;
	if (!font.openFromFile("../assets/fonts/OpenSans-Italic.ttf")) {
      std::cerr << "Failed to load font!\n";
	}

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

        if (showCongrats) {
          break;
    	}

        if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
    	  if (showPath) {
        	showPath = false;
          } else {
        	pathToExit = PathFinder::bfsFindPath(generatedMaze, 1, 0);
        	showPath = true;
          }
        }

        // Player position
        sf::Vector2f pos = player.getPosition();
        int currentRow = static_cast<int>((pos.y + cellSize / 2) / cellSize);
        int currentCol = static_cast<int>((pos.x + cellSize / 2) / cellSize);

        // Сollisions and movement
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
            if (currentRow == 16 && currentCol == 29) {
              showCongrats = true;
              sf::Vector2f playerPosition(30 * cellSize + cellSize / 5.0f, 16 * cellSize + cellSize / 5.0f);
  			  player.setPosition(playerPosition);
              break;
    		}
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

    // Show path
    if (showPath) {
	  for (const auto& cell : pathToExit) {
  	  sf::RectangleShape pathCell(sf::Vector2f(cellSize, cellSize));
      pathCell.setFillColor(sf::Color::Green);
      pathCell.setPosition(sf::Vector2f(cell.second * cellSize, cell.first * cellSize));
      window.draw(pathCell);
      }
	}

    // Winner modal window
    if (showCongrats) {
      // Size
      sf::Vector2f size(250, 100);
      sf::Vector2f position(WINDOW_WIDTH / 2 - size.x / 2, WINDOW_HEIGHT / 2 - size.y / 2);

      // Border
      sf::RectangleShape border(size + sf::Vector2f(10, 10));
      border.setFillColor(sf::Color(192, 192, 192));
      border.setPosition(position - sf::Vector2f(5, 5));

      // Main block
      sf::RectangleShape popup(size);
      popup.setFillColor(sf::Color::White);
      popup.setPosition(position);

      // Text
      sf::Text text(font);
      text.setString("Congratulations!");
      text.setCharacterSize(20);
      text.setFillColor(sf::Color::Black);
      text.setStyle(sf::Text::Bold);
      text.setPosition({position.x + 30, position.y + 35});

      // Draw items
      window.draw(border);
      window.draw(popup);
      window.draw(text);
    }

    // Display player
    window.draw(player);

    // Update the window
    window.display();
  }
}