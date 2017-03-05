#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 9

typedef struct node {
	char vertex;
	int weight;
} node;

typedef struct priority_queue {
	node *nodes;
	int size;
} priority_queue;

void swap(node *a, node *b)
{
	node temp = *a;
	*a = *b;
	*b = temp;
}

void min_heapify(priority_queue *queue, int i)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	int smallest = i;

	if((queue -> nodes[left].weight < queue -> nodes[smallest].weight) && (left < queue -> size)) {
		smallest = left;
	}

	if((queue -> nodes[right].weight < queue -> nodes[smallest].weight) && (right < queue -> size)) {
		smallest = right;
	}

	if(smallest != i) {
		swap(&queue -> nodes[smallest], &queue -> nodes[i]);
		min_heapify(queue, smallest);
	}
}

void build_min_heap(priority_queue *queue)
{
	int i;

	for(i = (queue -> size - 1) / 2; i >= 0; i--) {
		min_heapify(queue, i);
	}
}

node extract_min(priority_queue *queue)
{
	if(queue -> size > 0) {
		node min = queue -> nodes[0];
		queue -> nodes[0] = queue -> nodes[queue -> size - 1];
		queue ->size -= 1;
		min_heapify(queue, 0);

		return min;
	}
}

void init_queue(priority_queue *queue)
{
	queue -> nodes = (node *)malloc(sizeof(node) * SIZE);
	queue -> size = SIZE;
}

void find_mst(int (*graph)[SIZE], int start_node)
{
	int sum_weight = 0;
	int i;
	node u;
	priority_queue *queue = (priority_queue *)malloc(sizeof(priority_queue));
	node *parent_node = (node *)malloc(sizeof(node) * SIZE);
	parent_node[start_node].vertex = ' ';

	init_queue(queue);

	for(i = 0; i < SIZE; i++) {
		queue -> nodes[i].vertex = i + 97;
		if(i == start_node) {
			queue -> nodes[i].weight = 0;
		}

		else {
			queue -> nodes[i].weight = INT_MAX;
		}
	}

	build_min_heap(queue);
	
	while(queue -> size > 0) {
		u = extract_min(queue);
		sum_weight += u.weight;
		printf("w<%c,%c> = %d\n", parent_node[u.vertex - 97].vertex, u.vertex, u.weight);

		for(i = 0; i < queue -> size; i++) {
			if(queue -> nodes[i].weight > graph[u.vertex - 97][queue -> nodes[i].vertex - 97]) {
				queue -> nodes[i].weight = graph[u.vertex - 97][queue -> nodes[i].vertex - 97];
				parent_node[queue -> nodes[i].vertex - 97] = u;
			}
		}

		build_min_heap(queue);
	}

	printf("\nw<MST> = %d\n", sum_weight);

	free(queue -> nodes);
	free(queue);
	free(parent_node);
}

int main()
{
	int graph[SIZE][SIZE] = {	{	   0,		4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,		  8, INT_MAX},
								{	   4,		0,		 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX,		 11, INT_MAX},
								{INT_MAX,		8,		 0,		  7, INT_MAX,		4, INT_MAX, INT_MAX,	   2},
								{INT_MAX, INT_MAX,		 7,		  0,	   9,	   14, INT_MAX, INT_MAX, INT_MAX},
								{INT_MAX, INT_MAX, INT_MAX,		  9,	   0,	   10, INT_MAX, INT_MAX, INT_MAX},
								{INT_MAX, INT_MAX,		 4,		 14,	  10,		0,		 2, INT_MAX, INT_MAX},
								{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,		2,		 0,		  1,	   6},
								{	   8,	   11, INT_MAX, INT_MAX, INT_MAX, INT_MAX,		 1,		  0,	   7},
								{INT_MAX, INT_MAX,		 2, INT_MAX, INT_MAX, INT_MAX,		 6,		  7,	   0}};

	find_mst(graph, 0);
	return 0;
}
