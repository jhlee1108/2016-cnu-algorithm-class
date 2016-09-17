#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void merge(int *a, int start, int mid, int end)
{
	int *temp = (int*)malloc(sizeof(int) * MAX_SIZE);
	int i;
	int s = start;
	int m = mid;
	int t = start;

	for(i = start; i < end; i++)
	{
		temp[i] = a[i];
	}

	while((s < mid) && (m < end))
	{
		if(temp[s] < temp[m])
		{
			a[t++] = temp[s++];
		}
		else
		{
			a[t++] = temp[m++];
		}
	}

	if(s == m)
	{
		for(i = m; i < end; i++)
		{
			a[t++] = temp[i];
		}
	}

	if(m == end)
	{
		for(i = s; i < mid; i++)
		{
			a[t++] = temp[i];
		}
	}

	free(temp);
}

void merge_sort(int *a, int start, int end)
{
	int mid = (start + end) / 2;

	if((end - start) <= 1)
	{
		return;
	}

	merge_sort(a,start,mid);
	merge_sort(a,mid,end);
	merge(a,start,mid,end);
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
	FILE *fp = fopen("hw02_10man.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;

	while(0 < fscanf(fp,"%d,",&a[n]))
	{
		n++;
	}

	merge_sort(a,0,n);
	write_array(a,n);
	fclose(fp);

	return 0;
}