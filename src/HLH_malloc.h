/*
malloc replacement

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _HLH_MALLOC_H_

#define _HLH_MALLOC_H_

#include <stdint.h>

#ifndef HLH_MALLOC_MALLOC
#define HLH_MALLOC_MALLOC malloc
#endif

#ifndef HLH_MALLOC_FREE
#define HLH_MALLOC_FREE free
#endif

#ifndef HLH_MALLOC_REALLOC
#define HLH_MALLOC_REALLOC realloc
#endif

#ifndef HLH_MALLOC_LOG
#define HLH_MALLOC_LOG printf
#endif

typedef struct HLH_memory_node
{
  int32_t size;
  struct HLH_memory_node *next;
}HLH_memory_node;

typedef struct
{
   int32_t block_size;
   void *addr;
   HLH_memory_node *sfirst, *slast;
}HLH_block_manager;

typedef struct
{
   int bmanage_total;
   int m_instance;
   int mem_break ;
   int malloc_max_size;
   int malloc_min_size;
   HLH_block_manager bmanage[5];
}HLH_malloc_instance;

void  HLH_malloc_default(HLH_malloc_instance *i);
void  HLH_malloc_set_max_memory_used(HLH_malloc_instance *mi, int bytes);
void  HLH_malloc_set_min_memory_required(HLH_malloc_instance *mi, int bytes);
void  HLH_malloc_malloc_init(HLH_malloc_instance *mi);
void *HLH_malloc(HLH_malloc_instance *mi, uint32_t size);
void *HLH_realloc(HLH_malloc_instance *mi, void *ptr, uint32_t size);
void  HLH_free(HLH_malloc_instance *mi, void *ptr);
void  HLH_malloc_memory_report(HLH_malloc_instance *mi);

#endif

#ifdef HLH_MALLOC_IMPLEMENTATION
#ifndef HLH_MALLOC_IMPLEMENTATION_ONCE
#define HLH_MALLOC_IMPLEMENTATION_ONCE

static void HLH_block_manager_init(HLH_block_manager *b, void *block, long block_size);
static void *HLH_block_manager_alloc(HLH_block_manager *b, long size);
static void HLH_block_manager_free(HLH_block_manager *b, void *ptr);
static long HLH_block_manager_pointer_size(HLH_block_manager *b, void *ptr);
static void HLH_block_manager_report(HLH_block_manager *b);

void HLH_malloc_default(HLH_malloc_instance *i)
{
   i->bmanage_total = 0;
   i->m_instance = 0;
   i->mem_break = -1;
   i->malloc_max_size = 1<<25;
   i->malloc_min_size = 1<<24;
}

void HLH_malloc_set_max_memory_used(HLH_malloc_instance *mi, int bytes)
{
   mi->malloc_max_size = bytes;
   if(mi->malloc_min_size>mi->malloc_max_size) //TODO: < in golgotha source code, why?
      mi->malloc_min_size = mi->malloc_max_size;
}

void HLH_malloc_set_min_memory_required(HLH_malloc_instance *mi, int bytes)
{
   mi->malloc_min_size = bytes;
}

void HLH_malloc_malloc_init(HLH_malloc_instance *mi)
{
   if(mi->bmanage_total)
   {
      HLH_MALLOC_LOG("HLH_malloc: already initialized\n");
      return;
   }

   void *mem;
   int32_t size = mi->malloc_max_size;
   for(mem = NULL;!mem&&size>=mi->malloc_min_size;)
   {
      mem = HLH_MALLOC_MALLOC(size);
      if(!mem) 
         size-=0x100;        
   }

   if(mem)
   {
      HLH_block_manager_init(&mi->bmanage[mi->bmanage_total],mem,size);
      mi->bmanage_total++; 
      HLH_MALLOC_LOG("HLH_malloc: allocated %d bytes for allocator\n",size);
      size-=0x1000;
   }  
   else
   {
      HLH_MALLOC_LOG("HLH_malloc: not enough memory\n");
   }
}

void *HLH_malloc(HLH_malloc_instance *mi, uint32_t size)
{
   if(size==0)
      HLH_MALLOC_LOG("HLH_malloc: tried to malloc 0 bytes\n");

   mi->m_instance++;
   if(mi->m_instance==mi->mem_break)
      HLH_MALLOC_LOG("HLH_malloc: mem break\n");

   if(!mi->bmanage_total) 
   {
      return HLH_MALLOC_MALLOC(size);
   }

   size = (size+3)&(0xffffffff-3);

   for(int i = 0;i<mi->bmanage_total;i++)
   {
      void *a = HLH_block_manager_alloc(&mi->bmanage[i],size);
      if(a) 
         return a;
   }

   HLH_MALLOC_LOG("HLH_malloc: Out of memory\n");
   return NULL;
}

void *HLH_realloc(HLH_malloc_instance *mi, void *ptr, uint32_t size)
{
   if(!ptr) 
      return HLH_malloc(mi,size);

   if(!mi->bmanage_total) 
   {
      void *d = HLH_MALLOC_REALLOC(ptr,size); 
      return d;
   }

   if(size==0) 
   { 
      HLH_free(mi,ptr); 
      return NULL; 
   }

   int32_t old_size = 0;
   for(int i = 0;i<mi->bmanage_total;i++)
   {
      if(ptr>=(void *)mi->bmanage[i].sfirst && 
         ptr<=(void *)(((char *)mi->bmanage[i].sfirst)+mi->bmanage[i].block_size))
      {
         old_size = HLH_block_manager_pointer_size(&mi->bmanage[i],ptr);  

         if(ptr<=(void *)mi->bmanage[i].slast)
         {
            void *nptr = HLH_malloc(mi,size);
            if((int32_t)size>old_size)
               memcpy(nptr,ptr,old_size);
            else
               memcpy(nptr,ptr,size);

            HLH_block_manager_free(&mi->bmanage[i],ptr);

            return nptr;
         }
      }
   }

   HLH_MALLOC_LOG("HLH_malloc: realloc() bad pointer\n");
   return NULL;
}

void HLH_free(HLH_malloc_instance *mi, void *ptr)
{
   if(!mi->bmanage_total) 
   { 
      HLH_MALLOC_FREE(ptr); 
      return ; 
   }

   for(int i = 0;i<mi->bmanage_total;i++)
   {
      if(ptr>=(void *)mi->bmanage[i].sfirst)  // is the pointer in this block?
      {
         if(ptr<=(void *)mi->bmanage[i].slast)  // is it in static space?
         {
            HLH_block_manager_free(&mi->bmanage[i],ptr);
            return ;
         } 
      }
   }

   HLH_MALLOC_LOG("HLH_malloc: free() bad pointer\n");
}

void HLH_malloc_memory_report(HLH_malloc_instance *mi)
{
   if(!mi->bmanage_total)
      return;

   for(int i = 0;i<mi->bmanage_total;i++)
   {
      HLH_block_manager_report(&mi->bmanage[i]);
   }
}

static void HLH_block_manager_init(HLH_block_manager *b, void *block, long block_size)
{
   b->block_size = block_size;
   b->addr = block;

   b->sfirst=(HLH_memory_node *)(((char *)block));   
   b->slast = b->sfirst;
   b->sfirst->size=-(block_size-(int32_t)sizeof(HLH_memory_node));
   b->sfirst->next=NULL;
}

static void *HLH_block_manager_alloc(HLH_block_manager *b, long size)
{
   HLH_memory_node *s = b->sfirst;
   if(!s) 
      return NULL;
   for(;s&&-s->size<size;s = s->next);  
   if(!s)
      return NULL;
   s->size = -s->size;

   if(s->size-size>sizeof(HLH_memory_node)+4)  //is there enough space to split the block?
   {    
      HLH_memory_node *p = (HLH_memory_node *)((char *)s+sizeof(HLH_memory_node)+size);
      if(s==b->slast)
         b->slast = p;
      p->size = -(s->size-size-(int32_t)sizeof(HLH_memory_node));
      p->next=s->next;
      s->next=p;
      s->size=size;
   }

   return (void *)(((char *)s)+sizeof(HLH_memory_node));
}

static void HLH_block_manager_free(HLH_block_manager *b, void *ptr)
{
   HLH_memory_node *o=(HLH_memory_node *)(((char *)ptr)-sizeof(HLH_memory_node)),*last = NULL;

   if(o->next&&o->next->size<0)   //see if we can add into next block
   {
      if (o->next==b->slast)
         b->slast = o;
      o->size+=-o->next->size+sizeof(HLH_memory_node);
      o->next = o->next->next;
   }

   HLH_memory_node *n = b->sfirst;
   for(;n&&n!=o;n=n->next)
      last = n;

   if(last&&last->size<0)
   {
      if(o==b->slast)
         b->slast = last;
      last->next=o->next;
      last->size-=o->size+sizeof(HLH_memory_node);	
   }
   else
      o->size=-o->size;            
}

static long HLH_block_manager_pointer_size(HLH_block_manager *b, void *ptr)
{
   return ((HLH_memory_node *)(((char *)ptr)-sizeof(HLH_memory_node)))->size;
}

static void HLH_block_manager_report(HLH_block_manager *b)
{
   HLH_MALLOC_LOG("************** Block size = %d ***************\n",b->block_size);
   HLH_MALLOC_LOG("Index\tBase\t\t(Offset)\t      Size\n");
   int i = 0;
   HLH_memory_node * f=b->sfirst;
   int32_t f_total = 0, a_total = 0;

   for(;f;f = f->next,i++)
   {
      HLH_MALLOC_LOG("%4d\t%p\t(%10ld)\t%10d",i,f,((char *)f-(char *)b->sfirst),f->size);
      if(f->size>0)
      {
         a_total+=f->size;
      }
      else
      {
         f_total+=-f->size;
      }

      HLH_MALLOC_LOG("\n");
   }

   HLH_MALLOC_LOG("**************** Block summary : %d free, %d allocated\n",f_total,a_total);
}

#endif
#endif
