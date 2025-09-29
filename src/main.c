#include <GL/glut.h>

void init() {
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 2.0f, 2.0f, 2.0f, 1.0f }; 
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat mat_diffuse[] = { 0.2f, 0.6f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)16/9, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        23, 6, 0,        // posição da câmera
        0, 0, 0,         // olha para o centro
        0, 1, 0
    );

    // --- Mesa de sinuca ---
    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(28.0f, 0.5f, 16.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas laterais ---
    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(12.5f, 0.7f, 0.5f);
        glTranslatef(0.545f, 0.6f, 16.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(12.5f, 0.7f, 0.5f);
        glTranslatef(-0.545f, 0.6f, 16.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(12.5f, 0.7f, 0.5f);
        glTranslatef(0.545f, 0.6f, -16.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(12.5f, 0.7f, 0.5f);
        glTranslatef(-0.545f, 0.6f, -16.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // --- Tabelas frontais ---
    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(0.5f, 0.7f, 14.0f);
        glTranslatef(28.0f, 0.6f, 0.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.5f, 0.0f);
        glScalef(0.5f, 0.7f, 14.0f);
        glTranslatef(-28.0f, 0.6f, 0.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // --- Bola ---
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(10.0f, 0.6f, 0.0f);
        glutSolidSphere(0.4, 50, 50);
    glPopMatrix();

    // --- Taco ---
    glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.0f); // marrom do taco
        glTranslatef(22.0f, 1.3f, 0.0f); // posição inicial
        glRotatef(-90, 0, 1, 0);         // inclinação horizontal
        glRotatef(3, 1, 0, 0);           // inclinação vertical
        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, 0.1, 0.05, 11.0, 20, 20); // taco afunilado
        gluDeleteQuadric(quad);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 450);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sinuca 3D");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
