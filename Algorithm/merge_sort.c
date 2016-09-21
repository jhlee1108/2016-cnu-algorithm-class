#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000000

void merge(int *a, int n)
{
	int *temp = (int*)malloc(sizeof(int) * n);
	int mid = n / 2;
	int array_index = 0;
	int i = 0;
	int j = mid;
	int t;

	for(t = 0; t < n; t++)
	{
		temp[t] = a[t];
	}

	while((i < mid) && (j < n))
	{
		if(temp[i] < temp[j])
		{
			a[array_index++] = temp[i++];
		}
		else
		{
			a[array_index++] = temp[j++];
		}
	}

	if(i == mid)
	{
		for(t = j; t < n; t++)
		{
			a[array_index++] = temp[t];
		}
	}

	else
	{
		for(t = i; t < mid; t++)
		{
			a[array_index++] = temp[t];
		}
	}

	free(temp);
}

void merge_sort(int *a, int n, int *count)
{
	int mid = n / 2;

	if(n <= 1)
	{
		return;
	}

	merge_sort(a,mid, count);
	merge_sort(a + mid,n - mid, count);
	merge(a,n);
	*count += 1;
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("hw01_01_201200737_merge.txt","w");
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
	int count = 0;
	time_t start_time = 0, end_time = 0;

	printf("Reading input file...\n");
	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	printf("Start merge sort\n");
	start_time = clock();
	merge_sort(a, n, &count);
	end_time = clock();
	printf("Finish\n");
	printf("%d ms\n", end_time - start_time);
	printf("Call merge() %d times\n", count);

	printf("Writing array...\n");
	write_array(a,n);
	fclose(fp);


	return 0;
}