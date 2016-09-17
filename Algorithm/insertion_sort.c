/*#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

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
	FILE *fp = fopen("data02_insertion.txt","w");
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

	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	insertion_sort(a,n);
	write_array(a,n);
	fclose(fp);
	free(a);

	return 0;
}*/