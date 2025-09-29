#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846

float angulo = 0.0f; // ângulo da câmera

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
    gluPerspective(45, (float)16 / 9, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Calcula posição da câmera em círculo
    float raio = 25.0f;
    float camX = sin(angulo) * raio;
    float camZ = cos(angulo) * raio;
    float camY = 12.0f; // altura fixa

    gluLookAt(
        camX, camY, camZ, // posição da câmera
        0, 0, 0,          // olha para o centro da mesa
        0, 1, 0           // "cima"
    );

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

    // --- Bola ---
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.9f, 10.0f);
    glutSolidSphere(0.4f, 50, 50);
    glPopMatrix();

    // --- Taco ---
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);
    glTranslatef(0.0f, 1.0f, 23.0f);
    glRotatef(180, 0, 1, 0);
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.1, 0.05, 11.0, 20, 20);
    gluDeleteQuadric(quad);
    glPopMatrix();

    glutSwapBuffers();
}

void idle()
{
    angulo += 0.006f; // velocidade de rotação da câmera
    if (angulo > 2 * M_PI)
        angulo -= 2 * M_PI;

    glutPostRedisplay(); // redesenha continuamente
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 450);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sinuca 3D");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle); // animação da câmera

    glutMainLoop();
    return 0;
}
