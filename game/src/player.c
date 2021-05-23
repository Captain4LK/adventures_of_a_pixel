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
//-------------------------------------

//Variables
struct Player player;
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

void player_update()
{
   //Player movement
   if(player.move_unlocked)
   {
      if(SLK_key_down(SLK_KEY_D)||SLK_gamepad_down(0,SLK_PAD_RIGHT))
      {
         if(map_get_pixel(player.map_x,player.map_y,player.x+1,player.y).n==BLACK.n)
            player.x++;
      }

      if(SLK_key_down(SLK_KEY_A)||SLK_gamepad_down(0,SLK_PAD_LEFT))
      {
         if(map_get_pixel(player.map_x,player.map_y,player.x-1,player.y).n==BLACK.n)
            player.x--;
      }
   }
   //-------------------------------------

   //Check if player has left map (x-axis)
   if(player.x>63)
   {
      player.x = 0;
      player.rx = player.x;
      player.ry = player.y;
      player.map_x++;
      
      terrain_needs_redraw = 1;
   }
   else if(player.x<0)
   {
      player.x = 63;
      player.rx = player.x;
      player.ry = player.y;
      player.map_x--;
      
      terrain_needs_redraw = 1;
   }
   //-------------------------------------

   //Gravity
   if(map_get_pixel(player.map_x,player.map_y,player.x,player.y+1).n==BLACK.n&&player.jump_time==0)
      player.y++;
   //-------------------------------------

   //Jumping
   if(player.jump_unlocked&&(SLK_key_pressed(SLK_KEY_SPACE)||SLK_gamepad_pressed(0,SLK_PAD_A)))
   {
      if(map_get_pixel(player.map_x,player.map_y,player.x,player.y+1).n!=BLACK.n)
      {
         player.jump_time = 10;
         player.jumps = player.double_jump_unlocked;
         Mix_PlayChannel(-1,sound_jump,0);
      }
      else if(player.jumps)
      {
         player.jump_time = 10;
         player.jumps = 0;
         Mix_PlayChannel(-1,sound_jump,0);
      }
   }
   if(player.jump_time>0&&player.jump_time<4)
   {
      player.jump_time--;
   }
   else if(player.jump_time>3)
   {
      if(map_get_pixel(player.map_x,player.map_y,player.x,player.y-1).n==BLACK.n)
      {
         player.y--;
         player.jump_time--;
      }
      else
      {
         player.jump_time = 0;
      }
   }
   //-------------------------------------

   //Check if player has left map (y-axis)
   if(player.y>63)
   {
      player.y = 0;
      player.rx = player.x;
      player.ry = player.y;
      player.map_y++;

      terrain_needs_redraw = 1;
   }
   if(player.y<0)
   {
      player.y = 63;
      player.rx = player.x;
      player.ry = player.y;
      player.map_y--;

      terrain_needs_redraw = 1;
   }
   //-------------------------------------

   //Damage collision
   if(SLK_rgb_sprite_get_pixel(SLK_layer_get(1)->type_1.target,player.x,player.y).a)
   {
      player.x = player.rx;
      player.y = player.ry;
      Mix_PlayChannel(-1,sound_die,0);
   }

   SLK_draw_rgb_color(player.x,player.y,player.color);
}
//-------------------------------------
