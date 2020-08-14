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
#include "map.h"
#include "modes.h"
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

void player_update()
{
   //Player movement
   if(SLK_key_down(SLK_KEY_D))
   {
      if(map_get_pixel(player.map_x,player.map_y,player.x+1,player.y).n==BLACK.n)
         player.x++;
   }

   if(SLK_key_down(SLK_KEY_A))
   {
      if(map_get_pixel(player.map_x,player.map_y,player.x-1,player.y).n==BLACK.n)
         player.x--;
   }

   //Check if player has left map (x-axis)
   if(player.x>63)
   {
      player.x = 0;
      player.map_x++;
      
      terrain_needs_redraw = 1;
   }
   else if(player.x<0)
   {
      player.x = 63;
      player.map_x--;
      
      terrain_needs_redraw = 1;
   }

   //Gravity
   if(map_get_pixel(player.map_x,player.map_y,player.x,player.y+1).n==BLACK.n&&player.jump_time==0)
      player.y++;

   //Jumping
   if(SLK_key_pressed(SLK_KEY_SPACE))
   {
      if(map_get_pixel(player.map_x,player.map_y,player.x,player.y+1).n!=BLACK.n)
      {
         player.jump_time = 10;
         player.jumps = player.double_jump_unlocked;
      }
      else if(player.jumps)
      {
         player.jump_time = 10;
         player.jumps = 0;
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

   if(player.y>63)
   {
      player.y = 0;
      player.map_y++;

      terrain_needs_redraw = 1;
   }

   SLK_draw_rgb_color(player.x,player.y,player.color);
}
//-------------------------------------
