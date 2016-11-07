#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 1000000
#define min(x,y) ((x) < (y) ? (x) : (y))

typedef struct point{
	double x;
	double y;
} point;

double euclidean_distance(point *p1, point *p2)
{
	double dist = sqrt(pow(p1 -> x - p2 -> x, 2) + pow(p1 -> y - p2 -> y, 2));

	return dist;
}

int compare_x(const void *a, const void *b)
{
	point *p1 = (point *)a;
	point *p2 = (point *)b;

	if(p1 -> x > p2 -> x)
	{
		return 1;
	}

	else if(p1 -> x < p2 -> x)
	{
		return -1;
	}

	else
	{
		return 0;
	}
}

int compare_y(const void *a, const void *b)
{
	point *p1 = (point *)a;
	point *p2 = (point *)b;

	if(p1 -> y > p2 -> y)
	{
		return 1;
	}

	else if(p1 -> y < p2 -> y)
	{
		return -1;
	}

	else
	{
		return 0;
	}
}

double brute_force(point *point_list, int n)
{
	int i,j;
	double min_dist = euclidean_distance(&point_list[0], &point_list[1]);

	for(i = 0; i < (n - 1); i++)
	{
		for(j = i + 1; j < n; j++)
		{
			if(euclidean_distance(&point_list[i], &point_list[j]) < min_dist)
			{
				min_dist = euclidean_distance(&point_list[i], &point_list[j]);
			}
		}
	}

	return min_dist;
}

double closest_pair(point *point_list, int n)
{
	int mid = n/2;
	double min_dist, dist1, dist2;
	point *remaining_points = (point *)malloc(sizeof(point) * n);
	int remaining_points_size = 0;
	int i,j;
	double l = (point_list[mid - 1].x + point_list[mid].x) / 2;

	if(n <= 3)
	{
		return brute_force(point_list, n);
	}

	dist1 = closest_pair(point_list, mid);
	dist2 = closest_pair(point_list + mid, n - mid);
	min_dist = min(dist1, dist2);

	for(i = 0; i < n; i++)
	{
		if((point_list[i].x >= (l - min_dist)) && (point_list[i].x <= (l + min_dist)))
		{
			remaining_points[remaining_points_size++] = point_list[i];
		}
	}

	qsort(remaining_points, remaining_points_size, sizeof(point), compare_y);
	
	for(i = 0; i < (remaining_points_size - 1); i++)
	{
		for(j = i + 1; j < remaining_points_size; j++)
		{
			if(remaining_points[j].y - remaining_points[i].y >= min_dist)
			{
				break;
			}

			dist1 = euclidean_distance(&remaining_points[i], &remaining_points[j]);
			min_dist = min(min_dist, dist1);
		}
	}

	free(remaining_points);
	return min_dist;
}

int main()
{
	FILE *fp = fopen("data07_closest.txt", "r");
	point *point_list = (point *)malloc(sizeof(point) * MAX_SIZE);
	int n = 0;
	double min_dist;

	while(0 < fscanf(fp,"%lf,%lf",&point_list[n].x, &point_list[n].y))
	{
		n++;
	}

	qsort(point_list, n, sizeof(point), compare_x);
	min_dist = closest_pair(point_list, n);
	printf("%.3lf\n", min_dist);

	fclose(fp);
	free(point_list);

	return 0;
}