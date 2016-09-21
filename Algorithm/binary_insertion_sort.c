#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000000

int binary_search(int *a, int n, int key)
{
	int i,j,m;

	if(a[0] > key)
	{
		return 0;
	}

	else if((a[0] <= key) && (key < a[n - 1]))
	{
		i = 0;
		j = n;

		while((i + 1) != j)
		{
			m = (i + j) / 2;

			if(a[m] <= key)
			{
				i = m;
			}

			else
			{
				j = m;
			}
		}

		return j;
	}

	else
	{
		return n;
	}
}

void insertion_sort(int *a, int n)
{
	int insert,j,key;

	for(j = 1; j < n; j++)
	{
		key = a[j];
		insert = binary_search(a, j, key);
		memmove(a + insert + 1, a + insert, sizeof(int) * (j - insert));
		a[insert] = key;
	}
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("hw01_01_201200737_binary_insertion.txt","w");
	fprintf(fp,"%d",a[0]);

	while(i < n)
	{
		fprintf(fp,",%d",a[i]);
		i = i + 1;
	}

	fclose(fp);
}

int main()
{
	FILE *fp = fopen("data02.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;
	time_t start_time = 0, end_time = 0;

	printf("Reading input file...\n");
	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	printf("Start insertion sort\n");
	start_time = clock();
	insertion_sort(a,n);
	end_time = clock();
	printf("Finish\n");
	printf("%d ms\n", end_time - start_time);

	printf("Writing array...\n");
	write_array(a,n);
	fclose(fp);


	return 0;
}