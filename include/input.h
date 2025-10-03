#ifndef INPUT_H
#define INPUT_H

extern int isTacada;
extern int cameraAtual;

extern float bolaX, bolaZ; // testar colisões
extern float bolaVX, bolaVZ; 

extern float yaw;
extern float pitch;
extern int width, height;

extern void atualiza();

void mouseMotion(int x, int y);
void mouse(int button, int state, int x, int y);
void teclado(unsigned char key, int x, int y);

#endif