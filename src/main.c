#include <GL/glut.h>
#include <math.h>

#include "../include/sinuca.h"
#include "../include/input.h"

#define M_PI 3.14159265358979323846

// Câmera e animação de tacada
int isTacada = 0;
int cameraAtual = 0;

// Movimentação do mouse
float yaw = 0.0f;   // rotação horizontal da câmera
float pitch = 0.3f; // inclinação vertical fixa
int lastX, lastY;
int width = 800, height = 450;

// Posições iniciais das bolas
float bolaX = 0.0f;
float bolaY = 0.9f;
float bolaZ = -10.0f;

// Posição inicial da bola 2
float bola2X = 0.5f; // Modificado para não sobrepor
float bola2Y = 0.9f;
float bola2Z = 8.75f;

// Posição inicial da bola 3
float bola3X = -0.5f;
float bola3Y = 0.9f;
float bola3Z = 8.75f;

// Posição inicial da bola 4
float bola4X = 0.0f;
float bola4Y = 0.9f;
float bola4Z = 8.1f;

// Velocidades
float bolaVX = 0.0f, bolaVZ = 0.0f;
float bola2VX = 0.0f, bola2VZ = 0.0f;
float bola3VX = 0.0f, bola3VZ = 0.0f;
float bola4VX = 0.0f, bola4VZ = 0.0f;

float atrito = 0.95f;

void init()
{
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {2.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Cor do brilho (branco)
    GLfloat mat_specular[] = {0.2f, 0.2f, 0.2f, 1.0f};  // Material com brilho
    GLfloat shininess[] = {2.5f};                      // Intensidade do brilho

    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // Luz com componente especular
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // Material com componente especular
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);   // Define o "brilho"

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

    if (bolaVX == 0 && bolaVZ == 0)
        cameraAtual = 1;

    if (cameraAtual == 0)
    {
        // cam. preview
        float raio = 25.0f;
        float camX = sin(yaw) * raio;
        float camZ = cos(yaw) * raio;
        float camY = 12.0f;

        gluLookAt(camX, camY, camZ,
                  0, 0, 0,
                  0, 1, 0);

        isTacada = 0; // gambiarra para fazer a animação funcionar
    }
    else
    {
        // cam. jogo
        float raio = 8.0f;
        float camX = bolaX + sin(yaw) * raio;
        float camY = bolaY + 5;
        float camZ = bolaZ + cos(yaw) * raio;

        gluLookAt(camX, camY, camZ,
                  bolaX, bolaY, bolaZ,
                  0, 1, 0);

        desenhaTaco(camX, camY, camZ, bolaX, bolaY, bolaZ);
    }

    desenhaMesa();
    desenhaBola(bolaX, bolaY, bolaZ, 1.0f, 1.0f, 1.0f);    // bolão
    desenhaBola(bola2X, bola2Y, bola2Z, 1.0f, 0.0f, 0.0f); // bola 2 - vermelha
    desenhaBola(bola3X, bola3Y, bola3Z, 0.0f, 1.0f, 0.0f); // bola 3 - verde
    desenhaBola(bola4X, bola4Y, bola4Z, 0.0f, 0.0f, 1.0f); // bola 4 - azul

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
    glutMouseFunc(mouse);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}