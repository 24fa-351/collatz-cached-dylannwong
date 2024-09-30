#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.c"
#include "lfucache.c"

int cache_acceses = 0;
int CACHE_HITS = 0;

unsigned long long (*check_provider)(unsigned long long);
void (*insert_provider)(unsigned long long, unsigned long long);
unsigned long long (*provider)(unsigned long long);

unsigned long long collatz_c(unsigned long long num) {

  if (num == 1) {

    return 0;
  }

  if (num % 2 == 0) {

    return 1 + provider(num / 2);

  } else {

    return 1 + provider((num * 3) + 1);
  }
}

unsigned long long collatz_wrapper(unsigned long long n) {

  cache_acceses++;

  unsigned long long cache_data = check_provider(n);

  if (cache_data != -1) {
    CACHE_HITS++;
    return cache_data;
  }

  unsigned long long result;

  if (n == 1) {
    result = 0;
  } else {
    if (n % 2 == 0) {

      result = 1 + collatz_wrapper(n / 2);

    } else {

      result = 1 + collatz_wrapper((n * 3) + 1);
    }
  }
  insert_provider(n, result);

  return result;
}

int main(int argc, char *argv[]) {

  // open file and set header
  FILE *fpt;
  fpt = fopen("data.csv", "a");
  // fprintf(fpt, "info, CPU, cache_hit_rate, cache_size, sample_count,
  // range_size\n");

  // puts arguments in variables
  int num_times = atoi(argv[1]);
  int min_num = atoi(argv[2]);
  int max_num = atoi(argv[3]);
  char *cache_type = argv[4];
  int cache_size = atoi(argv[5]);

  // looping N times printing out steps each time

  srand(time(NULL));

  if (strcmp(cache_type, "LRU") == 0) {
    cacheInitialization(cache_size);
    check_provider = &cache_check;
    insert_provider = &cache_insert;
    provider = &collatz_wrapper;
  } else if (strcmp(cache_type, "LFU") == 0) {
    lfuCacheInitialization(cache_size);
    provider = &collatz_wrapper;
    insert_provider = &lfu_insert;
    check_provider = &lfu_check;
  } else {
    provider = &collatz_c;
  }

  for (int i = 0; i < num_times; ++i) {

    int num = rand() % (max_num - min_num + 1) + min_num;

    unsigned long long step = provider(num);

    printf("%lld\n", step);
  }

  float hit_percentage = (float)CACHE_HITS / cache_acceses * 100;
  printf("Hit percent: %f", hit_percentage);
  printf("HIT: %d", CACHE_HITS);
  fprintf(fpt, "%s , %.2f, %d, %d, %d\n", cache_type, hit_percentage,
          cache_size, num_times, max_num);

  fclose(fpt);

  return 0;
}
