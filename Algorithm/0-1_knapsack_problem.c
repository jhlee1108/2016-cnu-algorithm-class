#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (a > b ? a : b)
#define MAX_ITEM_SIZE 101
#define MAX_BAG_SIZE 51

typedef struct item {
	int value;
	int weight;
} item;

void create_table(int table[][MAX_BAG_SIZE], int item_size, int bag_size, item *items)
{
	int i,j;

	for(i = 0; i <= item_size; i++) {
		for(j = 0; j <= bag_size; j++) {
			if(i == 0)
				table[i][j] = 0;
			else if(items[i].weight > j)
				table[i][j] = table[i - 1][j];
			else
				table[i][j] = MAX(table[i - 1][j], items[i].value + table[i - 1][j - items[i].weight]);
			printf("%5d", table[i][j]);
		}
		printf("\n");
	}
}

void find_item(int table[][MAX_BAG_SIZE],int item_size,int bag_size,item *items) 
{
	int max_value;
	int item_num[MAX_ITEM_SIZE];
	int i = item_size;
	int j = bag_size;
	int n = 0;

	printf("max : %d\n", table[item_size][bag_size]);

	while(i > 0 && j > 0) {
		if(items[i].weight > j) 
			i--;
		else if(table[i - 1][j] > items[i].value + table[i - 1][j - items[i].weight])
			i--;
		else {
			item_num[n++] = i;
			j = j - items[i].weight;
			i--;
		}
	}

	printf("item :");
	for(i = n - 1; i >= 0; i--)
		printf(" %d", item_num[i]);
	printf("\n");
}

int main()
{
	int bag_size, i, v, w;
	int item_size = 0;
	int table[MAX_ITEM_SIZE][MAX_BAG_SIZE];
	FILE *fp = fopen("data11.txt", "r");
	item *items = (item *)malloc(sizeof(item) * MAX_ITEM_SIZE);

	printf("bag_size(0~50) : ");
	scanf("%d", &bag_size);
	if(bag_size > 50)
		bag_size = 50;
	if(bag_size < 0)
		bag_size = 0;

	while(fscanf(fp, "%d,%d,%d", &i, &v, &w) != EOF) {
		items[i].value = v;
		items[i].weight = w;
		item_size++;
	}
	fclose(fp);

	create_table(table, item_size, bag_size, items);
	find_item(table, item_size, bag_size, items);

	free(items);
	return 0;
}