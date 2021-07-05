/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _MAP_LIST_H_

#define _MAP_LIST_H_

typedef struct
{
   uint16_t preview_id;
   uint16_t map_id;
   uint16_t pal_front_id;
   uint16_t pal_back_id;
   char title[13];
}Map_entry;

extern uint8_t map_list_size;
extern Map_entry *map_entries;

void map_list_load();
void map_list_load_assets();

#endif
