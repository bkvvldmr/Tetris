cmake_minimum_required(VERSION 3.29.6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tetris CXX)


find_package(Threads REQUIRED)
find_package(ftxui REQUIRED)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


set(SOURCE_FILES
    main.cpp
    grid.cpp
    game.cpp
    block.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(tetris
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
  PRIVATE  sfml-graphics
)