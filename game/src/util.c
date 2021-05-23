/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <time.h>
#include <SLK/SLK.h>
#include <SDL2/SDL_mixer.h>

#define HLH_MALLOC_IMPLEMENTATION
#include "../../shared/HLH_malloc.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "player.h"
#include "mode.h"
#include "sound.h"
#include "map.h"
#include "util.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
HLH_malloc_instance mem_game;
HLH_malloc_instance mem_util;
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations
//-------------------------------------
