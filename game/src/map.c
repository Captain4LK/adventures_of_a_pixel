/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <string.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "ressource.h"
#include "assets.h"
#include "map.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
typedef struct
{
   uint8_t foreground[96*128];
   uint8_t background[96*128];
}Map_room_file;
//-------------------------------------

//Variables
//static SLK_RGB_sprite *sprites[4];
//Map world[64][64];
Map *map = NULL;
static uint8_t room_count = 0;
static uint8_t room_start = 0;
//-------------------------------------

//Function prototypes
//static void choose_new_dir(Enemie *e);
//static void map_parse_screen(SLK_RGB_sprite *screen, int x, int y);
//-------------------------------------

//Function implementations

void map_load(int id, uint16_t pal_front_id, uint16_t pal_back_id)
{
   map_free();

   map = util_malloc(sizeof(*map));
   memset(map,0,sizeof(*map));

   //Load map data
   char tmp[64];
   sprintf(tmp,"MAP%05d",id);
   unsigned size_in;
   int32_t size_out;
   void *mem_pak, *mem_decomp;
   mem_pak = lump_get(tmp,LUMP_MAP,&size_in);
   mem_decomp = util_mem_decompress(mem_pak,size_in,&size_out);
   int pos = 0;
   room_count = *(((uint8_t *)mem_decomp)+pos); pos+=1;
   room_start = *(((uint8_t *)mem_decomp)+pos); pos+=1;
   for(int i = 0;i<room_count;i++)
   {
      map->rooms[i] = util_malloc(sizeof(*map->rooms[i]));
      memcpy(map->rooms[i],mem_decomp+pos,sizeof(*map->rooms[i]));
      pos+=sizeof(*map->rooms[i]);
   }
   util_free(mem_pak);
   util_free(mem_decomp);

   //Load palettes
   sprintf(tmp,"PAL%05d",pal_front_id);
   mem_pak = lump_get(tmp,LUMP_PAL,&size_in);
   map->pal_foreground = palette_load(mem_pak,size_in);
   util_free(mem_pak);
   sprintf(tmp,"PAL%05d",pal_back_id);
   mem_pak = lump_get(tmp,LUMP_PAL,&size_in);
   map->pal_background = palette_load(mem_pak,size_in);
   util_free(mem_pak);
   SLK_layer_set_palette(1,map->pal_foreground);
   SLK_layer_set_palette(2,map->pal_background);

   //Arrange map
   map->start = map->rooms[room_start];
}

void map_free()
{
   if(map==NULL)
      return;

   for(int i = 0;i<256;i++)
   {
      if(map->rooms[i]!=NULL)
         util_free(map->rooms[i]);
      map->rooms[i] = NULL;
   }

   if(map->pal_foreground!=NULL)
      util_free(map->pal_foreground);
   map->pal_foreground = NULL;
   if(map->pal_background!=NULL)
      util_free(map->pal_background);
   map->pal_background = NULL;

   if(map!=NULL)
      util_free(map);
   map = NULL;
}

/*void maps_load()
{
   SLK_RGB_sprite *map_sheet = SLK_rgb_sprite_load("assets/map_sheet.png");
   for(int x = 0;x<64;x++)
   {
      for(int y = 0;y<64;y++)
      {
         SLK_rgb_sprite_destroy(world[x][y].terrain);
         world[y][x].terrain = SLK_rgb_sprite_create(64,64);
         SLK_rgb_sprite_copy_partial(world[y][x].terrain,map_sheet,0,0,x*64,y*64,64,64);

         map_parse_screen(world[y][x].terrain,x,y);

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
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty+2;
                  world[y][x].num_fireballs++;

                  break;
               case 253:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 1;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty-2;
                  world[y][x].num_fireballs++;

                  break;
               case 252:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 2;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx+2;
                  world[y][x].fireballs[world[y][x].num_fireballs].by = ty;
                  world[y][x].num_fireballs++;

                  break;
               case 251:
                  world[y][x].fireballs[world[y][x].num_fireballs].delay = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].dir = 3;
                  world[y][x].fireballs[world[y][x].num_fireballs].x = tx;
                  world[y][x].fireballs[world[y][x].num_fireballs].y = ty;
                  world[y][x].fireballs[world[y][x].num_fireballs].bx = tx-2;
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
               case 249: //Left
                  world[y][x].enemies[world[y][x].num_enemies].x = tx;
                  world[y][x].enemies[world[y][x].num_enemies].y = ty;
                  world[y][x].enemies[world[y][x].num_enemies].dir = 0;
                  if(map_get_pixel(x,y,tx,ty-1).n==BLACK.n)
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = 1; //Ground below
                  else 
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = -1; //Ground above
                  world[y][x].terrain->data[ty*64+tx] = BLACK;
                  world[y][x].num_enemies++;

                  break;
               case 248: //Right
                  world[y][x].enemies[world[y][x].num_enemies].x = tx;
                  world[y][x].enemies[world[y][x].num_enemies].y = ty;
                  world[y][x].enemies[world[y][x].num_enemies].dir = 1;
                  if(map_get_pixel(x,y,tx,ty-1).n==BLACK.n)
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = 1; //Ground below
                  else 
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = -1; //Ground above
                  world[y][x].terrain->data[ty*64+tx] = BLACK;
                  world[y][x].num_enemies++;

                  break;
               case 247: //Up
                  world[y][x].enemies[world[y][x].num_enemies].x = tx;
                  world[y][x].enemies[world[y][x].num_enemies].y = ty;
                  world[y][x].enemies[world[y][x].num_enemies].dir = 2;
                  if(map_get_pixel(x,y,tx-1,ty).n==BLACK.n)
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = 1; //Ground right
                  else 
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = -1; //Ground left
                  world[y][x].terrain->data[ty*64+tx] = BLACK;
                  world[y][x].num_enemies++;

                  break;
               case 246: //Down
                  world[y][x].enemies[world[y][x].num_enemies].x = tx;
                  world[y][x].enemies[world[y][x].num_enemies].y = ty;
                  world[y][x].enemies[world[y][x].num_enemies].dir = 3;
                  if(map_get_pixel(x,y,tx-1,ty).n==BLACK.n)
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = 1; //Ground right
                  else 
                     world[y][x].enemies[world[y][x].num_enemies].ground_dir = -1; //Ground left
                  world[y][x].terrain->data[ty*64+tx] = BLACK;
                  world[y][x].num_enemies++;

                  break;
               case 1:
                  world[y][x].unlocks[world[y][x].num_unlocks].type = 0;
                  world[y][x].num_unlocks++;

                  break;
               case 2:
                  world[y][x].unlocks[world[y][x].num_unlocks].type = 1;
                  world[y][x].num_unlocks++;

                  break;
               case 3:
                  world[y][x].unlocks[world[y][x].num_unlocks].type = 2;
                  world[y][x].num_unlocks++;

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
   //Draw lava pits
   for(int i = 0;i<world[player.map_y][player.map_x].num_lava;i++)
      SLK_draw_rgb_color(world[player.map_y][player.map_x].lava[i].x,world[player.map_y][player.map_x].lava[i].y,world[player.map_y][player.map_x].lava[i].color);

   map_update_enemies();
   map_update_fireballs();

   //Activate unlocks
   if(!world[player.map_y][player.map_x].unlocked)
   {
      for(int i = 0;i<world[player.map_y][player.map_x].num_unlocks;i++)
      {
         switch(world[player.map_y][player.map_x].unlocks[i].type)
         {
         case 0: //Movement
            player.move_unlocked = 1;
            break;
         case 1: //Jump
            player.jump_unlocked = 1;
            break;
         case 2: //Double jump
            player.double_jump_unlocked = 1;
            break;
         }
      }

      world[player.map_y][player.map_x].unlocked = 1;
   }

   //Choose right music
   if(world[player.map_y][player.map_x].music!=-1&&current_music!=world[player.map_y][player.map_x].music)
   {
      if(Mix_PlayingMusic())
         Mix_HaltMusic();

      current_music = world[player.map_y][player.map_x].music; 
      Mix_PlayMusic(music[current_music],-1);
   }
}

void map_update_fireballs()
{
   //Update fireballs
   for(int i = 0;i<world[player.map_y][player.map_x].num_fireballs;i++)
   {
      Spawner_fireball *f = &world[player.map_y][player.map_x].fireballs[i];

      if(f->delay)
      {
         f->delay--;
         if(f->delay==1)
            Mix_PlayChannel(-1,sound_fireball,0);
      }
      else 
      {
         switch(f->dir)
         {
         case 0:
            if(f->by>64)
            {
               f->by = f->y+2;
               Mix_PlayChannel(-1,sound_fireball,0);
            }
            else
               f->by++;

            break;
         case 1:
            if(f->by<0)
            {
               f->by = f->y-2;
               Mix_PlayChannel(-1,sound_fireball,0);
            }
            else
               f->by--;

            break;
         case 2:
            if(f->bx>64)
            {
               f->bx = f->x+2;
               Mix_PlayChannel(-1,sound_fireball,0);
            }
            else
               f->bx++;
            break;
         case 3:
            if(f->bx<0)
            {
               f->bx = f->x-2;
               Mix_PlayChannel(-1,sound_fireball,0);
            }
            else
               f->bx--;
            break;
         }
      }

      SLK_draw_rgb_sprite(sprites[f->dir],f->bx-1,f->by-1);
   }
}

void map_update_enemies()
{

   for(int i = 0;i<world[player.map_y][player.map_x].num_enemies;i++)
   {
      Enemie *e = &world[player.map_y][player.map_x].enemies[i];

      switch(e->dir)
      {
      case 0:
         if(map_get_pixel(player.map_x,player.map_y,e->x-1,e->y).n==BLACK.n&&map_get_pixel(player.map_x,player.map_y,e->x,e->y+e->ground_dir).n!=BLACK.n)
            e->x--;
         else
            choose_new_dir(e);

         break;
      case 1:
         if(map_get_pixel(player.map_x,player.map_y,e->x+1,e->y).n==BLACK.n&&map_get_pixel(player.map_x,player.map_y,e->x,e->y+e->ground_dir).n!=BLACK.n)
            e->x++;
         else
            choose_new_dir(e);

         break;
      case 2:
         if(map_get_pixel(player.map_x,player.map_y,e->x,e->y-1).n==BLACK.n&&map_get_pixel(player.map_x,player.map_y,e->x+e->ground_dir,e->y).n!=BLACK.n)
            e->y--;
         else
            choose_new_dir(e);

         break;
      case 3:
         if(map_get_pixel(player.map_x,player.map_y,e->x,e->y+1).n==BLACK.n&&map_get_pixel(player.map_x,player.map_y,e->x+e->ground_dir,e->y).n!=BLACK.n)
            e->y++;
         else
            choose_new_dir(e);

         break;
      }

      SLK_draw_rgb_color(e->x,e->y,SLK_color_create(241,100,31,255));
   }

}

SLK_Color map_get_pixel(int map_x, int map_y, int x, int y)
{
   if(x<0||x>63||y<0||y>63)
      return BLACK;

   return world[map_y][map_x].terrain->data[y*64+x];
}

static void choose_new_dir(Enemie *e)
{
   if(e->dir!=0&&e->dir!=1&&map_get_pixel(player.map_x,player.map_y,e->x-1,e->y).n==BLACK.n&&(map_get_pixel(player.map_x,player.map_y,e->x-1,e->y+1).n!=BLACK.n||map_get_pixel(player.map_x,player.map_y,e->x-1,e->y-1).n!=BLACK.n)) //Left
   {
      e->dir = 0;  
      if(map_get_pixel(player.map_x,player.map_y,e->x-1,e->y-1).n==BLACK.n)
         e->ground_dir = 1; //Ground below
      else 
         e->ground_dir = -1; //Ground above
      e->x--;
   }
   else if(e->dir!=1&&e->dir!=0&&map_get_pixel(player.map_x,player.map_y,e->x+1,e->y).n==BLACK.n&&(map_get_pixel(player.map_x,player.map_y,e->x+1,e->y+1).n!=BLACK.n||map_get_pixel(player.map_x,player.map_y,e->x+1,e->y-1).n!=BLACK.n)) //Right
   {
      e->dir = 1;  
      if(map_get_pixel(player.map_x,player.map_y,e->x+1,e->y-1).n==BLACK.n)
         e->ground_dir = 1; //Ground below
      else 
         e->ground_dir = -1; //Ground above
      e->x++;
   }
   else if(e->dir!=2&&e->dir!=3&&map_get_pixel(player.map_x,player.map_y,e->x,e->y-1).n==BLACK.n&&(map_get_pixel(player.map_x,player.map_y,e->x+1,e->y-1).n!=BLACK.n||map_get_pixel(player.map_x,player.map_y,e->x-1,e->y-1).n!=BLACK.n)) //Up
   {
      e->dir = 2;  
      if(map_get_pixel(player.map_x,player.map_y,e->x-1,e->y-1).n==BLACK.n)
         e->ground_dir = 1; //Ground below
      else 
         e->ground_dir = -1; //Ground above
      e->y--;
   }
   else if(e->dir!=3&&e->dir!=2&&map_get_pixel(player.map_x,player.map_y,e->x,e->y+1).n==BLACK.n&&(map_get_pixel(player.map_x,player.map_y,e->x+1,e->y+1).n!=BLACK.n||map_get_pixel(player.map_x,player.map_y,e->x-1,e->y+1).n!=BLACK.n)) //Down
   {
      e->dir = 3;  
      if(map_get_pixel(player.map_x,player.map_y,e->x-1,e->y+1).n==BLACK.n)
         e->ground_dir = 1; //Ground below
      else 
         e->ground_dir = -1; //Ground above
      e->y++;
   }
}

static void map_parse_screen(SLK_RGB_sprite *screen, int x, int y)
{
   world[y][x].num_fireballs = 0;
   if(world[y][x].fireballs)
   free(world[y][x].fireballs);

   world[y][x].num_lava = 0;
   if(world[y][x].lava)
   free(world[y][x].lava);

   world[y][x].num_unlocks = 0;
   if(world[y][x].unlocks)
   free(world[y][x].unlocks);

   world[y][x].num_enemies = 0;
   if(world[y][x].enemies)
   free(world[y][x].enemies);

   world[y][x].music = -1;

   for(int i = 0;i<64*64;i++)
   {
      int alpha = screen->data[i].a;
      if(alpha==254||alpha==253||alpha==252||alpha==251) //Fireball spawner
         world[y][x].num_fireballs++;
      else if(alpha==250)
         world[y][x].num_lava++;
      else if(alpha==249||alpha==248||alpha==247||alpha==246)
         world[y][x].num_enemies++;
      else if(alpha==100)
         world[y][x].music = 0;
      else if(alpha==101)
         world[y][x].music = 1;
      else if(alpha==1||alpha==2||alpha==3)
         world[y][x].num_unlocks++;
   }
   
   //Create fireball spawners
   world[y][x].fireballs = malloc(sizeof(Spawner_fireball)*world[y][x].num_fireballs);
   world[y][x].num_fireballs = 0; //Reuse as counter
   
   //Create lava objects
   world[y][x].lava = malloc(sizeof(Lava)*world[y][x].num_lava);
   world[y][x].num_lava = 0;

   //Create unlocks
   world[y][x].unlocks = malloc(sizeof(Unlock)*world[y][x].num_unlocks);
   world[y][x].unlocked = 0;
   world[y][x].num_unlocks = 0;

   //Create enemies
   world[y][x].enemies = malloc(sizeof(Enemie)*world[y][x].num_enemies);
   world[y][x].num_enemies = 0;
}*/
//-------------------------------------
