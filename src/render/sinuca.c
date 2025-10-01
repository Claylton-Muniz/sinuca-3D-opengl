#include <GL/glut.h>

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

void desenhaTaco()
{
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);
    glTranslatef(0.0f, 1.0f, 23.0f);
    glRotatef(180, 0, 1, 0);
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.1, 0.05, 11.0, 20, 20);
    gluDeleteQuadric(quad);
    glPopMatrix();
}