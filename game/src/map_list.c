/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <string.h>
#include <SLK/SLK.h>

#include "../../external/HLH_json.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "ressource.h"
#include "assets.h"
#include "map_list.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
uint8_t map_list_size = 0;
Map_entry *map_entries = NULL;
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

void map_list_load()
{
   unsigned size_in;
   void *mem_pak;

   mem_pak = lump_get("MAPLIST",LUMP_LIST,&size_in);
   HLH_json5_root *root = HLH_json_parse_char_buffer(mem_pak,size_in);
   HLH_json5 *array = HLH_json_get_object(&root->root,"maps");
   map_list_size = HLH_json_get_array_size(array);
   map_entries = util_malloc(sizeof(*map_entries)*map_list_size);
   for(int i = 0;i<map_list_size;i++)
   {
      HLH_json5 *el = HLH_json_get_array_item(array,i);
      const char *title = HLH_json_get_object_string(el,"title","(NULL)");
      strncpy(map_entries[i].title,title,12);
      map_entries[i].title[12] = '\0';
      map_entries[i].preview_id = (uint16_t)HLH_json_get_object_integer(el,"preview_id",0);
   }

   HLH_json_free(root);
   util_free(mem_pak);
}

void map_list_load_assets()
{
   assets_load_textures_begin();
   
   for(int i = 0;i<map_list_size;i++)
      assets_load_texture(map_entries[i].preview_id);

   assets_load_textures_end();
   ressource_flush();
}
//-------------------------------------
