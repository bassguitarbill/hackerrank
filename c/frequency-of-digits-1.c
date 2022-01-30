#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

  int digitFrequencies[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char s[1024];

  scanf("%[^\n]%c", &s);
  int i = 0;
  while(*(s + i) != NULL) {
    char c = *(s + i);
    if (c >= 48 && c <= 57) { // is a number character
      digitFrequencies[c - 48]++;
    }
    i++;
  }

  for (int i = 0; i < 10; i++) {
    printf("%d ", digitFrequencies[i]);
  }

  return 0;
}
