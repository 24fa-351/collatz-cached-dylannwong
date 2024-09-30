#include <stdio.h>
#include <stdlib.h>

// LRU cache

int cache_size = 0;
int cache_values = 0;

struct CacheData {
  int key;
  unsigned long long data;
};

struct CacheData *cache;

void cacheInitialization(int size) {
  cache_size = size;

  cache = (struct CacheData *)malloc(cache_size * sizeof(struct CacheData));
  for (int ix = 0; ix < size; ix++) {
    cache[ix].key = 0;
    cache[ix].data = -1;
  }
}

void cache_insert(unsigned long long n, unsigned long long result) {
  if (cache_size == cache_values) {
    for (int ix = cache_size - 1; ix > 0; ix--) {
      cache[ix] = cache[ix - 1];
    }

    cache[0].key = n;
    cache[0].data = result;
  } else {
    for (int ix = cache_values; ix > 0; ix--) {
      cache[ix] = cache[ix - 1];
    }

    cache[0].key = n;
    cache_values++;
    cache[0].data = result;
  }
}

unsigned long long cache_check(unsigned long long n) {

  for (int ix = 0; ix < cache_values; ix++) {

    if (n == cache[ix].key) {
      struct CacheData hit = cache[ix];
      for (int jx = ix; jx > 0; jx--) {
        cache[jx] = cache[jx - 1];
      }

      cache[0] = hit;

      return cache[0].data;
    }
  }
  return -1;
}

void cacheOut(int c_size) {

  printf("Cache Contents:\n");
  for (int ix = 0; ix < c_size; ix++) {
    printf("Key: %d, Data: %lld\n", cache[ix].key, cache[ix].data);
  }
}
