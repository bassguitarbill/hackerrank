#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lexicographic_sort(const char* a, const char* b) {
  int i = 0;
  while (a[i] > 0 && b[i] > 0) {
    if (a[i] < b[i]) return 1;
    if (b[i] < a[i]) return -1;
    i++;
  }
  if (a[i] == 0) return 1;
  if (b[i] == 0) return -1;
  return 0;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
  int i = 0;
  while (a[i] > 0 && b[i] > 0) {
    if (a[i] < b[i]) return -1;
    if (b[i] < a[i]) return 1;
    i++;
  }
  if (a[i] == 0) return -1;
  if (b[i] == 0) return 1;
  return 0;

}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
  int a_distinct_characters[26];
  int a_char_count = 0;
  int b_distinct_characters[26];
  int b_char_count = 0;
  for (int i = 0; i < 26; i++) {
    a_distinct_characters[i] = 0;
    b_distinct_characters[i] = 0;
  }

  // 97 is lowercase a
  
  int i = 0;
  while(a[i] > 0) {
    int c = a[i] - 97;
    if (!a_distinct_characters[c]) {
      a_distinct_characters[c] = 1;
      a_char_count += 1;
    }
    i++;
  }

  i = 0;
  while(b[i] > 0) {
    int c = b[i] - 97;
    if (!b_distinct_characters[c]) {
      b_distinct_characters[c] = 1;
      b_char_count += 1;
    }
    i++;
  }
  if (b_char_count > a_char_count) return 1;
  if (a_char_count > b_char_count) return -1;
  return lexicographic_sort(a, b);
}

int sort_by_length(const char* a, const char* b) {
  int index = 0;
  while (a[index] > 0 && b[index] > 0) {
    index++;
  }
  if (a[index] == 0 && b[index] == 0) return lexicographic_sort(a, b);
  if (a[index] == 0) return 1; // a is shorter so it comes first
  return -1; // b must be shorter
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
  if (len < 2) return;
  char* index = arr[0];
  char** upper = calloc(len, sizeof(char*));
  int ul = 0;
  char** lower = calloc(len, sizeof(char*));
  int ll = 0;

  for (int i = 1; i < len; i++) {
    if (cmp_func(index, arr[i]) > 0) {
      upper[ul] = arr[i];
      ul++;
    } else {
      lower[ll] = arr[i];
      ll++;
    }
  }

  /*printf("index = %s\n", index);
  printf("ul: %d\n", ul);
  printf("ll: %d\n", ll);
  printf("Before partition sorts\n");
  printf("upper: ");
  for (int i = 0; upper[i] > 0; i++) {
    printf("%s ", upper[i]);
  }
  printf("\nlower: ");
  for (int i = 0; lower[i] > 0; i++) {
    printf("%s ", lower[i]);
  }*/

  string_sort(upper, ul, cmp_func);
  string_sort(lower, ll, cmp_func);

  /*printf("After partition sorts\n");
  printf("upper: ");
  for (int i = 0; upper[i] > 0; i++) {
    printf("%s ", upper[i]);
  }
  printf("\nlower: ");
  for (int i = 0; lower[i] > 0; i++) {
    printf("%s ", lower[i]);
  }
  printf("\n");*/
  /*int i = 0;
  for (; i < ll; i++) {
    arr[i] = lower[i];
  }
  arr[i] = index;
  i++;
  for (; i < ul; i++) {
    arr[i] = upper[i - ll - 1];
  }*/
  arr[ll] = index; // get it out of the way before we clobber it
  for (int i = 0; i < ll; i++) {
    arr[i] = lower[i];
  }
  for (int i = ll + 1; i < ul + ll + 1; i++) {
    arr[i] = upper[i - ll - 1];
  }

  /*printf("After full sort\n");
  for (int i = 0; i < len; i++) {
    printf("%s ", arr[i]);
  }
  printf("\n");*/

  free(upper);
  free(lower);
}

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
