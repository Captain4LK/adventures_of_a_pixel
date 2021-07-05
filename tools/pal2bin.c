/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <stdlib.h>
#include <stdint.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

int main(int argc, char **argv)
{
   if(argc<2)
      return -1;

   SLK_Palette *p = SLK_palette_load(argv[1]);
   uint8_t used = (uint8_t)(p->used-1);
   FILE *f = fopen("out.bin","wb");
   fwrite(&used,1,1,f);
   for(int i = 0;i<p->used;i++)
   {
      fwrite(&p->colors[i].r,1,1,f);
      fwrite(&p->colors[i].g,1,1,f);
      fwrite(&p->colors[i].b,1,1,f);
      fwrite(&p->colors[i].a,1,1,f);
   }
   fclose(f);
   
   return 0;
}
//-------------------------------------
