cmake_minimum_required(VERSION 3.10)
project(tetris)

# Nastav standard pro C
set(CMAKE_C_STANDARD 99)

# Najdi knihovny SDL2 a SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Definuj spustitelný soubor, který se nachází ve složce src
add_executable(tetris src/tetris.c src/funkce.c)

# Změňme způsob připojení knihoven k cíli, přidejme běžný název SDL2_ttf
target_link_libraries(tetris SDL2::SDL2 SDL2_ttf)
