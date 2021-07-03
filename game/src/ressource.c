/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

//External includes
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <SLK/SLK.h>
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
#include "ressource.h"

#define CUTE_PATH_IMPLEMENTATION
#include "../../external/cute_path.h"

#define HLH_JSON_IMPLEMENTATION
#define HLH_JSON_MALLOC util_malloc
#define HLH_JSON_FREE util_free
#define HLH_JSON_REALLOC util_realloc
#include "../../external/HLH_json.h"

#define HLH_PAK_IMPLEMENTATION
#define HLH_PAK_MALLOC util_malloc
#define HLH_PAK_FREE util_free
#define HLH_PAK_REALLOC util_realloc
#include "../../external/HLH_pak.h"
//-------------------------------------

//#defines
//-------------------------------------

//Typedefs
typedef struct
{
   char name[9];
   char path[256];
   Elump type;
}Lump;

typedef struct Pak_buffer
{
   char path[256];
   HLH_pak *pak;
   struct Pak_buffer *next;
}Pak_buffer;
//-------------------------------------

//Variables
struct
{
   uint32_t used;
   uint32_t size;
   Lump *data;
}lumps = {0};

Pak_buffer *pak_buffer = NULL;
//-------------------------------------

//Function prototypes
static Elump string_to_elump(const char *t);
static void lumps_push(Lump l);
static void add_json_path(const char *path);
static void add_json_mem(const char *path, const void *mem, int size);
static void add_pak_path(const char *path);
//-------------------------------------

//Function implementations

void ressource_add(const char *path)
{
   char ext[32] = {0};
   path_pop_ext(path,NULL,ext);

   if(strncmp(ext,"json",32)==0)
      add_json_path(path);
   else if(strncmp(ext,"pak",32)==0)
      add_pak_path(path);
}

void ressource_flush()
{
   Pak_buffer *b = pak_buffer;
   while(b)
   {
      Pak_buffer *next = b->next;
      HLH_pak_close(b->pak);
      util_free(b);

      b = next;
   }

   pak_buffer = NULL;
}

void lump_add(const char *name, const char *path, Elump type)
{
   if(strlen(name)>8)
      printf("lump name too long (max 8 characters)\n");
   char ext[32] = {0};
   path_pop_ext(path,NULL,ext);
   if(strncmp(ext,"json",32)==0)
   {
      add_json_path(path);
      return;
   }
   if(strncmp(ext,"pak",32)==0&&type==LUMP_PAK)
   {
      add_pak_path(path);
      return;
   }

   Lump l;
   l.type = type;
   strncpy(l.name,name,8);
   l.name[8] = '\0';
   strncpy(l.path,path,255);
   l.path[255] = '\0';
   lumps_push(l);
}

//Read lumps from back to front to enable overiding
void *lump_get(const char *name, Elump type, unsigned *size)
{
   for(int i = lumps.used-1;i>=0;i--)
   {
      if(strncmp(name,lumps.data[i].name,8)==0)
      {
         if(lumps.data[i].type!=type)
            printf("types do not match for lump %s\n",name);

         //Check for pak file
         char ext[32] = {0};
         path_pop_ext(lumps.data[i].path,NULL,ext);
         if(strncmp(ext,"pak",32)==0)
         {
            //Check if pak already opened
            Pak_buffer *b = pak_buffer;
            while(b)
            {
               if(strcmp(b->path,lumps.data[i].path)==0)
                  break;
               b = b->next;
            }
            if(b==NULL)
            {
               b = util_malloc(sizeof(*b));
               b->pak = HLH_pak_open(lumps.data[i].path,"r");
               strncpy(b->path,lumps.data[i].path,255);
               b->path[255] = '\0';
               b->next = pak_buffer;
               pak_buffer = b;
            }

            int index = HLH_pak_find(b->pak,name);
            *size = HLH_pak_size(b->pak,index);
            return HLH_pak_extract(b->pak,index);
         }

         //Raw reading
         FILE *f = fopen(lumps.data[i].path,"rb");
         if(!f)
         {
            printf("failed to open %s\n",lumps.data[i].path);
            *size = 0;
            return NULL;
         }
         fseek(f,0,SEEK_END);
         *size = ftell(f);
         fseek(f,0,SEEK_SET);
         uint8_t *buffer = util_malloc(*size+1);
         fread(buffer,*size,1,f);
         buffer[*size] = 0;
         fclose(f);
         return buffer;
      }
   }

   printf("lump %s not found\n",name);
   *size = 0;
   return NULL;
}

const char *lump_get_path(const char *name, Elump type)
{
   for(int i = lumps.used-1;i>=0;i--)
   {
      if(strncmp(name,lumps.data[i].name,8)==0)
      {
         if(lumps.data[i].type!=type)
            printf("types do not match for lump %s\n",name);
         
         return lumps.data[i].path;
      }
   }

   printf("lump %s not found\n",name);
   return NULL;
}

//Convert a string to the matching
//Elump type.
//Hashing for better performance
static Elump string_to_elump(const char *t)
{
   uint64_t hash = util_fnv64a(t);
   //printf("%s %lu\n",t,hash);

   switch(hash)
   {
   case 10188928075460420658U: return LUMP_PAL;
   case  2187779760063523436U: return LUMP_MUS;
   case  3806790633606677507U: return LUMP_JSON;
   case  7818530539252466654U: return LUMP_TEX;
   case  8440912394771940537U: return LUMP_WAV;
   default:                    return LUMP_ERROR;
   }
}

//Parse a json file and add all lumps to list
static void add_json_path(const char *path)
{
   char base_path[256] = {0};
   char tmp[256] = {0};
   path_pop(path,base_path,NULL);
   strcat(base_path,"/");

   HLH_json5_root *root = HLH_json_parse_file(path);
   //if(HLH_json_get_object_integer(&root->root,"version",0)!=ASSET_VERSION)
      //printf("invalid json version, expected version %d got version %d\n",ASSET_VERSION,HLH_json_get_object_integer(&root->root,"version",0));

   HLH_json5 *array = HLH_json_get_object(&root->root,"lumps");
   if(array==NULL)
      printf("no 'lumps' array in json\n");

   int count = HLH_json_get_array_size(array);
   for(int i = 0;i<count;i++)
   {
      HLH_json5 *el = HLH_json_get_array_item(array,i);
      int type = string_to_elump(HLH_json_get_object_string(el,"type","NULL"));
      if(type==LUMP_ERROR)
         printf("invalid lump type\n");

      strcpy(tmp,base_path);
      lump_add(HLH_json_get_object_string(el,"name","NULL"),strcat(tmp,HLH_json_get_object_string(el,"path","NULL")),type);
   }

   HLH_json_free(root);
}

//Same as add_json_path, but operates on memory
//instead of file
static void add_json_mem(const char *path, const void *mem, int size)
{
   char base_path[256] = {0};
   char tmp[256] = {0};
   path_pop(path,base_path,NULL);
   strcat(base_path,"/");

   HLH_json5_root *root = HLH_json_parse_char_buffer(mem,size);

   HLH_json5 *array = HLH_json_get_object(&root->root,"lumps");
   if(array==NULL)
      printf("no 'lumps' array in json\n");

   int count = HLH_json_get_array_size(array);
   for(int i = 0;i<count;i++)
   {
      HLH_json5 *el = HLH_json_get_array_item(array,i);
      int type = string_to_elump(HLH_json_get_object_string(el,"type","NULL"));
      if(type==LUMP_ERROR)
         printf("invalid lump type\n");

      strcpy(tmp,base_path);
      lump_add(HLH_json_get_object_string(el,"name","NULL"),strcat(tmp,HLH_json_get_object_string(el,"path","NULL")),type);
   }

   HLH_json_free(root);
}

//Parse a pak file and add to list
static void add_pak_path(const char *path)
{
   //Add pak to list
   Pak_buffer *b = util_malloc(sizeof(*b));
   b->pak = HLH_pak_open(path,"r");
   strncpy(b->path,path,255);
   b->path[255] = '\0';
   b->next = pak_buffer;
   pak_buffer = b;

   //Add all files in pak to lump array
   int count = HLH_pak_count(b->pak);
   for(int i = 0;i<count;i++)
   {
      //Parse json files seperately
      if(HLH_pak_type(b->pak,i)==LUMP_JSON)
      {
         void *mem = HLH_pak_extract(b->pak,i);
         int size = HLH_pak_size(b->pak,i);
         add_json_mem(path,mem,size);
         util_free(mem);
      }
      else
      {
         lump_add(HLH_pak_name(b->pak,i),path,HLH_pak_type(b->pak,i));
      }
   }
}

//Add a lump to the lump array.
//Array will dynamically expand if more 
//space is needed
static void lumps_push(Lump l)
{
   //Allocate memory for list
   if(lumps.data==NULL)
   {
      lumps.size = 16;
      lumps.used = 0;
      lumps.data = util_malloc(sizeof(*lumps.data)*lumps.size);
   }
  
   lumps.data[lumps.used++] = l;
   if(lumps.used==lumps.size)
   {
      lumps.size+=16;
      lumps.data = util_realloc(lumps.data,sizeof(*lumps.data)*lumps.size);
   }
}
//-------------------------------------
