/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <SDL2/SDL_mixer.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "map.h"
#include "mode.h"
#include "sound.h"
#include "player.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
typedef enum
{
   GAME_TITLE
}Game_mode;
//-------------------------------------

//Variables
static Game_mode mode = 0;
int terrain_needs_redraw;
//-------------------------------------

//Function prototypes
static void mode_title_update();
//-------------------------------------

//Function implementations

void mode_update()
{
   switch(mode)
   {
   case GAME_TITLE: mode_title_update(); break;
   }
}

static void mode_title_update()
{
}

/*void mode_0_update()
{
   if(terrain_needs_redraw)
   {
      SLK_layer_set_current(3);
      SLK_draw_rgb_sprite(world[0][0].terrain,0,0);
      SLK_draw_rgb_set_changed(1);
      terrain_needs_redraw = 0;
   }

   if(SLK_key_pressed(SLK_KEY_S)||SLK_gamepad_down(0,SLK_PAD_DOWN))
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
}*/
//-------------------------------------
