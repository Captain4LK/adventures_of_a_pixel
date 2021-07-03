/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _ASSETS_H_

#define _ASSETS_H_

extern SLK_Pal_sprite **textures;

void assets_load_default();
void assets_load_textures_begin();
void assets_load_texture(uint16_t id);
void assets_load_textures_end();

#endif
