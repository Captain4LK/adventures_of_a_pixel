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

#include "../../shared/HLH_malloc.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "player.h"
#include "mode.h"
#include "sound.h"
#include "map.h"
#include "util.h"
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
   //Parse arguments
   int alloc_size = 0;
   for(int i = 1;i<argc;i++)
   {
      if(argv[i][0]=='-')
      {
         //Set custom allocator amount
         if(argv[i][1]=='m'&&argv[i][2]=='b')
            alloc_size = atoi(argv[++i]);
      }
   }

   //Initialize memory allocator
   if(alloc_size==0)
      alloc_size = 32;
   alloc_size/=2;
   HLH_malloc_default(&mem_game);
   HLH_malloc_default(&mem_util);
   HLH_malloc_set_max_memory_used(&mem_game,alloc_size*1024*1024);
   HLH_malloc_set_min_memory_required(&mem_game,alloc_size*1024*512);
   HLH_malloc_set_max_memory_used(&mem_util,alloc_size*1024*1024);
   HLH_malloc_set_min_memory_required(&mem_util,alloc_size*1024*512);
   HLH_malloc_init(&mem_game);
   HLH_malloc_init(&mem_util);

   SLK_setup(170,96,3,"Adventures of a pixel",0,SLK_WINDOW_MAX,0);
   SLK_timer_set_fps(20); //Beyond cinematic

   //Layer 0: menu/hud/front general
   SLK_layer_create(0,SLK_LAYER_PAL);
   SLK_layer_set_dynamic(0,0);
   SLK_layer_activate(0,1);
   SLK_layer_set_current(0);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Layer 1: Damaging stuff
   SLK_layer_create(1,SLK_LAYER_PAL);
   SLK_layer_activate(1,1);
   SLK_layer_set_dynamic(1,0);
   SLK_layer_set_current(1);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Layer 3: Terrain/Player
   SLK_layer_create(2,SLK_LAYER_PAL);
   SLK_layer_set_dynamic(2,0);
   SLK_layer_activate(2,1);
   SLK_layer_set_current(2);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Init audio system
   //I'm using SDL2_mixer since I don't need any
   //advanced features
   if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
        printf("Error: SDL_mixer failed to initialize! SDL_mixer Error: %s\n",Mix_GetError());

   //Load data
   SLK_draw_pal_load_font("assets/cursive2.slk");

   while(SLK_core_running())
   {
      SLK_update();
      
      mode_update();

      SLK_render_update();
  }

   /*//Load sounds and music
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
  }*/

   return 0;
}
//-------------------------------------
