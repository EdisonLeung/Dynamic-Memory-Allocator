/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 1 - Inferring Mystery Cache Geometries
 *
 * Name(s): Edison Leung 
 * NetID(s): 2136014
 *
 * NOTES:
 * 1. When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 *
 * 2. Do NOT change the provided main function, especially the print statement.
 * If you do so, the autograder may fail to grade your code even if it produces
 * the correct result.
 */

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"


/* Returns the size (in B) of each block in the cache. */
int get_block_size(void) {
  int size = 0;
  flush_cache();
  access_cache(0);
  while (access_cache(size)) {
     size++;
  }
  return size;
}


/* Returns the size (in B) of the cache. */
int get_cache_size(int block_size) {
  int size = 0;
  int i;
  flush_cache();
  access_cache(0);

  while(access_cache(0)) {
     size += block_size;
     flush_cache();
     for (i = 0; i <= size; i+=block_size) {
        access_cache(i);
     }
  } 
  return size;
}


/* Returns the associativity of the cache. */
int get_cache_assoc(int cache_size) {
  int assoc = 0;
  int i;
  flush_cache();
  access_cache(0);
  while(access_cache(0)) {
     assoc++;
     flush_cache();
     for(i = 0; i <= assoc; i++) {
        access_cache(i*cache_size);
     } 
  } 
  
  return assoc;
}


/* Run the functions above on a given cache and print the results. */
int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
