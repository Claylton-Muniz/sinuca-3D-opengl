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

int bolaEmCacapa(float bx, float bz)
{
    float raioCacapa = 0.4f;
    for (int i = 0; i < 6; i++)
    {
        float dx = bx - cacapas[i][0];
        float dz = bz - cacapas[i][1];
        float dist = sqrt(dx * dx + dz * dz);
        if (dist < raioCacapa)
            return 1;
    }
    return 0;
}

void colisaoBolas(float *x1, float *z1, float *vx1, float *vz1, 
                  float *x2, float *z2, float *vx2, float *vz2)
{
    float dx = *x2 - *x1;
    float dz = *z2 - *z1;
    float distancia = sqrt(dx * dx + dz * dz);
    
    // Raio das bolas
    float raio = 0.4f;
    
    // Verifica se há colisão
    if (distancia < 2 * raio)
    {
        // Normaliza o vetor direção
        dx /= distancia;
        dz /= distancia;
        
        // Calcula a velocidade relativa
        float dvx = *vx2 - *vx1;
        float dvz = *vz2 - *vz1;
        
        // Produto escalar entre velocidade relativa e normal
        float produtoEscalar = dvx * dx + dvz * dz;
        
        // Se as bolas estão se afastando, não faz nada
        if (produtoEscalar > 0) return;
        
        // Coeficiente de restituição (elasticidade)
        float e = 0.9f;
        
        // Impulso
        float j = -(1 + e) * produtoEscalar;
        j /= 2.0f; // massas iguais
        
        // Aplica o impulso
        *vx1 -= j * dx;
        *vz1 -= j * dz;
        *vx2 += j * dx;
        *vz2 += j * dz;
        
        // Corrige a sobreposição
        float sobreposicao = 2 * raio - distancia;
        *x1 -= dx * sobreposicao * 0.5f;
        *z1 -= dz * sobreposicao * 0.5f;
        *x2 += dx * sobreposicao * 0.5f;
        *z2 += dz * sobreposicao * 0.5f;
        
        printf("Colisão entre bolas!\n");
    }
}

void verificaColisaoBolas()
{
    colisaoBolas(&bolaX, &bolaZ, &bolaVX, &bolaVZ, 
                 &bola2X, &bola2Z, &bola2VX, &bola2VZ);
}

void atualiza()
{
    float dt = 0.016f;
    
    // Atualiza posição da bola 1
    bolaX += bolaVX * dt;
    bolaZ += bolaVZ * dt;
    
    // Atualiza posição da bola 2
    bola2X += bola2VX * dt;
    bola2Z += bola2VZ * dt;
    
    // Aplica atrito às duas bolas
    float atrito = 0.98f;
    bolaVX *= pow(atrito, dt * 60);
    bolaVZ *= pow(atrito, dt * 60);
    bola2VX *= pow(atrito, dt * 60);
    bola2VZ *= pow(atrito, dt * 60);
    
    // Para as bolas se a velocidade for muito baixa
    if (fabs(bolaVX) < 0.001f) bolaVX = 0;
    if (fabs(bolaVZ) < 0.001f) bolaVZ = 0;
    if (fabs(bola2VX) < 0.001f) bola2VX = 0;
    if (fabs(bola2VZ) < 0.001f) bola2VZ = 0;
    
    // Verifica colisão entre bolas
    verificaColisaoBolas();
    
    // Checar caçapas para ambas as bolas
    if (bolaEmCacapa(bolaX, bolaZ))
    {
        printf("Bolão encaçapada!\n");
        bolaVX = bolaVZ = 0;
        bolaX = 0.0f;
        bolaZ = -10.0f;
    }
    
    if (bolaEmCacapa(bola2X, bola2Z))
    {
        printf("Bola 2 encaçapada!\n");
        bola2VX = bola2VZ = 0;
        bola2X = 0.0f;
        bola2Y = -1.0f;
        bola2Z = 0.0f;
    }
    
    // Colisão com as paredes (para ambas as bolas)
    float minX = -8.0f + 0.4f;
    float maxX = 8.0f - 0.4f;
    float minZ = -14.0f + 0.4f;
    float maxZ = 14.0f - 0.4f;
    
    // Para bola 1
    if (bolaZ < -0.11f || bolaZ > 0.18f)
    {
        if (bolaX < minX) { bolaX = minX; bolaVX = -bolaVX; }
        if (bolaX > maxX) { bolaX = maxX; bolaVX = -bolaVX; }
        if (bolaZ < minZ) { bolaZ = minZ; bolaVZ = -bolaVZ; }
        if (bolaZ > maxZ) { bolaZ = maxZ; bolaVZ = -bolaVZ; }
    }
    
    // Para bola 2
    if (bola2Z < -0.11f || bola2Z > 0.18f)
    {
        if (bola2X < minX) { bola2X = minX; bola2VX = -bola2VX; }
        if (bola2X > maxX) { bola2X = maxX; bola2VX = -bola2VX; }
        if (bola2Z < minZ) { bola2Z = minZ; bola2VZ = -bola2VZ; }
        if (bola2Z > maxZ) { bola2Z = maxZ; bola2VZ = -bola2VZ; }
    }
    
    glutPostRedisplay();
    if (fabs(bolaVX) > 0.001f || fabs(bolaVZ) > 0.001f || 
        fabs(bola2VX) > 0.001f || fabs(bola2VZ) > 0.001f)
        glutTimerFunc(16, atualiza, 0);
}