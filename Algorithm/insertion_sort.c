/*#include <stdio.h>

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

int main()
{
	int a[6] = {8,2,4,9,3,6};
	print_array(a,6);
	insertion_sort(a,6);
	print_array(a,6);
	return 0;
}*/