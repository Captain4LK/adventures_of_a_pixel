/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _MAP_H_

#define _MAP_H_

typedef struct Map_room
{
   uint8_t foreground[96*128];
   uint8_t background[96*128];
   struct Map_room *up, *down, *left, *right;
}Map_room;

typedef struct
{
   Map_room *rooms[256];
   SLK_Palette *pal_background;
   SLK_Palette *pal_foreground;
   Map_room *start;
}Map;

extern Map *map;

void map_load(int id, uint16_t pal_front_id, uint16_t pal_back_id);
void map_free();

/*typedef struct
{
   int x;
   int y;
   int bx;
   int by;
   int dir;
   int delay;
}Spawner_fireball;

typedef struct
{
   int x;
   int y;
   SLK_Color color;
}Lava;

typedef struct
{
   int type;
}Unlock;

typedef struct
{
  int x;
  int y;
  int dir;
  int ground_dir;
}Enemie;

typedef struct
{
   SLK_RGB_sprite *terrain;
   int num_fireballs;
   Spawner_fireball *fireballs;
   int num_lava;
   Lava *lava;
   int num_unlocks;
   int unlocked;
   Unlock *unlocks;
   int num_enemies;
   Enemie *enemies;
   int music;
}Map;

extern Map world[64][64];

void maps_load();
void assets_load();
SLK_Color map_get_pixel(int map_x, int map_y, int x, int y);
SLK_Color damage_map_get_pixel(int map_x, int map_y, int x, int y);
void map_update();
void map_update_fireballs();
void map_update_enemies();*/

#endif
