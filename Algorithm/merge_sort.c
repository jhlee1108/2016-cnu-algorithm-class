#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000000

void merge(int *a, int n)
{
	int *temp = (int*)malloc(sizeof(int) * n);
	int mid = n / 2;
	int i = 0;
	int j = mid;
	int t = 0;
	int k;

	for(k = 0; k < n; k++)
	{
		temp[k] = a[k];
	}

	while((i < mid) && (j < n))
	{
		if(temp[i] < temp[j])
		{
			a[t++] = temp[i++];
		}
		else
		{
			a[t++] = temp[j++];
		}
	}

	if(i == mid)
	{
		for(k = j; k < n; k++)
		{
			a[t++] = temp[k];
		}
	}

	else
	{
		for(k = i; k < mid; k++)
		{
			a[t++] = temp[k];
		}
	}

	free(temp);
}

void merge_sort(int *a, int n)
{
	int mid = n / 2;

	if(n <= 1)
	{
		return;
	}

	merge_sort(a,mid);
	merge_sort(a + mid,n - mid);
	merge(a,n);
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("data02_merge.txt","w");
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
	FILE *fp = fopen("hw02_100man.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;
	time_t start_time = 0, end_time = 0;

	printf("Reading input file...\n");
	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	printf("Start merge sort\n");
	start_time = clock();
	merge_sort(a,n);
	end_time = clock();
	printf("Finish\n");
	printf("%d ms\n", end_time - start_time);

	printf("Writing array...\n");
	write_array(a,n);
	fclose(fp);


	return 0;
}