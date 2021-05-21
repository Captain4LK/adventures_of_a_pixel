/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _SOUND_H_

#define _SOUND_H_

#include <SDL2/SDL_mixer.h>

extern int current_music;
extern Mix_Music *music[2];

extern Mix_Chunk *sound_jump;
extern Mix_Chunk *sound_die;
extern Mix_Chunk *sound_fireball;

#endif
