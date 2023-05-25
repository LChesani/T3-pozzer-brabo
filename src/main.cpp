#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GameManager.h"
#include "canvas/gl_canvas2d.h"

#include "canvas/gl_canvas2d.h"
int screenWidth = 1280, screenHeight = 720;
int mouseX, mouseY;
GameManager *gameManager = nullptr;

void render(){
   if(gameManager != nullptr){
      gameManager->render();
   }
}

void keyboard(int key)
{
   gameManager->keyDown(key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   gameManager->keyUp(key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;


   if( state == 0 ) //clicou
   {

   }
}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "Space invaders malvado");
   gameManager = new GameManager(screenWidth, screenHeight);
   CV::run();
}
