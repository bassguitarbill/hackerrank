#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


int max(int a, int b, int t) {
  if (b >= t) return a;
  return a < b ? b : a;
}

void calculate_the_maximum(int n, int k) {
  int maxAnd = 0, maxOr = 0, maxXor = 0;
  for (int a = 1; a <= n; a++) {
    for (int b = a + 1; b <= n; b++) {
      maxAnd = max(maxAnd, a & b, k);
      maxOr  = max(maxOr , a | b, k);
      maxXor = max(maxXor, a ^ b, k);
    }
  }
  printf("%d\n%d\n%d\n", maxAnd, maxOr, maxXor);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
