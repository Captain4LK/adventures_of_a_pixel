/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _CONFIG_H_

#define _CONFIG_H_

#define XRES 170
#define YRES 96
#define FPS 20 //Beyond cinematic
#define MEM_MIN (1024*1024*8)
#define MEM_MAX (1024*1024*16)

#define BLACK SLK_color_create(0,0,0,255)

#define RNG_TABLE_SIZE 512

extern SLK_key config_jump;
extern unsigned config_texture_timeout;

void ini_parse(const char *path);

#endif
