/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
//-------------------------------------

//#defines
#define READ_ARG(I) \
   ((++(I))<argc?argv[(I)]:NULL)
//-------------------------------------

//Typedefs
typedef struct
{
   uint8_t foreground[128*96];
   uint8_t background[128*96];
}Map_room_file;
//-------------------------------------

//Variables
static uint8_t room_count = 0;
static uint8_t start_room = 0;
static Map_room_file map_rooms[256] = {0};
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

int main(int argc, char **argv)
{
   const char *map_path = NULL;
   for(int i = 1;i<argc;i++)
   {
      if(strcmp(argv[i],"-fin")==0)
      {
         map_path = READ_ARG(i);
      }
   }

   if(map_path==NULL)
   {
      return -1;
   }

   //Read map from file/generate empty map if not existing
   FILE *f = fopen(map_path,"rb");
   if(f==NULL)
   {
      room_count = 1;
      start_room = 0;
   }
   else
   {
      fread(&room_count,1,1,f);
      fread(&start_room,1,1,f);
      for(int i = 0;i<room_count;i++)
         fread(&map_rooms[i],sizeof(map_rooms[i]),1,f);

      fclose(f);
   }

   //Process input

   //Write map to file
   f = fopen(map_path,"wb");
   if(f==NULL)
   {
      puts("Well, sucks to be you!");
      return -1;
   }
   fwrite(&room_count,1,1,f);
   fwrite(&start_room,1,1,f);
   for(int i = 0;i<room_count;i++)
      fwrite(&map_rooms[i],sizeof(map_rooms[i]),1,f);
   fclose(f);

   return 0;
}
//-------------------------------------
