#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

void merge_and_count(int *a, int n, int *count)
{
	int *temp = (int*)malloc(sizeof(int) * n);
	int mid = n / 2;
	int array_index = 0;
	int i = 0;
	int j = mid;
	int t;

	for(t = 0; t < n; t++) {
		temp[t] = a[t];
	}

	while((i < mid) && (j < n)) {
		if(temp[i] < temp[j]) {
			a[array_index++] = temp[i++];
		}

		else {
			a[array_index++] = temp[j++];
			*count += (mid - i);
		}
	}

	if(i == mid) {
		for(t = j; t < n; t++) {
			a[array_index++] = temp[t];
		}
	}

	else {
		for(t = i; t < mid; t++) {
			a[array_index++] = temp[t];
		}
	}

	free(temp);
}

void sort_and_count(int *a, int n, int *count)
{
	int mid = n / 2;

	if(n <= 1) {
		return;
	}

	sort_and_count(a, mid, count);
	sort_and_count(a + mid, n - mid, count);
	merge_and_count(a, n, count);
}

void print_array(int *a, int n)
{
	int i;

	for(i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

int main()
{
	FILE *fp = fopen("data07_inversion.txt","r");
	int *a = (int*)malloc(sizeof(int) * MAX_SIZE);
	int n = 0;
	int count = 0;

	while(0 < fscanf(fp,"%d,",&a[n])) {
		n++;
	}

	sort_and_count(a, n, &count);
	printf("count = %d\n", count);

	fclose(fp);
	free(a);

	return 0;
}
