cmake_minimum_required(VERSION 3.10)

project(MySFMLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.7")

# Вказуємо точні шляхи до заголовкових файлів SFML
include_directories("/usr/local/Cellar/sfml/3.0.0_1/include")
set(CMAKE_OSX_ARCHITECTURES "x86_64")  # Використовуємо x86_64 для Intel Mac

# Додаємо вихідний файл
add_executable(MySFMLProject src/Game.cpp) # всі модулі

# Линкуємо бібліотеки SFML
target_link_libraries(MySFMLProject
    /usr/local/Cellar/sfml/3.0.0_1/lib/libsfml-window.dylib
    /usr/local/Cellar/sfml/3.0.0_1/lib/libsfml-system.dylib
    /usr/local/Cellar/sfml/3.0.0_1/lib/libsfml-graphics.dylib
    /usr/local/Cellar/sfml/3.0.0_1/lib/libsfml-audio.dylib
)
