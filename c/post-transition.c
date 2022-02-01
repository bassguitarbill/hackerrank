#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

void print_all_packages(town t) {
  printf("%s:\n", t.name);
  for (int i = 0; i < t.offices_count; i++) {
    printf("\t%d:\n", i);
    post_office o = t.offices[i];
    for (int j = 0; j < o.packages_count; j++) {
      printf("\t\t%s\n", o.packages[j].id);
    }
  }
}

bool can_accept_package(post_office o, package p) {
  int weight = p.weight;
  if (weight >= o.min_weight && weight <= o.max_weight) return true;
  return false;
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
  post_office source_office = source->offices[source_office_index];
  post_office target_office = target->offices[target_office_index];

  package* denied = calloc(source_office.packages_count, sizeof(package));
  int dl = 0;
  package* accepted = calloc(source_office.packages_count, sizeof(package));
  int al = 0;

  for (int i = 0; i < source_office.packages_count; i++) {
    if (can_accept_package(target_office, source_office.packages[i])) {
      accepted[al] = source_office.packages[i];
      al++;
    } else {
      denied[dl] = source_office.packages[i];
      dl++;
    }
  }

  free(source_office.packages);
  source->offices[source_office_index].packages = denied;
  source->offices[source_office_index].packages_count = dl;

  if (al == 0) return;

  target->offices[target_office_index].packages = realloc(
      target->offices[target_office_index].packages,
      sizeof(package) * (target->offices[target_office_index].packages_count + al)
      );

  for (int i = 0; i < al; i++) {
    target->offices[target_office_index].packages[target_office.packages_count + i] = accepted[i];
  }

  target->offices[target_office_index].packages_count += al;
  free(accepted);
}

int num_packages_in_town(town t) {
  int sum = 0;
  for (int i = 0; i < t.offices_count; i++) {
    post_office o = t.offices[i];
    sum += o.packages_count;
  }
  return sum;
}

town town_with_most_packages(town* towns, int towns_count) {
  int max_packages = -1;
  town town_with_the_most;

  for (int i = 0; i < towns_count; i++) {
    int num_packages = num_packages_in_town(towns[i]);
    if (num_packages > max_packages) {
      max_packages = num_packages;
      town_with_the_most = towns[i];
    }
  }
  return town_with_the_most;
}

town* find_town(town* towns, int towns_count, char* name) {
  for (int i = 0; i < towns_count; i++) {
    if (strcmp(towns[i].name, name) == 0) {
      return &(towns[i]);
    }
  }
  return NULL;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
