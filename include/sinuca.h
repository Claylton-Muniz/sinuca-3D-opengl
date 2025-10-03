#ifndef SINUCA_H
#define SINUCA_H

// Variáveis da bola 1 (bolão)
extern float bolaX, bolaY, bolaZ;
extern float bolaVX, bolaVZ;

// Variáveis da bola 2
extern float bola2X, bola2Y, bola2Z;
extern float bola2VX, bola2VZ;

// Outras variáveis
extern int isTacada;
extern int cameraAtual;
extern float yaw, pitch;
extern int width, height;

// Funções
void desenhaMesa();
void desenhaBola(float x, float y, float z, float r, float g, float b);
void desenhaTaco(float camX, float camY, float camZ, float alvoX, float alvoY, float alvoZ);
int bolaEmCacapa(float bx, float bz);
void atualiza();
void verificaColisaoBolas();

#endif