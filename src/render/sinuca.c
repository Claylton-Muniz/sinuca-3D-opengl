#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "../../include/sinuca.h"

#define M_PI 3.14159265358979323846

float t = 0;

void desenhaMesa()
{
    // --- Mesa (base verde) ---
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(16.0f, 0.5f, 28.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas laterais (em Z+) ---
    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(0.0f, 0.6f, 14.0f);
    glScalef(14.0f, 0.7f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas laterais (em Z-) ---
    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(0.0f, 0.6f, -14.0f);
    glScalef(14.0f, 0.7f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas frontais (em X+) ---
    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(8.0f, 0.6f, -6.8f);
    glScalef(0.5f, 0.7f, 12.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(8.0f, 0.6f, 6.8f);
    glScalef(0.5f, 0.7f, 12.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas frontais (em X-) ---
    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(-8.0f, 0.6f, -6.8f);
    glScalef(0.5f, 0.7f, 12.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f);
    glTranslatef(-8.0f, 0.6f, 6.8f);
    glScalef(0.5f, 0.7f, 12.5f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaBola()
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.9f, 10.0f);
    glutSolidSphere(0.4f, 50, 50);
    glPopMatrix();
}

void desenhaTaco(float camX, float camY, float camZ, float alvoX, float alvoY, float alvoZ)
{
    // Direção da câmera → alvo
    float dirX = alvoX - camX;
    float dirY = alvoY - camY;
    float dirZ = alvoZ - camZ;

    float len = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    dirX /= len;
    dirY /= len;
    dirZ /= len;

    // Posição do taco
    float tacoX = camX + dirX * 2.0f;
    float tacoY = camY + dirY * 2.0f - 2.0f;
    float tacoZ = camZ + dirZ * 2.0f;

    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);
    glTranslatef(tacoX, tacoY, tacoZ);

    // Alinhamento do cilindro
    float ref[3] = {0, 0, 1};
    float eixo[3] = {
        ref[1] * dirZ - ref[2] * dirY,
        ref[2] * dirX - ref[0] * dirZ,
        ref[0] * dirY - ref[1] * dirX};

    float eixoLen = sqrt(eixo[0] * eixo[0] + eixo[1] * eixo[1] + eixo[2] * eixo[2]);
    if (eixoLen > 1e-6)
    {
        eixo[0] /= eixoLen;
        eixo[1] /= eixoLen;
        eixo[2] /= eixoLen;
        float dot = ref[0] * dirX + ref[1] * dirY + ref[2] * dirZ;
        float angulo = acos(dot) * 180.0 / M_PI;
        glRotatef(angulo, eixo[0], eixo[1], eixo[2]);
    }

    // animação
    if (isTacada) {
        float amplitude = 4.0f;
        float frequencia = 1.5f;
        t += 0.016f;
        float deslocamento = amplitude * -sin(2 * M_PI * frequencia * t);
        if (deslocamento > 3.8f) {
            deslocamento = 0;
            isTacada = 0;
            t = 0;
        }
        glTranslatef(0.0f, 0.0f, deslocamento);
    }

    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.1, 0.05, 11.0, 20, 20);
    gluDeleteQuadric(quad);

    glPopMatrix();
}

