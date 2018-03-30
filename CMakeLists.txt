cmake_minimum_required(VERSION 3.5)
project(IslandDefense)

set(CMAKE_CXX_STANDARD 17)
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
        srcs/helpers/DisplayableShape.hpp
        srcs/helpers/Entity.hpp
        srcs/helpers/Movable.hpp
        srcs/helpers/Axes.hpp
        srcs/helpers/OpenGL.hpp
        srcs/helpers/Glut.hpp
        srcs/helpers/Color.hpp srcs/Stats.cpp srcs/includes/Stats.hpp srcs/Projectile.cpp srcs/includes/Projectile.hpp srcs/Cannon.cpp srcs/includes/Cannon.hpp srcs/helpers/Alive.hpp srcs/UI.cpp srcs/includes/UI.hpp srcs/Projectiles.cpp srcs/includes/Projectiles.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(IslandDefense ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})