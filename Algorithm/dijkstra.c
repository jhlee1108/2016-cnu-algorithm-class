#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define MAX_VALUE 1000000

typedef struct node{
	int key;
	int distance;
} node;

typedef struct priority_queue{
	node *nodes;
	int size;
} priority_queue;

void swap(node *a, node *b)
{
	node temp = *a;
	*a = *b;
	*b = temp;
}

void init_queue(priority_queue *queue)
{
	queue -> nodes = (node *)malloc(sizeof(node) * SIZE);
	queue -> size = SIZE;
}

void min_heapify(priority_queue *queue, int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int smallest = i;

	if((left < queue -> size) && (queue -> nodes[i].distance > queue -> nodes[left].distance))
		smallest = left;

	if((right < queue -> size) && (queue -> nodes[smallest].distance > queue -> nodes[right].distance))
		smallest = right;

	if(smallest != i){
		swap(&queue -> nodes[i], &queue -> nodes[smallest]);
		min_heapify(queue, smallest);
	}
}

void build_min_heap(priority_queue *queue)
{
	int i;

	for(i = (queue -> size - 1) / 2; i >= 0; i--)
		min_heapify(queue, i);
}

node extract_min(priority_queue *queue)
{
	if(queue -> size > 0){
		node min = queue -> nodes[0];
		queue -> nodes[0] = queue -> nodes[queue -> size - 1];
		queue ->size -= 1;
		min_heapify(queue, 0);

		return min;
	}
}

void decrease_distance(priority_queue *queue, int i, int new_distance)
{
	if((i < queue -> size) && (queue -> nodes[i].distance > new_distance)){
		queue -> nodes[i].distance = new_distance;
		while(i > 0){
			if(queue -> nodes[(i - 1) / 2].distance <= new_distance)
				break;
			swap(&queue -> nodes[(i - 1) / 2], &queue -> nodes[i]);
			i = (i - 1) / 2;
		}
	}
}

void find_shortest_path(int (*graph)[SIZE], int start_node)
{
	int i;
	node temp;
	int s_size = 0;
	node *s = (node *)malloc(sizeof(node) * SIZE);
	priority_queue *queue = (priority_queue *)malloc(sizeof(priority_queue));
	init_queue(queue);

	for(i = 0; i < SIZE; i++){
		queue -> nodes[i].key = i;
		if(i == start_node)
			queue -> nodes[i].distance = 0;
		else
			queue -> nodes[i].distance = MAX_VALUE;
	}

	build_min_heap(queue);

	while(queue -> size > 0){
		temp = extract_min(queue);
		s[s_size] = temp;
		printf("--------------------------------------------\n");
		printf("S[%d] : d[%c] = %d\n", s_size, temp.key + 65, temp.distance);
		printf("--------------------------------------------\n");

		for(i = 0; i < queue -> size; i++){
			printf("Q[%d] : d[%c] = %d", i, queue -> nodes[i].key + 65, queue -> nodes[i].distance);

			if(queue -> nodes[i].distance > temp.distance + graph[temp.key][queue -> nodes[i].key]){
				printf(" -> d[%c] = %d", queue -> nodes[i].key + 65, temp.distance + graph[temp.key][queue -> nodes[i].key]);
				decrease_distance(queue, i, temp.distance + graph[temp.key][queue -> nodes[i].key]);
			}

			printf("\n");
		}

		s_size++;
		printf("\n\n");
	}

	free(s);
	free(queue -> nodes);
	free(queue);
}

int main()
{
	int graph[SIZE][SIZE] = {	{			0,			10,			3,	MAX_VALUE,	MAX_VALUE},
								{	MAX_VALUE,			0,			1,			2,	MAX_VALUE},
								{	MAX_VALUE,			4,			0,			8,			2},
								{	MAX_VALUE,	MAX_VALUE,	MAX_VALUE,			0,			7},
								{	MAX_VALUE,	MAX_VALUE,	MAX_VALUE,			9,			0}};

	printf("dijkstra algorithm\n\n");
	find_shortest_path(graph, 0);

	return 0;
}