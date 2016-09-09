/*#include <stdio.h>

int binary_search(int *a, int n, int key)
{
	int start = 0;
	int end = n;

	while(end > start)
	{
		int mid = (start + end) / 2;

		if(a[mid] == key)
		{
			return mid;
		}

		if(a[mid] < key)
		{
			if(a[mid + 1] > key)
			{
				return mid + 1;
			}

			start = mid + 1;
		}

		if(a[mid] > key)
		{
			if(a[mid - 1] < key)
			{
				return mid;
			}

			end = mid - 1;
		}
	}

	return start;
}

void move_array(int *a, int i, int j)
{
	while(i < j)
	{
		a[j] = a[j - 1];
		j = j - 1;
	}
}

void insertion_sort(int *a, int n)
{
	int insert,j,key;

	for(j = 1; j < n; j++)
	{
		key = a[j];
		insert = binary_search(a,j,key);
		move_array(a,insert,j);
		a[insert] = key;
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
}*/
