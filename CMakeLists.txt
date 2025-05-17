cmake_minimum_required(VERSION 3.10)

project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Налаштування для macOS
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.7")
set(CMAKE_OSX_ARCHITECTURES "x86_64")  # або arm64 для Apple Silicon

# Вказуємо шлях до заголовочних файлів SFML
include_directories(
    /Users/x/Desktop/projects/SFML/build/install/include
)

# Вказуємо шлях до бібліотек SFML
link_directories(
    /Users/x/Desktop/projects/SFML/build/install/lib
)

# Додаємо головний файл
add_executable(MySFMLProject
    src/Game.cpp
    src/components/Maze.cpp
    src/components/PathFinder.cpp
    src/constants/MainConstants.h
)

# Лінкуємо SFML
target_link_libraries(MySFMLProject
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
)
