# Copyright (c) 2018-2019 Andrei Krylov 
# Distributed under the GNU AGPLv3 software license, see the accompanying
# file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

# Command call:
# cmake -G <generator>
#       -DCMAKE_BUILD_TYPE:STRING=<build_type> 
#       -DSFML_DIR:PATH="<path_to_the_SFMLConfig>" ..
# Example:
# cmake -G "Visual Studio 15 2017 Win64"
#	    -DCMAKE_BUILD_TYPE:STRING="Debug"
#	    -DSFML_DIR:PATH="D:/vcpkg/installed/x64-windows/share/sfml" ..
# On Linux and MacOS if you use default location - 3rd parameter can be ignored.

cmake_minimum_required(VERSION 3.1 FATAL_ERROR) 

project(Snake2D VERSION 0.8.0 LANGUAGES CXX)

set(CMAKE_CXX_STARDARD 14)

find_package(SFML 2.5.1 REQUIRED 
  COMPONENTS system window graphics
  PATHS "${SFML_DIR}"
)

get_filename_component(PROJECT_BASE ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
configure_file(
  "${PROJECT_BASE}/Snake2D/src/common/Version.h.in" 
  "${PROJECT_BASE}/Snake2D/src/common/Version.h"
)
set(SNAKE2D_SOURCES 
  "Snake2D/main.cpp"
  "Snake2D/common/Common.cpp"
  "Snake2D/common/Parameters.cpp"
  "Snake2D/common/Point2D.cpp"
  "Snake2D/common/Random.cpp"
  "Snake2D/common/Rect2D.cpp"
  "Snake2D/core/AboutController.cpp"
  "Snake2D/core/BoardModel.cpp"
  "Snake2D/core/EndgameController.cpp"
  "Snake2D/core/FoodModel.cpp"
  "Snake2D/core/GameController.cpp"
  "Snake2D/core/GameManager.cpp"
  "Snake2D/core/GameWindow.cpp"
  "Snake2D/core/InputHandler.cpp"
  "Snake2D/core/MainMenuController.cpp"
  "Snake2D/core/MainMenuItemModel.cpp"
  "Snake2D/core/MainMenuModel.cpp"
  "Snake2D/core/ScoreboardModel.cpp"
  "Snake2D/core/SnakeModel.cpp"
)

add_executable(${PROJECT_NAME} ${SNAKE2D_SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window)
