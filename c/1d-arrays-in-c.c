#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
  int number;
  scanf("%d", &number);

  int *elements = calloc(number, sizeof(int));
  int element;
  for (int i = 0; i < number; i++) {
    scanf("%d", &element);
    *(elements + i) = element;
  }

  int sum = 0;
  for (int i = 0; i < number; i++) {
    sum += *(elements + i);
  }

  printf("%d\n", sum);

  return 0;
}
