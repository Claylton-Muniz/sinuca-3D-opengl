#include <GL/glut.h>
#include <math.h>

#include "../../include/fisica.h"

void atualiza()
{
    // atualiza posição da bola pela velocidade
    bolaX += bolaVX;
    bolaZ += bolaVZ;

    // atrito para desacelerar
    bolaVX *= atrito;
    bolaVZ *= atrito;

    // se a velocidade ficar muito pequena, para a bola
    if (fabs(bolaVX) < 0.001f) bolaVX = 0;
    if (fabs(bolaVZ) < 0.001f) bolaVZ = 0;

    glutPostRedisplay();
    glutTimerFunc(16, atualiza, 0); // ~60 FPS
}