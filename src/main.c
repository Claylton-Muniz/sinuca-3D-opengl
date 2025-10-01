#include <GL/glut.h>
#include <math.h>

#include "../include/sinuca.h"
#include "../include/input.h" 

#define M_PI 3.14159265358979323846

float yaw = 0.0f;   // rotação horizontal da câmera
float pitch = 0.3f; // inclinação vertical fixa
int lastX, lastY;
int width = 800, height = 450;

void init()
{
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {2.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat mat_diffuse[] = {0.2f, 0.6f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / height, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    // esconder cursor
    glutSetCursor(GLUT_CURSOR_NONE);

    // centralizar o mouse no início
    lastX = width / 2;
    lastY = height / 2;
    glutWarpPointer(lastX, lastY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float raio = 25.0f; // modificar para usar de zoom
    float camX = sin(yaw) * raio;
    float camZ = cos(yaw) * raio;
    float camY = 12.0f; // altura fixa

    gluLookAt(
        camX, camY, camZ, // posição da câmera
        0, 0, 0,          // olha pro centro
        0, 1, 0);

    desenhaMesa();
    desenhaBola();
    desenhaTaco();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sinuca 3D");

    init();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
