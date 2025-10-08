#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL/SOIL.h>

#include "../../include/sinuca.h"

#define M_PI 3.14159265358979323846

float t = 0;

void desenhaEsferaTexturizada(GLuint textura, int texturaCarregada) {
    if(texturaCarregada) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        
        // Configuração para melhor qualidade de textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    // Desenhar esfera com coordenadas de textura adequadas
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE); // Habilita geração automática de coordenadas
    gluQuadricNormals(quad, GLU_SMOOTH);
    
    gluSphere(quad, 0.4f, 50, 50);
    
    gluDeleteQuadric(quad);
    
    if(texturaCarregada) {
        glDisable(GL_TEXTURE_2D);
    }
}

void desenhaBolaTexturizada(float x, float y, float z, GLuint textura, int texturaCarregada) {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(x, y, z);
    
    // Desenhar a esfera sem textura
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluSphere(quad, 0.4f, 50, 50);
    gluDeleteQuadric(quad);
    
    // Quadrado com textura
    if(texturaCarregada) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // SALVAR estado atual da iluminação
        GLboolean lightingEnabled;
        glGetBooleanv(GL_LIGHTING, &lightingEnabled);
        
        // DESABILITAR iluminação para a textura
        glDisable(GL_LIGHTING);
        
        // Resetar cor para branco puro
        glColor3f(1.0f, 1.0f, 1.0f);
        
        // Salvar a matriz atual
        glPushMatrix();
        
        // Obter a matriz de modelo/visão atual
        GLfloat modelview[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
        
        // Anular a rotação para que o quadrado sempre fique de frente para a câmera
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j)
                    modelview[i*4+j] = 1.0;
                else
                    modelview[i*4+j] = 0.0;
            }
        }
        
        // Aplicar a matriz modificada
        glLoadMatrixf(modelview);
        
        // Posicionar o quadrado na superfície da bola
        glTranslatef(0.0f, 0.0f, 0.4f);
        
        // Tamanho do quadrado
        float tamanho = 0.25f;
        
        // Desenhar o quadrado
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-tamanho, -tamanho, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(tamanho, -tamanho, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(tamanho, tamanho, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-tamanho, tamanho, 0.0f);
        glEnd();
        
        glPopMatrix();
        
        // RESTAURAR estado da iluminação
        if(lightingEnabled) {
            glEnable(GL_LIGHTING);
        }
        
        glDisable(GL_TEXTURE_2D);
    }
    
    glPopMatrix();
}

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

void desenhaBola(float x, float y, float z, float r, float g, float b)
{
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x, y, z);
    glutSolidSphere(0.4f, 50, 50);
    glPopMatrix();
}

void desenhaTaco(float camX, float camY, float camZ, float alvoX, float alvoY, float alvoZ)
{
    // Direção da câmera → bola (alvo)
    float dirX = alvoX - camX;
    float dirY = alvoY - camY;
    float dirZ = alvoZ - camZ;

    float len = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    dirX /= len;
    dirY /= len;
    float dirZ_norm = dirZ / len;

    // Posição fixa do taco
    float distanciaFixa = 15.0f; // distância constante da bola
    float alturaFixa = 0.9f;    // altura fixa do taco
    float offsetLateral = 0.0f; // ajuste lateral se necessário

    float tacoX = alvoX - dirX * distanciaFixa + offsetLateral;
    float tacoY = alturaFixa;
    float tacoZ = alvoZ - dirZ_norm * distanciaFixa;

    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);
    glTranslatef(tacoX, tacoY, tacoZ);

    // printf("x: %f y: %f z: %f\n", tacoX, tacoY, tacoZ);

    // Alinhamento do taco apontando para a bola
    float dirTacoX = alvoX - tacoX;
    float dirTacoY = alvoY - tacoY;
    float dirTacoZ = alvoZ - tacoZ;

    float lenTaco = sqrt(dirTacoX * dirTacoX + dirTacoY * dirTacoY + dirTacoZ * dirTacoZ);
    dirTacoX /= lenTaco;
    dirTacoY /= lenTaco;
    dirTacoZ /= lenTaco;

    // Rotação para alinhar com a direção bola-taco
    float ref[3] = {0, 0, 1}; // eixo padrão do cilindro
    float eixo[3] = {
        ref[1] * dirTacoZ - ref[2] * dirTacoY,
        ref[2] * dirTacoX - ref[0] * dirTacoZ,
        ref[0] * dirTacoY - ref[1] * dirTacoX};

    float eixoLen = sqrt(eixo[0] * eixo[0] + eixo[1] * eixo[1] + eixo[2] * eixo[2]);
    if (eixoLen > 1e-6)
    {
        eixo[0] /= eixoLen;
        eixo[1] /= eixoLen;
        eixo[2] /= eixoLen;
        float dot = ref[0] * dirTacoX + ref[1] * dirTacoY + ref[2] * dirTacoZ;
        float angulo = acos(dot) * 180.0 / M_PI;
        glRotatef(angulo, eixo[0], eixo[1], eixo[2]);
    }

    // Animação da tacada
    if (isTacada)
    {
        float amplitude = 1.5f;  // deslocamento máximo reduzido
        float frequencia = 1.5f; // ciclos por segundo
        t = t + 0.016f;          // segundos

        float deslocamento = amplitude * sin(2 * M_PI * frequencia * t);

        if (deslocamento > 1.4f)
        {
            deslocamento = 0;
            isTacada = 0;
            t = 0;
        }

        // Movimento na direção do taco (para frente e para trás)
        glTranslatef(0.0f, 0.0f, deslocamento);
    }

    // Desenha cilindro
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.1, 0.05, 11.0, 20, 20);
    gluDeleteQuadric(quad);

    glPopMatrix();
}
