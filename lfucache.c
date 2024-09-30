#include <stdio.h>
#include <stdlib.h>

int lfu_size;
int lfu_values = 0;
// LFU cache
struct LfuCacheData {
  unsigned long long key;
  int hits;
  unsigned long long data;
};

struct LfuCacheData *lfu;

void lfuCacheInitialization(int size) {
  lfu_size = size;

  lfu = (struct LfuCacheData *)malloc(lfu_size * sizeof(struct LfuCacheData));
  for (int ix = 0; ix < size; ix++) {
    lfu[ix].key = 0;
    lfu[ix].data = -1;
    lfu[ix].hits = 0;
  }
}

void lfu_insert(unsigned long long n, unsigned long long result) {
  if (lfu_size == lfu_values) {
    struct LfuCacheData least = lfu[0];
    for (int ix = 0; ix < lfu_size; ix++) {
      if (least.hits > lfu[ix].hits) {
        least = lfu[ix];
      }
    }
    least.key = n;
    least.data = result;
    least.hits = 0;

  } else {
    // printf("new value\n");
    for (int ix = 0; ix < lfu_size; ix++) {
      if (lfu[ix].data == -1) {
        lfu[ix].data = result;
        lfu[ix].key = n;
        lfu_values++;
        break;
      }
    }
  }
}
unsigned long long lfu_check(unsigned long long n) {
  for (int ix = 0; ix < lfu_size; ix++) {
    if (n == lfu[ix].key) {
      lfu[ix].hits++;
      return lfu[ix].data;
    }
  }
  return -1;
}

void lfuOut(int lfu_size) {
  printf("LFU Contents:\n");
  for (int ix = 0; ix < lfu_size; ix++) {
    printf("Key: %lld, Data: %lld Hits: %d\n", lfu[ix].key, lfu[ix].data,
           lfu[ix].hits);
  }
}