#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000000

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int mid(int *a, int i, int j, int k)
{
	if(((a[i] >= a[j]) && (a[i] < a[k])) || ((a[i] < a[j]) && (a[i] >= a[k])))
	{
		return i;
	}

	else if(((a[j] >= a[i]) && (a[j] < a[k])) || ((a[j] < a[i]) && (a[j] >= a[k])))
	{
		return j;
	}

	else
	{
		return k;
	}
}

int random(int *a, int p, int r)
{
	int i, j, k;
	
	srand(time(NULL));
	i = (rand() % (r - p - 1)) + p;
	j = (rand() % (r - p - 1)) + p;
	k = (rand() % (r - p - 1)) + p;
	//printf("random value = %d, %d, %d\n", a[i], a[j], a[k]);
	
	return mid(a, i, j, k);
}

int partition(int *a, int p, int r)
{
	int i = p - 1;
	int j;
	int x = a[r - 1];

	for(j = p; j < r - 1; j++)
	{
		if(a[j] <= x)
		{
			i++;
			swap(&a[i], &a[j]);
		}
	}

	i++;
	swap(&a[i], &a[j]);

	return i;
}

int randomized_partition(int *a, int p, int r)
{
	int i;

	if((r - p - 1) > 50)
	{
		i = random(a, p, r);
		//printf("mid = %d\n", a[i]);
		swap(&a[i], &a[r - 1]);
	}

	return partition(a, p, r);
}

void randomized_quick_sort(int *a, int p, int r)
{
	int q;

	if(p < r)
	{
		q = randomized_partition(a, p, r);
		randomized_quick_sort(a, p, q);
		randomized_quick_sort(a, q + 1, r);
	}
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("hw03_01_201200737_quickRandom.txt","w");
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
	FILE *fp = fopen("hw02_1000man.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;
	time_t start_time = 0, end_time = 0;

	printf("Reading input file...\n");
	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	printf("Start quick sort\n");
	start_time = clock();
	randomized_quick_sort(a, 0, n);
	end_time = clock();
	printf("Finish\n");
	printf("%d ms\n", end_time - start_time);

	printf("Writing array...\n");
	write_array(a, n);
	fclose(fp);


	return 0;
}