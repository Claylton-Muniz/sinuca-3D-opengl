#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "../../include/fisica.h"

float cacapas[6][2] = {
    {7.5f, -13.6f},
    {-7.7f, -13.8f},
    {-8.2f, -0.05f},
    {-7.5f, 13.7f},
    {7.7f, 13.6f},
    {8.2f, -0.05f}};

int bolaEmCacapa()
{
    float raioCacapa = 0.4f; // raio de captura
    for (int i = 0; i < 6; i++)
    {
        float dx = bolaX - cacapas[i][0];
        float dz = bolaZ - cacapas[i][1];
        float dist = sqrt(dx * dx + dz * dz);
        if (dist < raioCacapa)
            return 1;
    }
    return 0;
}

void atualiza()
{
    // atualiza posição da bola pela velocidade
    float dt = 0.016f; // ~16 ms se você mantiver fixo em 60 FPS
    bolaX += bolaVX * dt;
    bolaZ += bolaVZ * dt;

    // atrito para desacelerar
    float atrito = 0.98f;           // mais próximo de 1, mais realista
    bolaVX *= pow(atrito, dt * 60); // suaviza baseado no tempo
    bolaVZ *= pow(atrito, dt * 60);

    // se a velocidade ficar muito pequena, para a bola
    if (fabs(bolaVX) < 0.001f)
        bolaVX = 0;
    if (fabs(bolaVZ) < 0.001f)
        bolaVZ = 0;

    // Checar caçapa
    if (bolaEmCacapa())
    {
        printf("Bola encaçapada!\n");
        bolaVX = bolaVZ = 0;
        // bolão
        bolaX = 0.0f;
        bolaZ = -10.0f;
        glutPostRedisplay();
        return;
    }

    glutPostRedisplay();
    if (fabs(bolaVX) > 0.001f || fabs(bolaVZ) > 0.001f)
        glutTimerFunc(16, atualiza, 0); // ~60 FPS

    // Limites da mesa considerando raio da bola
    float minX = -8.0f + 0.4f;
    float maxX = 8.0f - 0.4f;
    float minZ = -14.0f + 0.4f;
    float maxZ = 14.0f - 0.4f;

    // Checar colisão com paredes laterais (X)
    if (bolaZ < -0.11f || bolaZ > 0.18f)
    {
        if (bolaX < minX)
        {
            bolaX = minX; // reposiciona para dentro
            printf("Colisão na tabela da esquerda!\n");
            bolaVX = -bolaVX; // depois você pode rebater
        }
        if (bolaX > maxX)
        {
            bolaX = maxX;
            printf("Colisão na tabela da direita!\n");
            bolaVX = -bolaVX;
        }

        // Checar colisão com paredes frontais (Z)
        if (bolaZ < minZ)
        {
            bolaZ = minZ;
            printf("Colisão na tabela inferior!\n");
            bolaVZ = -bolaVZ;
        }
        if (bolaZ > maxZ)
        {
            bolaZ = maxZ;
            printf("Colisão na tabela superior!\n");
            bolaVZ = -bolaVZ;
        }
    }
}