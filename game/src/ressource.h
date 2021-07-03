/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _RESSOURCE_H_

#define _RESSOURCE_H_

typedef enum
{
   LUMP_ERROR, LUMP_PAL, LUMP_MUS, LUMP_JSON, LUMP_PAK, LUMP_TEX, LUMP_WAV,
}Elump;

void ressource_add(const char *path);
void ressource_flush();
void lump_add(const char *name, const char *path, Elump type);
void *lump_get(const char *name, Elump type, unsigned *size);
const char *lump_get_path(const char *name, Elump type);

#endif
