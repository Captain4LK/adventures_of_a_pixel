/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _PLAYER_H_

#define _PLAYER_H_

struct Player
{
   SLK_Color color;
   int map_x;
   int map_y;
   int x;
   int y;
   int rx;
   int ry;
   int jump_time;
   int jumps;
   int double_jump_unlocked;
   int move_unlocked;
   int jump_unlocked;
};
extern struct Player player;

void player_update();

#endif
