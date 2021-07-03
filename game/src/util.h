/*
Adventures of a pixel - a low res plattformer

Written in 2021 by Lukas Holzbeierlein (Captain4LK) email: captain4lk [at] tutanota [dot] com

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 
*/

#ifndef _UTIL_H_

#define _UTIL_H_

#define UTIL_MAX(a,b) \
   ((a)>(b)?(a):(b))

#define UTIL_MIN(a,b) \
   ((a)<(b)?(a):(b))

typedef int32_t fixed22;

void  util_compress(FILE *in, FILE *out);
void  util_compress_path(const char *path_in, const char *path_out);
void  util_mem_compress(void *mem, int32_t length, FILE *out);
void *util_decompress(FILE *in, int32_t *length);
void *util_decompress_path(const char *path, int32_t *length);
void *util_mem_decompress(void *mem, int32_t length_in, int32_t *length_out);

void util_malloc_init(int min, int max);
void *util_malloc(size_t size);
void util_free(void *ptr);
void *util_realloc(void *ptr, size_t size);
void util_malloc_report();

uint64_t util_fnv64a(const char *str);
uint32_t util_fnv32a(const char *str);

unsigned util_rand();
int util_rand_get_state();
void util_rand_set_state(int state);

fixed22 fixed22_from_int(int in);
int     fixed22_to_int(fixed22 in);
fixed22 fixed22_div(fixed22 a, fixed22 b);
fixed22 fixed22_mul(fixed22 a, fixed22 b);
fixed22 fixed22_round(fixed22 in);
fixed22 fixed22_floor(fixed22 in);
fixed22 fixed22_ceil(fixed22 in);
fixed22 fixed22_sqrt(fixed22 in);
fixed22 fixed22_deg_to_angle(fixed22 in);
fixed22 fixed22_rad_to_angle(fixed22 in);
fixed22 fixed22_angle_to_deg(fixed22 in);
fixed22 fixed22_angle_to_rad(fixed22 in);

#endif
