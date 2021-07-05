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
#include "map_list.h"
#include "map.h"
#include "assets.h"
#include "mode.h"
//-------------------------------------

//#defines
#define CLAMP_WRAP(lo,up,val) \
   ((val)<lo?up:((val)>up)?lo:val)
//-------------------------------------

//Typedefs
typedef enum
{
   GAME_TITLE, GAME_CREDITS, GAME_EPSEL, GAME_GAME
}Game_mode;
//-------------------------------------

//Variables
static Game_mode mode = 0;
//-------------------------------------

//Function prototypes
static void mode_title_update();
static void mode_credits_update();
static void mode_epsel_update();
static void mode_game_update();
//-------------------------------------

//Function implementations

void mode_update()
{
   switch(mode)
   {
   case GAME_TITLE: mode_title_update(); break;
   case GAME_CREDITS: mode_credits_update(); break;
   case GAME_EPSEL: mode_epsel_update(); break;
   case GAME_GAME: mode_game_update(); break;
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
         if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
         {
            map_list_load_assets();
            mode = GAME_EPSEL;
         }
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

static void mode_epsel_update()
{
   static int ep_selected = 0;
   int x,y;
   int selected = -1;
   SLK_mouse_get_layer_pos(0,&x,&y);

   if(y>=YRES-18&&y<YRES-6&&x>=6&&x<42)
   {
      selected = 0;
      if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
         mode = GAME_TITLE;
   }
   else if(y>=YRES-18&&y<YRES-6&&x>=XRES-42&&x<XRES-6)
   {
      selected = 1;
      if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
      {
         map_load(map_entries[ep_selected].map_id,map_entries[ep_selected].pal_front_id,map_entries[ep_selected].pal_back_id);
         mode = GAME_GAME;
      }
   }
   else if(x>=32&&x<68)
   {
      if(y>=4&&y<16)
      {
         selected = 2;
         if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
            ep_selected = CLAMP_WRAP(0,map_list_size-1,ep_selected-1);
      }
      else if(y>=58&&y<70)
      {
         selected = 3;
         if(SLK_mouse_pressed(SLK_BUTTON_LEFT))
            ep_selected = CLAMP_WRAP(0,map_list_size-1,ep_selected+1);
      }
   }

   //Drawing
   SLK_layer_set_current(0);
   SLK_draw_pal_clear();

   SLK_draw_pal_string(8,YRES-16,1,"Back",15);
   SLK_draw_pal_string(XRES-40,YRES-16,1,"Play",15);
   SLK_draw_pal_rectangle(6,YRES-18,36,12,selected==0?161:15);
   SLK_draw_pal_rectangle(XRES-42,YRES-18,36,12,selected==1?161:15);
   SLK_draw_pal_rectangle(XRES-70,4,66,66,15);

   SLK_draw_pal_sprite(textures[map_entries[ep_selected].preview_id],XRES-69,5);

   SLK_draw_pal_string(2,18,1,map_entries[CLAMP_WRAP(0,map_list_size-1,ep_selected-1)].title,8);
   SLK_draw_pal_string(2,33,1,map_entries[ep_selected].title,15);
   SLK_draw_pal_string(2,48,1,map_entries[CLAMP_WRAP(0,map_list_size-1,ep_selected+1)].title,8);

   SLK_draw_pal_line(32,15,49,5,15);
   SLK_draw_pal_line(67,15,50,5,15);
   SLK_draw_pal_rectangle(32,4,36,12,selected==2?161:15);

   SLK_draw_pal_line(32,58,49,68,15);
   SLK_draw_pal_line(67,58,50,68,15);
   SLK_draw_pal_rectangle(32,58,36,12,selected==3?161:15);

   SLK_draw_pal_index(x-1,y-1,161);
   SLK_draw_pal_index(x-2,y-2,161);
   SLK_draw_pal_index(x+1,y-1,161);
   SLK_draw_pal_index(x+2,y-2,161);
   SLK_draw_pal_index(x-1,y+1,161);
   SLK_draw_pal_index(x-2,y+2,161);
   SLK_draw_pal_index(x+1,y+1,161);
   SLK_draw_pal_index(x+2,y+2,161);
}

static void mode_game_update()
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
