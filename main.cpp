//
//  main.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <iostream>


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // DRAW

    glutSwapBuffers();
}

/**
 *
 * @param key
 * @param x
 * @param y
 *
 * F1: Toggle wireframe mode on/off
 * n: Toggle normal visualisation on/off
 * q: Left cannon rotate up
 * Q: Left cannon rotate down
 * a: Left boat move left
 * d: Left boat move right
 * o: Right cannon rotate up
 * O: Right cannon rotate down
 * l: Right boat move leftj: Right boat move right
 * e: Left boat fire
 * i: Right boat fire
 * r: Left boat defence
 * y: Right boat defence
 * g: Toggle wave animation on/off
 * +: Double wave tesselation
 * -: Halve wave tesselation
 * q/Esc: Quit the program
 *
 */
void keyboard(unsigned char key, int x, int y) {
    std::cout << "Key : " << std::endl;
    switch (key) {
        case 27:
        case 'q':
            exit(EXIT_SUCCESS);
        default:
            break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Island Defense 2D");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return EXIT_SUCCESS;
}