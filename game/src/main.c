/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <time.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "ressource.h"
#include "assets.h"
#include "mode.h"
#include "map_list.h"
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
   //Initialize memory allocator
   util_malloc_init(MEM_MIN,MEM_MAX);
   SLK_set_malloc(util_malloc);
   SLK_set_free(util_free);
   SLK_set_realloc(util_realloc);

   SLK_setup(XRES,YRES,3,"Adventures of a pixel",0,SLK_WINDOW_MAX,0);
   SLK_mouse_show_cursor(0);
   SLK_timer_set_fps(FPS);

   //Layer 0: menu/hud/front general
   SLK_layer_create(0,SLK_LAYER_PAL);
   SLK_layer_set_dynamic(0,0);
   SLK_layer_activate(0,1);
   SLK_layer_set_current(0);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Layer 1: foreground layer
   SLK_layer_create(1,SLK_LAYER_PAL);
   SLK_layer_activate(1,1);
   SLK_layer_set_dynamic(1,0);
   SLK_layer_set_current(1);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Layer 2: background layer
   SLK_layer_create(2,SLK_LAYER_PAL);
   SLK_layer_set_dynamic(2,0);
   SLK_layer_activate(2,1);
   SLK_layer_set_current(2);
   SLK_draw_pal_set_clear_index(0);
   SLK_draw_pal_clear();

   //Load ressources
   ini_parse("settings.ini");
   ressource_add("data/main.json");
   map_list_load();
   assets_load_default();

   //SLK_Pal_sprite *p = SLK_pal_sprite_load("out.slk");
   //SLK_pal_sprite_save("test.slk",p,0);
   //util_compress_path("test.slk","out.4mb");

   while(SLK_core_running())
   {
      SLK_update();
      
      mode_update();
      if(SLK_key_pressed(SLK_KEY_P))
         util_malloc_report();

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
