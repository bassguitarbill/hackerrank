#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int distance(int x, int y, int center) {
  int distX = abs(x - center);
  int distY = abs(y - center);
  return distY < distX ? distX : distY;
}

int main() 
{
    int n;
    scanf("%d", &n);
    int center = n - 1;
    for (int x = 0; x < (2 * n - 1); x++) {
      for (int y = 0; y < (2 * n - 1); y++) {
        printf("%d ", distance(x, y, center) + 1);
      }
      printf("\n");
    }

  	// Complete the code to print the pattern.
    return 0;
}
