#include <stdio.h>

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

void print_array(int *a, int n)
{
	int i = 0;

	while(i < n)
	{
		printf("%d ",a[i]);
		i = i + 1;
	}

	printf("\n");
}

void write_array(int *a, int n)
{
	int i = 1;
	FILE *fp = fopen("data02_insertion.txt","w");
	fprintf(fp,"%d",a[0]);

	while(i < n)
	{
		fprintf(fp,",%d ",a[i]);
		i = i + 1;
	}

	fclose(fp);
}

int main()
{
	FILE *fp = fopen("data02.txt","r");
	int a[1000];
	int n = 0;

	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	print_array(a,n);
	insertion_sort(a,n);
	print_array(a,n);
	write_array(a,n);
	fclose(fp);

	return 0;
}