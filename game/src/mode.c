/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "mode.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
typedef enum
{
   GAME_TITLE, GAME_CREDITS
}Game_mode;
//-------------------------------------

//Variables
static Game_mode mode = 0;
int terrain_needs_redraw;
//-------------------------------------

//Function prototypes
static void mode_title_update();
static void mode_credits_update();
//-------------------------------------

//Function implementations

void mode_update()
{
   switch(mode)
   {
   case GAME_TITLE: mode_title_update(); break;
   case GAME_CREDITS: mode_credits_update(); break;
   }
}

static void mode_title_update()
{
   int x,y;
   int selected = -1;
   SLK_mouse_get_layer_pos(0,&x,&y);

   //Input
   if(y>=66&&y<78)
   {
      if(x>=6&&x<50)
      {
         selected = 0;
         if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
            mode = GAME_CREDITS;
      }
      else if(x>=(XRES-32)/2-2&&x<(XRES-32)/2+34)
      {
         selected = 1;
      }
      else if(x>=XRES-42&&x<XRES-6)
      {
         selected = 2;
         if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
            SLK_core_quit();
      }
   }

   //Drawing
   SLK_layer_set_current(0);
   SLK_draw_pal_clear();

   SLK_draw_pal_string((XRES-80)/2,8,1,"Adventures",15);
   SLK_draw_pal_string((XRES-32)/2,18,1,"of a",15);
   SLK_draw_pal_string((XRES-40)/2,28,1,"pixel",15);

   SLK_draw_pal_string(8,68,1,"About",15);
   SLK_draw_pal_string((XRES-32)/2,68,1,"Play",15);
   SLK_draw_pal_string(XRES-40,68,1,"Quit",15);

   SLK_draw_pal_rectangle(6,66,44,12,selected==0?161:15);
   SLK_draw_pal_rectangle((XRES-32)/2-2,66,36,12,selected==1?161:15);
   SLK_draw_pal_rectangle(XRES-42,66,36,12,selected==2?161:15);

   SLK_draw_pal_index(x-1,y-1,161);
   SLK_draw_pal_index(x-2,y-2,161);
   SLK_draw_pal_index(x+1,y-1,161);
   SLK_draw_pal_index(x+2,y-2,161);
   SLK_draw_pal_index(x-1,y+1,161);
   SLK_draw_pal_index(x-2,y+2,161);
   SLK_draw_pal_index(x+1,y+1,161);
   SLK_draw_pal_index(x+2,y+2,161);
}

static void mode_credits_update()
{
   int x,y;
   int selected = -1;
   SLK_mouse_get_layer_pos(0,&x,&y);

   if(y>=YRES-18&&y<YRES-6&&x>=6&&x<42)
   {
      selected = 0;
      if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
         mode = GAME_TITLE;
   }

   //Drawing
   SLK_layer_set_current(0);
   SLK_draw_pal_clear();

   SLK_draw_pal_string(8,YRES-16,1,"Back",15);
   SLK_draw_pal_rectangle(6,YRES-18,36,12,selected==0?161:15);

   SLK_draw_pal_index(x-1,y-1,161);
   SLK_draw_pal_index(x-2,y-2,161);
   SLK_draw_pal_index(x+1,y-1,161);
   SLK_draw_pal_index(x+2,y-2,161);
   SLK_draw_pal_index(x-1,y+1,161);
   SLK_draw_pal_index(x-2,y+2,161);
   SLK_draw_pal_index(x+1,y+1,161);
   SLK_draw_pal_index(x+2,y+2,161);
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
