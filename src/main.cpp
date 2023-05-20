

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stage/Stage.h"
#include "agent/Agent.h"
#include "agent/Protagonist.h"
#include "canvas/gl_canvas2d.h"
#include "stage/Stage.h"

int opcao  = 50;
int screenWidth = 500, screenHeight = 500;
int mouseX, mouseY;

Protagonist *player = nullptr;
Stage *stage = nullptr;

void render(){
   if(player != nullptr){
      player->render();
   }
   if(stage != nullptr){
      stage->render();
   }
}

void keyboard(int key)
{
   player->keyPress(key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   player->KeyUp(key);
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
   player = new Protagonist(screenWidth, 50.0, 100.0);
   stage = new Stage(screenWidth, screenHeight, player);
   CV::run();
}
