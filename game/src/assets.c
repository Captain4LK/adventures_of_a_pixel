/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "ressource.h"
#include "assets.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
SLK_Pal_sprite **textures = NULL;
static int8_t *textures_timeout = NULL;
//-------------------------------------

//Function prototypes
static SLK_Palette *palette_load(void *mem, int32_t size);
//-------------------------------------

//Function implementations

void assets_load_default()
{
   unsigned size_in;
   int32_t size_out;
   void *mem_pak, *mem_decomp;

   //Load font
   mem_pak = lump_get("FONT0",LUMP_TEX,&size_in);
   mem_decomp = util_mem_decompress(mem_pak,size_in,&size_out);
   SLK_draw_pal_set_font_sprite(SLK_pal_sprite_load_mem(mem_decomp,size_out));
   util_free(mem_pak);
   util_free(mem_decomp);

   //Load palette
   mem_pak = lump_get("PAL0",LUMP_PAL,&size_in);
   SLK_Palette *pal_new = palette_load(mem_pak,size_in);
   SLK_layer_set_palette(0,pal_new);
   SLK_layer_set_palette(1,pal_new);
   SLK_layer_set_palette(2,pal_new);
   util_free(mem_pak);

   ressource_flush();
}

void assets_load_textures_begin()
{
   if(textures!=NULL&&textures_timeout!=NULL)
   {
      for(int i = 0;i<UINT16_MAX;i++)
         textures_timeout[i]--;
   }
}

void assets_load_texture(uint16_t id)
{
   if(textures==NULL)
   {
      textures = util_malloc(sizeof(*textures)*UINT16_MAX);
      textures_timeout = util_malloc(sizeof(*textures_timeout)*UINT16_MAX);
      memset(textures,0,sizeof(*textures)*UINT16_MAX);
      memset(textures_timeout,0,sizeof(*textures_timeout)*UINT16_MAX);
   }

   textures_timeout[id] = config_texture_timeout;
   if(textures[id]!=NULL)
      return;

   char tmp[64];
   sprintf(tmp,"TEX%05d",id);

   unsigned size_in;
   int32_t size_out;
   void *mem_pak, *mem_decomp;
   mem_pak = lump_get(tmp,LUMP_TEX,&size_in);
   mem_decomp = util_mem_decompress(mem_pak,size_in,&size_out);
   SLK_Pal_sprite *n = SLK_pal_sprite_load_mem(mem_decomp,size_out);
   textures[id] = SLK_pal_sprite_create(n->width,n->height);
   for(int ty = 0;ty<n->height;ty++)
      for(int tx = 0;tx<n->width;tx++)
         textures[id]->data[tx*n->height+ty] = n->data[ty*n->width+tx];
   SLK_pal_sprite_destroy(n);
   util_free(mem_pak);
   util_free(mem_decomp);
}

void assets_load_textures_end()
{
   if(textures!=NULL&&textures_timeout!=NULL)
   {
      for(int i = 0;i<UINT16_MAX;i++)
      {
         if(textures_timeout[i]<=0)
         {
            textures_timeout[i] = 0;
            SLK_pal_sprite_destroy(textures[i]);
            textures[i] = NULL;
         }
      }
   }
}

static SLK_Palette *palette_load(void *mem, int32_t size)
{
   int pos = 0;
   SLK_Palette *p = malloc(sizeof(*p));
   p->used = *((uint8_t *)(mem)); pos++;
   p->used++;
   for(int i = 0;i<p->used;i++)
   {
      p->colors[i].r = *(((uint8_t *)mem)+pos); pos++;
      p->colors[i].g = *(((uint8_t *)mem)+pos); pos++;
      p->colors[i].b = *(((uint8_t *)mem)+pos); pos++;
      p->colors[i].a = *(((uint8_t *)mem)+pos); pos++;
   }

   return p;
}
//-------------------------------------
