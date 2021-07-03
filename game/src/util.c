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
#include <SLK/SLK.h>

#define CRUSH_C
#include "../../external/crush.c"

#define HLH_MALLOC_IMPLEMENTATION
#define HLH_MALLOC_MALLOC SLK_system_malloc
#define HLH_MALLOC_FREE SLK_system_free
#define HLH_MALLOC_REALLOC SLK_system_realloc
#include "../../external/HLH_malloc.h"
//-------------------------------------

//Internal includes
#include "config.h"
#include "util.h"
//-------------------------------------

//#defines
#define FNV_64_PRIME ((uint64_t)0x100000001b3ULL)
#define FNV_32_PRIME ((uint32_t)0x01000193)

#define SIGN(in) \
      (1|(in>>(sizeof(in)*8-1)))

#define FROM_INT(type,power) \
   type type##_from_int(int in) { return (type)in<<power; }

#define TO_INT(type,power) \
   int type##_to_int(type in) { return (int)(in>>power); }

#define DIV(type,con,power) \
   type type##_div(type a, type b) { return ((con)a*((con)1<<power))/b; }

#define MUL(type,con,power) \
   type type##_mul(type a, type b) { return ((con)a*(con)b)/((con)1<<power); }

#define ROUND(type,power,and) \
   type type##_round(type in) { int sign = SIGN(in); in*=sign; in = ((in+((type)1<<(power-1))))&(and); in*=sign; return in; }

#define FLOOR(type,and) \
   type type##_floor(type in) { int sign = SIGN(in); in*=sign; in&=(and); in*=sign; return in; }

#define CEIL(type,power,and) \
   type type##_ceil(type in) { int sign = SIGN(in); in*=sign; in = (in+((type)1<<power)-1)&(and); in*=sign; return in; }

#define SQRT(type,con,shift) \
   type type##_sqrt(type in) { int sign = SIGN(in); in*=sign; con result = 0, a = (con)in<<(shift/2), b = (con)1L<<(shift*2-2); while(b>a) b>>=2; \
   while(b) { if(a>=result+b) { a-=result+b; result = result+2*b; } b>>=2; result>>=1; } return result*sign; }

#define DEG2ANGLE(type) \
   type type##_deg_to_angle(type in) { return type##_div(type##_mul(type##_from_int(8),in),type##_from_int(360)); }

#define ANGLE2DEG(type) \
   type type##_angle_to_deg(type in) { return type##_mul(type##_from_int(45),in); } 

#define RAD2ANGLE(type,pi) \
   type type##_rad_to_angle(type in) { return type##_div(type##_mul(type##_from_int(8),in),2*pi); }

#define ANGLE2RAD(type,pi) \
   type type##_angle_to_rad(type in) { return type##_div(type##_mul(pi,in),type##_from_int(4)); }
//-------------------------------------

//Typedefs
//-------------------------------------

//Variables
static int seed = 0;
static HLH_malloc_instance memory;
//-------------------------------------

//Function prototypes
//-------------------------------------

//Function implementations

void util_compress(FILE *in, FILE *out)
{
   char *buffer_in = NULL;
   char *buffer_out = NULL;
   int32_t size = 0;
   fseek(in,0,SEEK_END);
   size = ftell(in);
   fseek(in,0,SEEK_SET);

   buffer_in = util_malloc(size+1);
   buffer_out = util_malloc(size+1);

   fread(buffer_in,size,1,in);
   buffer_in[size] = 0;

   fwrite(&size,4,1,out);
   size = crush_encode(buffer_in,size,buffer_out,size,9);
   fwrite(buffer_out,size,1,out);

   util_free(buffer_in);
   util_free(buffer_out);
}

void util_compress_path(const char *path_in, const char *path_out)
{
   FILE *in = fopen(path_in,"rb");
   FILE *out = fopen(path_out,"wb");
   util_compress(in,out);
   fclose(in);
   fclose(out);
}

void util_mem_compress(void *mem, int32_t length, FILE *out)
{
   char *buffer_out = util_malloc(length+1);

   fwrite(&length,4,1,out);
   int32_t size = crush_encode(mem,length,buffer_out,length,9);
   fwrite(buffer_out,size,1,out);

   util_free(buffer_out);
}

void *util_decompress(FILE *in, int *length)
{
   fread(length,4,1,in);
   char *buffer_in = NULL;
   int size = 0;
   fseek(in,0,SEEK_END);
   size = ftell(in)-4;
   fseek(in,4,SEEK_SET);
   buffer_in = util_malloc(size+1);
   char *buffer_out = util_malloc((*length)+1);
   fread(buffer_in,size,1,in);
   buffer_in[size] = 0;

   crush_decode(buffer_in,size,buffer_out,*length);
   buffer_out[*length] = 0;
   util_free(buffer_in);

   return buffer_out;
}

void *util_decompress_path(const char *path, int32_t *length)
{
   FILE *f = fopen(path,"rb");
   void *data = util_decompress(f,length);
   fclose(f);

   return data;
}

void *util_mem_decompress(void *mem, int32_t length_in, int32_t *length_out)
{
   *length_out = *((int32_t *)mem);
   char *buffer_out  = util_malloc((*length_out)+1);
   crush_decode(mem+4,length_in-4,buffer_out,*length_out);
   
   return buffer_out;
}

void util_malloc_init(int min, int max)
{
   HLH_malloc_default(&memory);
   HLH_malloc_set_min_memory_required(&memory,min);
   HLH_malloc_set_max_memory_used(&memory,max);
   HLH_malloc_init(&memory);
}

void *util_malloc(size_t size)
{
   return HLH_malloc(&memory,size);
}

void util_free(void *ptr)
{
   HLH_free(&memory,ptr);
}

void *util_realloc(void *ptr, size_t size)
{
   return HLH_realloc(&memory,ptr,size);
}

void util_malloc_report()
{
   HLH_malloc_memory_report(&memory);
}

uint64_t util_fnv64a(const char *str)
{
   uint64_t hval = 0xcbf29ce484222325ULL;
   unsigned char *s = (unsigned char *)str;
   while(*s)
   {
      hval^=(uint64_t)*s++;
      hval*=FNV_64_PRIME;
   }

   return hval;
}

uint32_t util_fnv32a(const char *str)
{
   uint32_t hval = 0x811c9dc5;
   unsigned char *s = (unsigned char *)str;
   while (*s) 
   {
      hval^=(uint32_t)*s++;
      hval *= FNV_32_PRIME;
   }

   return hval;
}

unsigned util_rand()
{
   static uint32_t w32_rtable[RNG_TABLE_SIZE];
   static int initialized = 0;

   if(!initialized)
   {
      uint32_t inc = 0xacd2d391, mul = 0xf34f9201, x = 0;
      for(int i = 0;i<RNG_TABLE_SIZE;i++)
      {     
         w32_rtable[i] = x;
         x = (x+inc)*mul;
      }
      initialized = 1;
   }

   seed = (seed+1)%RNG_TABLE_SIZE;
   return w32_rtable[seed];
}

int util_rand_get_state()
{
   return seed;
}

void util_rand_set_state(int state)
{
   seed = state%RNG_TABLE_SIZE;
}

FROM_INT(fixed22,10)
TO_INT(fixed22,10)
DIV(fixed22,int64_t,10)
MUL(fixed22,int64_t,10)
ROUND(fixed22,10,(INT32_MAX-(1<<10)))
FLOOR(fixed22,(INT32_MAX-(1<<10)))
CEIL(fixed22,10,(INT32_MAX-(1<<10)))
SQRT(fixed22,int64_t,32)
DEG2ANGLE(fixed22)
ANGLE2DEG(fixed22)
RAD2ANGLE(fixed22,205887);
ANGLE2RAD(fixed22,205887);
//-------------------------------------
