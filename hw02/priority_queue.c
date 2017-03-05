#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_SIZE 100
#define MAX_VALUE_LENGTH 20

typedef struct node{
	int key;
	char value[MAX_VALUE_LENGTH];
} node;

typedef struct priority_queue{
	int size;
	node *nodes;
} priority_queue;

void swap(node *a, node *b);
node *make_node();

void read_file(priority_queue *queue, FILE *fp);
void print_queue(priority_queue *queue);

void max_heapify(priority_queue *queue, int i);
void reverse_max_heapify(priority_queue *queue, int i);
void build_max_heap(priority_queue *queue);

void init_queue(priority_queue *queue);
void insert(priority_queue *queue, node *node);
node *get_max(priority_queue *queue);
void extract_max(priority_queue *queue);
void increase_key(priority_queue *queue, int i, int new_key);
void delete_node(priority_queue *queue, int i);



void swap(node *a, node *b)
{
	node temp = *a;
	*a = *b;
	*b = temp;
}

void max_heapify(priority_queue *queue, int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;

	if((left < queue -> size) && (queue -> nodes[left].key > queue -> nodes[i].key)) {
		largest = left;
	}

	if((right < queue -> size) && (queue -> nodes[right].key > queue -> nodes[largest].key)) {
		largest = right;
	}

	if(largest != i) {
		swap(&queue -> nodes[i], &queue -> nodes[largest]);
		max_heapify(queue, largest);
	}
}

void build_max_heap(priority_queue *queue)
{
	int i;

	for(i = (queue -> size - 1) / 2; i >= 0; i--) {
		max_heapify(queue,i);
	}
}

void read_file(priority_queue *queue, FILE *fp)
{
	char ch = 'a';
	int n = 0;

	while(ch != EOF) {
		fscanf(fp,"%d, ",&queue -> nodes[queue -> size].key);
		while((ch = fgetc(fp)) != 10 && ch != EOF) {
			queue -> nodes[queue -> size].value[n++] = ch;
		}

		queue -> nodes[queue -> size].value[n] = '\0';
		n = 0;
		queue -> size += 1;
	}
}

void print_queue(priority_queue *queue)
{
	int i;

	for(i = 0; i < queue -> size; i++) {
		printf("%3d, %20s, index : %d\n", queue -> nodes[i].key, queue -> nodes[i].value, i);
	}
}

void reverse_max_heapify(priority_queue *queue, int i)
{
	int parent_index = (i - 1) / 2;
	if((queue -> nodes[i].key > queue -> nodes[parent_index].key) && (i != 0)) {
		swap(&queue -> nodes[i], &queue -> nodes[parent_index]);
		reverse_max_heapify(queue, parent_index);
	}
}

void init_queue(priority_queue *queue)
{
	queue -> size = 0;
	queue -> nodes = (node *)malloc(sizeof(node) * MAX_SIZE);
}

void insert(priority_queue *queue, node *node)
{
	system("cls");
	printf("**** insert %s ****\n\n", node -> value);

	queue -> nodes[queue -> size] = *node;
	queue -> size += 1;
	reverse_max_heapify(queue, queue -> size - 1);
}

node *get_max(priority_queue *queue)
{
	node *max_node = (node *)malloc(sizeof(node));
	*max_node = queue -> nodes[0];

	system("cls");

	if(queue -> size == 0) {
		printf("**** queue is empty ****\n\n");
		return NULL;
	}

	printf("**** MAX : %d, %s ****\n\n", max_node -> key, max_node -> value);

	return max_node;
}

void extract_max(priority_queue *queue)
{
	system("cls");

	if(queue -> size == 0) {
		printf("**** queue is empty ****\n\n");
		return;
	}

	printf("**** extract_max ****\n\n");
	queue -> nodes[0] = queue -> nodes[queue -> size - 1];
	queue -> size -= 1;
	max_heapify(queue, 0);
}

void increase_key(priority_queue *queue, int i, int new_key)
{
	if((i >= queue -> size) || (i < 0)) {
		system("cls");
		printf("**** select 0~%d ****\n\n", (queue -> size) - 1);

		return;
	}

	system("cls");
	printf("**** increase_key ****\n\n");

	if(queue -> nodes[i].key < new_key) {
		queue -> nodes[i].key = new_key;
		reverse_max_heapify(queue, i);
	}

	else {
		queue -> nodes[i].key = new_key;
		max_heapify(queue, i);
	}

}

void delete_node(priority_queue *queue, int i)
{
	if((i >= queue -> size) || (i < 0)) {
		system("cls");
		printf("**** select 0~%d ****\n\n", (queue -> size) - 1);

		return;
	}

	system("cls");
	printf("**** delete_node ****\n\n");

	queue -> nodes[i] = queue -> nodes[queue -> size - 1];
	queue -> size -= 1;
	max_heapify(queue, i);
}

node *make_node()
{
	node *temp_node = (node *)malloc(sizeof(node));

	printf("value : ");
	scanf("%19s", temp_node -> value);

	printf("key : ");
	scanf("%d", &temp_node -> key);

	return temp_node;
}

int main()
{
	FILE *fp = fopen("data03.txt","r");
	priority_queue *queue = (priority_queue*)malloc(sizeof(priority_queue));
	char state = 'a';
	int temp_key;
	int node_index;
	node *temp_node;

	init_queue(queue);

	read_file(queue, fp);
	fclose(fp);

	build_max_heap(queue);

	printf("**** select your job ****\n\n");
	while(state != '6') {
		print_queue(queue);
		printf("-----------------------------------------------\n");
		printf("1. insert	2. max		3. extract_max\n");
		printf("4. increase_key	5. delete	6. exit\n");
		printf("-----------------------------------------------\n");
		state = getch();

		switch(state) {
		case '1':
			temp_node = make_node();
			insert(queue, temp_node);
			free(temp_node);
			break;

		case '2':
			temp_node = get_max(queue);
			free(temp_node);
			break;

		case '3':
			extract_max(queue);
			break;

		case '4':
			printf("select node_index : ");
			scanf("%d", &node_index);
			printf("new_key : ");
			scanf("%d", &temp_key);

			increase_key(queue, node_index, temp_key);
			break;

		case '5':
			printf("select node_index : ");
			scanf("%d", &node_index);

			delete_node(queue, node_index);
			break;

		case '6':
			break;

		default:
			system("cls");
			printf("**** select 1~6 ****\n\n");
			break;
		}
	}

	free(queue -> nodes);
	free(queue);

	return 0;
}
