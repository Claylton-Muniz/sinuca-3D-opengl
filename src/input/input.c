#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "../../include/input.h"

float forca = 40.0f;

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
        // direção olhando da câmera para a bola
        float dirX = -sin(yaw);
        float dirZ = -cos(yaw);

        // velocidade inicial
        if (bolaVX == 0 && bolaVZ == 0)
        {
            bolaVX = dirX * forca;
            bolaVZ = dirZ * forca;
            isTacada = 1;
            cameraAtual = 0;
            glutTimerFunc(0, atualiza, 0);
        }
    }
}

void teclado(unsigned char key, int x, int y)
{
    if (key == 'c' || key == 'C')
    {
        cameraAtual = 1 - cameraAtual; // alterna entre 0 e 1
        glutPostRedisplay();
    }
    if (key == 'w' || key == 'W')
    {
        bolaX += 0.3f;
        glutPostRedisplay();
    }
    if (key == 's' || key == 'S')
    {
        bolaX -= 0.3f;
        glutPostRedisplay();
    }
    if (key == 'a' || key == 'A')
    {
        bolaZ -= 0.3f;
        glutPostRedisplay();
    }
    if (key == 'd' || key == 'D')
    {
        bolaZ += 0.3f;
        glutPostRedisplay();
    }
    if (key == 'f' || key == 'F')
    {
        printf("bX: %f bZ: %f\n", bolaX, bolaZ);
    }
    if (key == 'p' || key == 'P')
    {
        bolaVX = 0;
        bolaVZ = 0;
    }
    if (key == '1')
    {
        forca = 10.0f;
    }
    if (key == '2')
    {
        forca = 25.0f;
    }
    if (key == '3')
    {
        forca = 40.0f;
    }
    if (key == '4')
    {
        forca = 70.0f;
    }
    if (key == 'r' || key == 'R')
    {
        // Posições iniciais das bolas
        bolaX = 0.0f;
        bolaY = 0.9f;
        bolaZ = -10.0f;

        // Posição inicial da bola 2
        bola2X = 0.5f; // Modificado para não sobrepor
        bola2Y = 0.9f;
        bola2Z = 8.75f;

        // Posição inicial da bola 3
        bola3X = -0.5f;
        bola3Y = 0.9f;
        bola3Z = 8.75f;

        // Posição inicial da bola 4
        bola4X = 0.0f;
        bola4Y = 0.9f;
        bola4Z = 8.1f;
    }
}
