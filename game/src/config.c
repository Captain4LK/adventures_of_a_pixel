/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <stdlib.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
SLK_key config_jump = SLK_KEY_SPACE;
unsigned config_texture_timeout = 1;
//-------------------------------------

//Function prototypes
static char *ini( const char *s );
static SLK_key strtokey(const char *s);
//-------------------------------------

//Function implementations

void ini_parse(const char *path)
{
   FILE *in = fopen(path,"rb");
   if(!in)
      return;
   char *buffer_in = NULL;
   int32_t size = 0;
   fseek(in,0,SEEK_END);
   size = ftell(in);
   if(size==0)
      return;
   fseek(in,0,SEEK_SET);

   buffer_in = util_malloc(size+1);

   fread(buffer_in,size,1,in);
   buffer_in[size] = 0;
   fclose(in);

   char *kv = ini(buffer_in);

   for(char *iter = kv;iter[0];)
   {
      //Read key
      uint64_t hash_key = util_fnv64a(iter);
      //printf("key: %s;%luU\n",iter,hash_key);
      while(*iter++);
      switch(hash_key)
      {
      case 16940139219101328589U: config_jump = strtokey(iter); break; //"jump"
      case 11034882399129047948U: config_texture_timeout = atoi(iter); break; //"texture_timeout"
      }
      //printf("val: '%s'\n", iter);
      while(*iter++);
   }
   
   if(kv!=NULL)
      util_free(kv);
   util_free(buffer_in);
}


//Ini parser by r-lyeh: https://github.com/r-lyeh/tinybits
static char *ini( const char *s )
{
   char *map = 0;
   int mapcap = 0, maplen = 0;
   enum { DEL, REM, TAG, KEY, SUB, VAL } fsm = DEL;
   const char *cut[6] = {0}, *end[6] = {0};
    while(*s)
    {
        while( *s && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') ) ++s;
        /**/ if( *s == ';' ) cut[fsm = REM] = ++s;
        else if( *s == '[' ) cut[fsm = TAG] = ++s;
        else if( *s == '+' ) cut[fsm = SUB] = ++s;
        else if( *s == '=' ) cut[fsm = VAL] = ++s;
        else if( *s > ' ' && *s <= 'z' && *s != ']' ) cut[fsm = KEY] = cut[SUB] = end[SUB] = s;
        else { ++s; continue; }
        /**/ if( fsm == REM ) { while(*s && *s != '\r'&& *s != '\n') ++s; }
        else if( fsm == TAG ) { while(*s && *s != '\r'&& *s != '\n'&& *s != ']') ++s; end[fsm] = s; }
        else if( fsm == KEY ) { while(*s && *s >  ' ' && *s <= 'z' && *s != '=') ++s; end[fsm] = s; }
        else if( fsm == SUB ) { while(*s && *s >  ' ' && *s <= 'z' && *s != '=') ++s; end[fsm] = s; }
        else if( fsm == VAL ) { while(*s && *s >= ' ' && *s <= 'z' && *s != ';') ++s; end[fsm] = s;
            while( end[fsm][-1] == ' ' ) --end[fsm];
            char buf[256] = {0}, *key = buf;
            if( end[TAG] - cut[TAG] ) key += sprintf(key, "%.*s.", (int)(end[TAG] - cut[TAG]), cut[TAG] );
            if( end[KEY] - cut[KEY] ) key += sprintf(key,  "%.*s", (int)(end[KEY] - cut[KEY]), cut[KEY] );
            if( end[SUB] - cut[SUB] ) key += sprintf(key, ".%.*s", (int)(end[SUB] - cut[SUB]), cut[SUB] );
            int reqlen = (key - buf) + 1 + (end[VAL] - cut[VAL]) + 1 + 1;
            if( (reqlen + maplen) >= mapcap ) map = util_realloc( map, mapcap += reqlen + 512 );
            sprintf( map + maplen, "%.*s%c%.*s%c%c", (int)(key - buf), buf, 0, (int)(end[VAL] - cut[VAL]), cut[VAL], 0, 0 );
            maplen += reqlen - 1;
        }
    }
    return map;
}

static SLK_key strtokey(const char *s)
{
   uint64_t hash_key = util_fnv64a(s);
   //printf("ikey: %s;%luU\n",s,hash_key);
   switch(hash_key)
   {
   case 12638187200555641996U: return SLK_KEY_A;
   case 12638190499090526629U: return SLK_KEY_B;
   case 12638189399578898418U: return SLK_KEY_C;
   case 12638183902020757363U: return SLK_KEY_D;
   case 12638182802509129152U: return SLK_KEY_E;
   case 12638186101044013785U: return SLK_KEY_F;
   case 12638185001532385574U: return SLK_KEY_G;
   case 12638197096160295895U: return SLK_KEY_H;
   case 12638195996648667684U: return SLK_KEY_I;
   case 12638199295183552317U: return SLK_KEY_J;
   case 12638198195671924106U: return SLK_KEY_K;
   case 12638192698113783051U: return SLK_KEY_L;
   case 12638191598602154840U: return SLK_KEY_M;
   case 12638194897137039473U: return SLK_KEY_N;
   case 12638193797625411262U: return SLK_KEY_O;
   case 12638205892253321583U: return SLK_KEY_P;
   case 12638204792741693372U: return SLK_KEY_Q;
   case 12638208091276578005U: return SLK_KEY_R;
   case 12638206991764949794U: return SLK_KEY_S;
   case 12638201494206808739U: return SLK_KEY_T;
   case 12638200394695180528U: return SLK_KEY_U;
   case 12638203693230065161U: return SLK_KEY_V;
   case 12638202593718436950U: return SLK_KEY_W;
   case 12638214688346347271U: return SLK_KEY_X;
   case 12638213588834719060U: return SLK_KEY_Y;
   case 12638216887369603693U: return SLK_KEY_Z;
   case 12638135523509116079U: return SLK_KEY_0;
   case 12638134423997487868U: return SLK_KEY_1;
   case 12638137722532372501U: return SLK_KEY_2;
   case 12638136623020744290U: return SLK_KEY_3;
   case 12638131125462603235U: return SLK_KEY_4;
   case 12638130025950975024U: return SLK_KEY_5;
   case 12638133324485859657U: return SLK_KEY_6;
   case 12638132224974231446U: return SLK_KEY_7;
   case 12638144319602141767U: return SLK_KEY_8;
   case 12638143220090513556U: return SLK_KEY_9;
   case  4858524775536387045U: return SLK_KEY_SPACE;
   default: return SLK_KEY_NONE;
   }
}
//-------------------------------------
