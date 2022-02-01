#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int compare (char* a, char* b) {
  int i = 0;
  while (a[i] > 0 && b[i] > 0) {
    if (a[i] > b[i]) return -1;
    if (b[i] > a[i]) return 1;
    i++;
  }
  if (a[i] == 0 && b[i] == 0) return 0;
  if (a[i] == 0) return 1;
  return -1;
}

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/

  /* The following algorithm generates the next permutation lexicographically after a given permutation. It changes the given permutation in-place.
  * Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
  * Find the largest index l greater than k such that a[k] < a[l].
  * Swap the value of a[k] with that of a[l].
  * Reverse the sequence from a[k + 1] up to and including the final element a[n].
  */

  bool lastPerm = true;
  int i = n - 2;
  for (; i >= 0; i--) {
    if (compare(s[i], s[i + 1]) == 1) {
      lastPerm = false;
      break;
    }
  }
  if (lastPerm) return 0;

  int j = n - 1;
  for (; j >= 0; j--) {
    if (compare(s[i], s[j]) == 1) {
      break;
    }
  }

  char* temp = s[i];
  s[i] = s[j];
  s[j] = temp;


  char** lastChunk = calloc(n - i - 1, sizeof(char*));
  for (int k = 0; k < n - i - 1; k++) {
    lastChunk[k] = s[(n - k) - 1];
  }

  for (int k = 0; k < n - i - 1; k++) {
    s[i + k + 1] = lastChunk[k];
  }

  free(lastChunk);
  return 1;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
