cmake_minimum_required(VERSION 2.8)
project(IslandDefense)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
add_executable(IslandDefense
        main.cpp

        srcs/Game.cpp
        srcs/includes/Game.hpp
        srcs/Island.cpp
        srcs/includes/Island.hpp
        srcs/Boat.cpp
        srcs/includes/Boat.hpp
        srcs/includes/Waves.hpp
        srcs/Waves.cpp
        srcs/helpers/Displayable.hpp
        srcs/helpers/Shape.hpp
        srcs/helpers/Entity.hpp
        srcs/helpers/Movable.hpp
        srcs/helpers/Axes.hpp
        srcs/helpers/Glut.hpp
        srcs/helpers/Color.hpp 
        srcs/Stats.cpp 
        srcs/includes/Stats.hpp 
        srcs/Projectile.cpp 
        srcs/includes/Projectile.hpp 
        srcs/Cannon.cpp 
        srcs/includes/Cannon.hpp 
        srcs/helpers/Alive.hpp 
        srcs/UI.cpp 
        srcs/includes/UI.hpp 
        srcs/Pellet.cpp 
        srcs/includes/Pellet.hpp 
        srcs/includes/Entities.hpp 
        srcs/Shape.cpp 
        srcs/Displayable.cpp 
        srcs/Movable.cpp 
        srcs/includes/Config.hpp 
        srcs/helpers/DefeatScreen.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(IslandDefense ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})