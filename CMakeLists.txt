cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

set(SFML_STATIC_LIBRARIES TRUE)

add_executable(minesweeper
        Toolbox.cpp
        Toolbox.h
        Button.cpp
        Button.h
        Tile.cpp
        Tile.h
        GameState.cpp
        GameState.h
        minesweeper.cpp
        minesweeper.h)
target_link_libraries(minesweeper sfml-graphics sfml-window)