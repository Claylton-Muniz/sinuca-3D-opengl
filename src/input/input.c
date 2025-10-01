#include <GL/glut.h>
#include <stdio.h>

#include "../../include/input.h"

void mouseMotion(int x, int y)
{
    static int lastX = 400, lastY = 225;

    if (x == width / 2 && y == height / 2)
    {
        // gambiarra para o teleporte do mouse
        // não bugar o movimento da cam
        return;
    }

    int dx = x - lastX;
    int dy = y - lastY;

    float sensibilidade = 0.005f;

    yaw += dx * sensibilidade;
    pitch += dy * sensibilidade;

    if (pitch > 1.0f)
        pitch = 1.0f;
    if (pitch < -0.2f)
        pitch = -0.2f;

    // re-centraliza
    glutWarpPointer(width / 2, height / 2);
    lastX = width / 2;
    lastY = height / 2;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        isTacada = 1;
        glutTimerFunc(0, atualiza, 0);
    }
}