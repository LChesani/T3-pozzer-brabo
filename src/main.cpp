

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "agent/Agent.h"
#include "agent/Protagonist.h"
#include "canvas/gl_canvas2d.h"

int opcao  = 50;
int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;

Protagonist *MC = nullptr;

void render()
{
   MC->render();
}

void keyboard(int key)
{
   MC->keyPress(key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   MC->KeyUp(key);
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
   MC = new Protagonist(screenWidth, 50.0, 100.0);
   CV::run();
}
