#include <stdio.h>
#include <stdlib.h>

    int steps = 0;

unsigned long long collatz_c(unsigned long long num) {


  if (num == 1) {

    printf(" steps: ");

    return steps;
  }

  steps += 1;

  if (num % 2 == 0) {

    return collatz_c(num / 2);

  } else {

    return collatz_c((num * 3) + 1);
  }
}

unsigned long long collatz_wrapper() {}

int main(int argc, char *argv[]) {

  //open file and set header
  FILE *fpt;
  fpt = fopen("data.csv", "a");
  fprintf(fpt, "N, Min, Max, Steps\n");

  //puts arguments in variables
  int num_times = atoi(argv[1]);

  int min_num = atoi(argv[2]);

  int max_num = atoi(argv[3]);


    
  for (int i = 0; i < num_times; ++i) {

    
    int num = rand() % (max_num - min_num + 1) + min_num;
    
    int step = collatz_c(num);
    if(i==1) {
        fprintf(fpt, "%d", step);
    }

    printf("%d ", step);

    printf("\n");

    steps = 0;
  }
    

  fclose(fpt);

  return 0;
}
