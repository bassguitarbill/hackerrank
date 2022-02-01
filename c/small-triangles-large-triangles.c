#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

double area(struct triangle t) {
  double p = (t.a + t.b + t.c) / 2.0;
  double areaSquared = p * (p - t.a) * (p - t.b) * (p - t.c);
  //double area = sqrt(areaSquared);
  return areaSquared; // Until triangles start having a negative area, this is fine
}

typedef struct triangle triangle;
void sort_by_area(triangle* tr, int n) {
  if (n == 0) return;
  if (n == 1) return;

  triangle index = tr[0];
  triangle* upper = calloc(n - 1, sizeof(struct triangle));
  int ul = 0;
  triangle* lower = calloc(n - 1, sizeof(struct triangle));
  int ll = 0;

  for (int i = 1; i < n; i ++) {
    if (compare_triangles(index, tr[i]) > 0) {
      upper[ul] = tr[i];
      ul++;
    } else {
      lower[ll] = tr[i];
      ll++;
    }
  }

  sort_by_area(upper, ul);
  sort_by_area(lower, ll);

  tr[ll] = index;

  for (int i = 0; i < ul + ll + 1; i ++) {
    if (i < ll) {
      tr[i] = lower[i];
    } else if (i > ll) {
      tr[i] = upper[i - ll - 1];
    }
  }

  free(upper);
  free(lower);
}

int compare_triangles(triangle a, triangle b) {
  double aa = area(a);
  double ab = area(b);
  if (aa > ab) return -1;
  if (ab > aa) return 1;
  return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
