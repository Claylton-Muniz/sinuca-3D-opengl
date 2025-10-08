#ifndef FISICA_H
#define FISICA_H

extern float atrito;

extern float bolaX, bolaY, bolaZ;
extern float bola2X, bola2Y, bola2Z;
extern float bola3X, bola3Y, bola3Z;
extern float bola4X, bola4Y, bola4Z;

extern float bolaVX, bolaVZ;
extern float bola2VX, bola2VZ;
extern float bola3VX, bola3VZ;
extern float bola4VX, bola4VZ;

void atualiza(int value);
int bolaEmCacapa(float bx, float bz);
void colisaoBolas(float *x1, float *z1, float *vx1, float *vz1, 
                  float *x2, float *z2, float *vx2, float *vz2);
void verificaColisaoBolas();

#endif