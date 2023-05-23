//********************************************************
// Cesar Tadeu Pozzer
// 09/2009
// UFSM
// pozzer@inf.ufsm.br
//********************************************************



#ifndef _FRAMES_H___
#define _FRAMES_H___

#include <stdio.h>
#include <time.h>
#include<windows.h>
#include "gl_canvas2d.h"
#include "utils.h"

#define UPDATE_RATE 30   //milisegundos


////////////////////////////////////////////////////////////////////////////////////////
class Frames{
   clock_t t1, t2;
   long    cont_frames;
   float   relativeSpeed = 1, fps = 120, fps_old;
   float lim = 20.0f;
public:
   Frames()
   {
      t1 = clock();
	  cont_frames = 0;
      fps_old = 20; //valor inicial
   }

   //*********************************************************************
   // Este metodo deve ser chamado uma unica vez a cada atualizacao de tela
   // Retorna o fps da aplicacao. Altere o valor de UPDATE_RATE para diferentes
   // tempos de atualizacao.
   //*********************************************************************
   float getFrames()
   {
      double tempo;

      t2 = clock();
      tempo  = (double)(t2 - t1);  //milisegundos
      cont_frames++;
      //apos UPDATE_RATE milisegundos, atualiza o framerate
      if( tempo > UPDATE_RATE )
      {
         t1 = t2;
         fps = cont_frames / (tempo/CLOCKS_PER_SEC);
         cont_frames = 0;
         fps_old = fps;

         return fps;
      }
      //se nao foi decorrido UPDATE_RATE milisegundos, retorna a taxa antiga
      return fps_old;
   }

    void setFps(float fps){
        this->lim = fps;
    }

   float getFps(){
      return fps;
   }

    void control(){
        getFrames();
        if(fps > lim){
            Sleep((1000/lim) - (1000/fps));
        }
    }

    float getRelativeSpeed(){
        return relativeSpeed;
    }

   void plotFps(float w, float h){
      CV::color(0,0,0);
      control();
      fps = getFrames();
      relativeSpeed = fps/120.0f;
      
      char *str = new char[10];
      char *str2 = new char[20];
      
      sprintf(str, "FPS: %.0f", fps);
      sprintf(str2, "Speed: %.5f", relativeSpeed);
      CV::text(10, h-70, str);
      CV::text(10, h-80, str2);
   }

};

#endif