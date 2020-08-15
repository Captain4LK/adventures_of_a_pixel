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
#include <SDL2/SDL_mixer.h>
#include "../SoftLK-lib/include/SLK/SLK.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "map.h"
#include "modes.h"
#include "sound.h"
#include "player.h"
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

void mode_0_update()
{
   if(terrain_needs_redraw)
   {
      SLK_layer_set_current(3);
      SLK_draw_rgb_sprite(world[0][0].terrain,0,0);
      SLK_draw_rgb_set_changed(1);
      terrain_needs_redraw = 0;
   }

   if(SLK_key_pressed(SLK_KEY_S))
   {
      mode = 1;

      player.color = SLK_color_create(196,241,41,255);
      player.map_x = 20;
      player.map_y = 15;
      player.x = 32;
      player.y = 38;
      
      terrain_needs_redraw = 1;

      //Mix_PlayMusic(music[current_music],-1);
   }
}

void mode_1_update()
{
   if(terrain_needs_redraw)
   {
      SLK_layer_set_current(3);
      SLK_draw_rgb_sprite(world[player.map_y][player.map_x].terrain,0,0);
      SLK_draw_rgb_set_changed(1);
      terrain_needs_redraw = 0;
   }

   SLK_layer_set_current(1);
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);
   map_update();

   SLK_layer_set_current(2);
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);
   player_update();

   if(SLK_key_down(SLK_KEY_CTRL)&&SLK_key_pressed(SLK_KEY_R))
   {
      maps_load();  
      terrain_needs_redraw = 1;
   }
}
//-------------------------------------
