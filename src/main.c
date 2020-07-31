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
#include "player.h"
#include "modes.h"
#include "map.h"
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
   SLK_setup(64,64,4,"LOWREZJAM 2020",1,SLK_WINDOW_MAX,0);
   SLK_mouse_set_relative(1);
   SLK_mouse_capture(1);
   SLK_timer_set_fps(60);

   //Layer 0: menu/hud/front general
   SLK_layer_create(0,SLK_LAYER_RGB);
   SLK_layer_set_dynamic(0,0);
   SLK_layer_activate(0,1);
   SLK_layer_set_current(0);
   SLK_draw_rgb_set_clear_color(SLK_color_create(0,0,0,0));
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);

   //Layer 1: Damaging stuff
   SLK_layer_create(1,SLK_LAYER_RGB);
   SLK_layer_activate(1,1);
   SLK_layer_set_dynamic(1,0);
   SLK_layer_set_current(1);
   SLK_draw_rgb_set_clear_color(SLK_color_create(0,0,0,0));
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);

   //Layer 2: Collectibles/player
   SLK_layer_create(2,SLK_LAYER_RGB);
   SLK_layer_set_dynamic(2,0);
   SLK_layer_activate(2,1);
   SLK_layer_set_current(2);
   SLK_draw_rgb_set_clear_color(SLK_color_create(0,0,0,0));
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);

   //Layer 3: Terrain
   SLK_layer_create(3,SLK_LAYER_RGB);
   SLK_layer_set_dynamic(3,0);
   SLK_layer_activate(3,1);
   SLK_layer_set_current(3);
   SLK_draw_rgb_set_clear_color(SLK_color_create(0,0,0,0));
   SLK_draw_rgb_clear();
   SLK_draw_rgb_set_changed(1);

   maps_load();

   mode = 0;
   terrain_needs_redraw = 1;

   while(SLK_core_running())
   {
      SLK_update();

      switch(mode)
      {
      case 0: //Title screen
         mode_0_update(); 
         break;
      }

      SLK_render_update();
   }

   return 0;
}
//-------------------------------------
