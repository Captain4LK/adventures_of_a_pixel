/*
Copyright (c) 2020, Lukas Holzbeierlein (Captain4LK) 
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _MAP_H_

#define _MAP_H_

typedef struct
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
void map_update_enemies();

#endif
