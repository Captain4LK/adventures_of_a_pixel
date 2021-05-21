/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <time.h>
#include <SLK/SLK.h>
#include <SDL2/SDL_mixer.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "player.h"
#include "modes.h"
#include "sound.h"
#include "map.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
int current_music;
Mix_Music *music[2];

Mix_Chunk *sound_jump;
Mix_Chunk *sound_die;
Mix_Chunk *sound_fireball;
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

int main(int argc, char **argv)
{
   SLK_setup(64,64,4,"LOWREZJAM 2020",0,SLK_WINDOW_MAX,0);
   SLK_timer_set_fps(20);

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

   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048 )<0)
        printf("Error: SDL_mixer failed to initialize! SDL_mixer Error: %s\n",Mix_GetError());

   //Load sounds and music
   current_music = -1;
   music[0] = Mix_LoadMUS("assets/music0.ogg");
   music[1] = Mix_LoadMUS("assets/music1.ogg");
   sound_jump = Mix_LoadWAV("assets/jump.wav");
   sound_die = Mix_LoadWAV("assets/die.wav");
   sound_fireball = Mix_LoadWAV("assets/fireball.wav");

   //Set seed
   srand(time(NULL));

   assets_load();
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
      case 1: //Game
         mode_1_update(); 
         break;
      }

      SLK_render_update();
   }

   return 0;
}
//-------------------------------------
