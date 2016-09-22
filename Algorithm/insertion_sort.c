/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000000

void insertion_sort(int *a, int n)
{
	int i,j,key;

	for(j = 1; j < n; j++)
	{
		key = a[j];
		i = j - 1;
		while(i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			i = i - 1;
		}
		a[i + 1] = key;
	}
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("hw01_01_201200737_insertion.txt","w");
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
}*/