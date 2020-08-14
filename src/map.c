/*
Copyright (c) 2020, Lukas Holzbeierlein (Captain4LK) 
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//External includes
#include "../SoftLK-lib/include/SLK/SLK.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "map.h"
#include "player.h"
#include "modes.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
static SLK_RGB_sprite *sprites[4];
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

void maps_load()
{
   SLK_RGB_sprite *map_sheet = SLK_rgb_sprite_load("assets/map_sheet.png");
   for(int x = 0;x<64;x++)
   {
      for(int y = 0;y<64;y++)
      {
         SLK_rgb_sprite_destroy(world[x][y].terrain);
         world[y][x].terrain = SLK_rgb_sprite_create(64,64);
         SLK_rgb_sprite_copy_partial(world[y][x].terrain,map_sheet,0,0,x*64,y*64,64,64);

         world[y][x].num_fireballs = 0;
         if(world[y][x].fireballs)
            free(world[y][x].fireballs);

         world[y][x].num_lava = 0;
         if(world[y][x].lava)
            free(world[y][x].lava);

         for(int i = 0;i<64*64;i++)
         {
            int alpha = world[y][x].terrain->data[i].a;
            if(alpha==254||alpha==253||alpha==252||alpha==251) //Fireball spawner
               world[y][x].num_fireballs++;
            else if(alpha==250)
               world[y][x].num_lava++;
         }
         
         //Create fireball spawners
         world[y][x].fireballs = malloc(sizeof(Spawner_fireball)*world[y][x].num_fireballs);
         world[y][x].num_fireballs = 0; //Reuse as counter
         
         //Create lava objects
         world[y][x].lava = malloc(sizeof(Lava)*world[y][x].num_lava);
         world[y][x].num_lava = 0;

         //Iterate again and actually load the spawners, enemies, etc
         for(int ty = 0;ty<64;ty++)
         {
            for(int tx = 0;tx<64;tx++)
            {
               int alpha = world[y][x].terrain->data[ty*64+tx].a;
               world[y][x].terrain->data[ty*64+tx].a = 255;

               if(alpha==255)
                  continue;

               switch(alpha)
               {
               case 254:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 0;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty;
                  world[y][x].num_fireballs++;

                  break;
               case 253:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 1;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty;
                  world[y][x].num_fireballs++;

                  break;
               case 252:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 2;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty;
                  world[y][x].num_fireballs++;

                  break;
               case 251:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 3;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty;
                  world[y][x].num_fireballs++;

                  break;
               case 250:
                  world[y][x].lava[world[y][x].num_lava].x = tx;
                  world[y][x].lava[world[y][x].num_lava].y = ty;
                  world[y][x].lava[world[y][x].num_lava].color = world[y][x].terrain->data[ty*64+tx];
                  world[y][x].terrain->data[ty*64+tx] = BLACK;
                  world[y][x].num_lava++;

                  break;
               }
            }
         }
      }
   }
   SLK_rgb_sprite_destroy(map_sheet);
}

//Yes this could go in a seperate source file, but the assets are needed here.
void assets_load()
{
   SLK_RGB_sprite *sheet = SLK_rgb_sprite_load("assets/sprites.png");
   
   //Fireball sprite
   sprites[0] = SLK_rgb_sprite_create(3,3);
   SLK_rgb_sprite_copy_partial(sprites[0],sheet,0,0,0,0,3,3);
   sprites[1] = SLK_rgb_sprite_create(3,3);
   SLK_rgb_sprite_copy_partial(sprites[1],sheet,0,0,3,0,3,3);
   sprites[2] = SLK_rgb_sprite_create(3,3);
   SLK_rgb_sprite_copy_partial(sprites[2],sheet,0,0,6,0,3,3);
   sprites[3] = SLK_rgb_sprite_create(3,3);
   SLK_rgb_sprite_copy_partial(sprites[3],sheet,0,0,9,0,3,3);

   SLK_rgb_sprite_destroy(sheet);
}

void map_update()
{
   //Update fireballs
   for(int i = 0;i<world[player.map_y][player.map_x].num_fireballs;i++)
   {
      Spawner_fireball *f = &world[player.map_y][player.map_x].fireballs[i];

      if(f->delay)
      {
         f->delay--;
      }
      else 
      {
         switch(f->dir)
         {
         case 0:
            if(map_get_pixel(player.map_x,player.map_y,f->bx,f->by+2).n!=BLACK.n)
            {
               f->by = f->y+1;
               f->delay = 8;
            }
            else
            {
               f->by++;
            }

            break;
         case 1:
            if(map_get_pixel(player.map_x,player.map_y,f->bx,f->by).n!=BLACK.n)
            {
               f->by = f->y-3;
               f->delay = 8;
            }
            else
            {
               f->by--;
            }

            break;
         case 2:
            if(map_get_pixel(player.map_x,player.map_y,f->bx+2,f->by).n!=BLACK.n)
            {
               f->bx = f->x+1;
               f->delay = 8;
            }
            else
            {
               f->bx++;
            }
            break;
         case 3:
            if(map_get_pixel(player.map_x,player.map_y,f->bx-2,f->by).n!=BLACK.n)
            {
               f->bx = f->x-1;
               f->delay = 8;
            }
            else
            {
               f->bx--;
            }
            break;
         }
      }

      SLK_draw_rgb_sprite(sprites[f->dir],f->bx-1,f->by);
   }

   //Draw lava pits
   for(int i = 0;i<world[player.map_y][player.map_x].num_lava;i++)
      SLK_draw_rgb_color(world[player.map_y][player.map_x].lava[i].x,world[player.map_y][player.map_x].lava[i].y,world[player.map_y][player.map_x].lava[i].color);
}

SLK_Color map_get_pixel(int map_x, int map_y, int x, int y)
{
   if(x<0||x>63||y<0||y>63)
      return BLACK;

   return world[map_y][map_x].terrain->data[y*64+x];
}
//-------------------------------------
