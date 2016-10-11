#include <stdio.h>
#include <math.h>

int log2_floor(unsigned long long input_number)
{
	int e = 0;
	unsigned long long k = 1;

	while(k <= input_number)
	{
		e += 1;
		k *= 2;
	}

	return e - 1;
}

int binary_search(unsigned long long input_number, int e)
{
	int i = e / 2;
	int j = e;
	int m;

	while((i + 1) != j)
	{
		m = (i + j) / 2;

		if(pow(2.0, m) <= input_number)
		{
			i = m;
		}

		else
		{
			j = m;
		}
	}

	return i;
}

int log2_floor_fast(unsigned long long input_number)
{
	int e = 1;
	unsigned long long k = 1;

	while(k <= input_number)
	{
		e *= 2;
		k = pow(2.0, e);
	}

	return binary_search(input_number, e);
}

int main()
{
	unsigned long long input_number = 1;
	int result;
	int fast_result;

	printf("Number : ");
	scanf("%lld", &input_number);

	result = log2_floor(input_number);
	printf("result = %d\n", result);

	fast_result = log2_floor_fast(input_number);
	printf("fast_result = %d\n", result);

	return 0;
}