cmake_minimum_required(VERSION 3.5)
project(IslandDefense)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
add_executable(IslandDefense
        main.cpp srcs/Game.cpp srcs/Island.cpp srcs/helpers/Game.hpp srcs/helpers/Displayable.hpp srcs/helpers/Island.hpp srcs/helpers/Entity.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(IslandDefense ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})