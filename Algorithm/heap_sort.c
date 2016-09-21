#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000000

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void max_heapify(int *a, int n, int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;

	if((left < n) && (a[left] > a[i]))
	{
		largest = left;
	}

	if((right < n) && (a[right] > a[largest]))
	{
		largest = right;
	}

	if(largest != i)
	{
		swap(a + i, a + largest);
		max_heapify(a,n,largest);
	}
}

void build_max_heap(int *a, int n)
{
	int i;

	for(i = (n - 1) / 2; i >= 0; i--)
	{
		max_heapify(a,n,i);
	}
}

void heap_sort(int *a, int n)
{
	int heap_size = n;
	
	build_max_heap(a,n);

	while(heap_size > 0)
	{
		swap(a, a + heap_size - 1);
		heap_size--;
		max_heapify(a,heap_size,0);
	}
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("hw01_01_201200737_heap.txt","w");
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
	FILE *fp = fopen("hw02_10man.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;
	time_t start_time = 0, end_time = 0;

	printf("Reading input file...\n");
	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	printf("Start heap sort\n");
	start_time = clock();
	heap_sort(a,n);
	end_time = clock();
	printf("Finish\n");
	printf("%d ms\n", end_time - start_time);

	printf("Writing array...\n");
	write_array(a,n);
	fclose(fp);


	return 0;
}