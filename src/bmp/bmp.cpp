//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Bmp.h"
#include <string.h>
#include "../canvas/gl_canvas2d.h"

Bmp::Bmp(const char *fileName)
{
   width = height = 0;
   data = NULL;
   if( fileName != NULL && strlen(fileName) > 0 )
   {
      load(fileName);
   }
   else
   {
      printf("Error: Invalid BMP filename");
   }
}

uchar* Bmp::getImage()
{
  return data;
}

int Bmp::getWidth(void)
{
  return width;
}

int Bmp::getHeight(void)
{
  return height;
}

void Bmp::convertBGRtoRGB()
{
  unsigned char tmp;
  if( data != NULL )
  {
     for(int y=0; y<height; y++)
     for(int x=0; x<width*3; x+=3)
     {
        int pos = y*bytesPerLine + x;
        tmp = data[pos];
        data[pos] = data[pos+2];
        data[pos+2] = tmp;
     }
  }
}

void Bmp::draw(float _x, float _y){
   CV::pointInit();
   for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * 3; x += 3) {
            // Calcule a posição do pixel no array de dados
            int pos = y * bytesPerLine + x;

            // Obtenha os valores RGB do pixel
            unsigned char r = data[pos + 2];  // componente R
            unsigned char g = data[pos + 1];  // componente G
            unsigned char b = data[pos];      // componente B

            // Chame a função color para definir a cor atual
            float r_norm = r / 255.0f;
            float g_norm = g / 255.0f;
            float b_norm = b / 255.0f;
            CV::color(r_norm, g_norm, b_norm);

            // Chame a função point para desenhar um ponto na posição (x / 3, y)
            CV::point2((x / 3)+_x, y+_y);
        }
    }
    CV::pointEnd();
}

void Bmp::load(const char *fileName)
{
  FILE *fp = fopen(fileName, "rb");
  if( fp == NULL )
  {
     printf("\nErro ao abrir arquivo %s para leitura", fileName);
     return;
  }

  //le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
  //o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
  fread(&header.type,      sizeof(unsigned short int), 1, fp);
  fread(&header.size,      sizeof(unsigned int),       1, fp);
  fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
  fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
  fread(&header.offset,    sizeof(unsigned int),       1, fp); //indica inicio do bloco de pixels

  //le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
  fread(&info.size,        sizeof(unsigned int),       1, fp);
  fread(&info.width,       sizeof(int),                1, fp);
  fread(&info.height,      sizeof(int),                1, fp);
  fread(&info.planes,      sizeof(unsigned short int), 1, fp);
  fread(&info.bits,        sizeof(unsigned short int), 1, fp);
  fread(&info.compression, sizeof(unsigned int),       1, fp);
  fread(&info.imagesize,   sizeof(unsigned int),       1, fp);
  fread(&info.xresolution, sizeof(int),                1, fp);
  fread(&info.yresolution, sizeof(int),                1, fp);
  fread(&info.ncolours,    sizeof(unsigned int),       1, fp);
  fread(&info.impcolours,  sizeof(unsigned int),       1, fp);

  width  = info.width;
  height = info.height;
  bits   = info.bits;
  bytesPerLine =(3 * (width + 1) / 4) * 4;
  imagesize    = bytesPerLine*height;

  //realiza diversas verificacoes de erro e compatibilidade
  if( header.type != 19778 )
  {
     printf("\nError: Arquivo BMP invalido");
     getchar();
     exit(0);
  }

  if( width*height*3 != imagesize )
  {
     //printf("\nWarning: Arquivo BMP nao tem largura multipla de 4");
     //getchar();
  }

  if( info.compression != 0 )
  {
     printf("\nError: Formato BMP comprimido nao suportado");
     getchar();
     return;
  }
  if( bits != 24 )
  {
     printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
     getchar();
     return;
  }

  if( info.planes != 1 )
  {
     printf("\nError: Numero de Planes nao suportado: %d", info.planes);
     getchar();
     return;
  }

  data = new unsigned char[imagesize];
  fseek(fp, header.offset, SEEK_SET);
  fread(data, sizeof(unsigned char), imagesize, fp);

  fclose(fp);
}
