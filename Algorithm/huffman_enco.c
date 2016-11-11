#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_LETTERS 27
#define MAX_DATA_SIZE 1000000

typedef struct node{
	int frequency;
	char letter;
	struct node *left;
	struct node *right;
} node;

typedef struct priority_queue{
	node **nodes;
	int size;
} priority_queue;

typedef struct table_index{
	char letter;
	char *enco;
} table_index;

typedef struct table{
	table_index *index;
	int size;
} table;

void swap(node *a, node *b)
{
	node temp = *a;
	*a = *b;
	*b = temp;
}

int compare_letter(const void *a, const void *b)
{
	table_index *t1 = (table_index *)a;
	table_index *t2 = (table_index *)b;

	if(t1 -> letter > t2 -> letter)
	{
		return 1;
	}

	else if(t1 -> letter < t2 -> letter)
	{
		return -1;
	}

	else
	{
		return 0;
	}
}

void min_heapify(priority_queue *queue, int i)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	int smallest = i;

	if((left < queue -> size) && (queue -> nodes[smallest] -> frequency > queue -> nodes[left] -> frequency))
		smallest = left;

	if((right < queue -> size) && (queue -> nodes[smallest] -> frequency > queue -> nodes[right] -> frequency))
		smallest = right;

	if(smallest != i){
		swap(queue -> nodes[i], queue -> nodes[smallest]);
		min_heapify(queue, smallest);
	}
}

void build_min_heap(priority_queue *queue)
{
	int i;

	for(i = (queue -> size - 1) / 2; i >= 0; i--)
		min_heapify(queue, i);
}

node *extract_min(priority_queue *queue)
{
	if(queue -> size > 0){
		node *min = queue -> nodes[0];
		queue -> nodes[0] = queue -> nodes[queue -> size - 1];
		queue -> nodes[queue -> size - 1] = NULL;
		queue -> size -= 1;
		min_heapify(queue, 0);

		return min;
	}
}

void insert(priority_queue *queue, node *n)
{
	int parent_index = (queue -> size - 1) / 2;
	int current_index = queue -> size;
	queue -> nodes[current_index] = n;

	while(current_index != 0){
		if(queue -> nodes[parent_index] -> frequency < queue -> nodes[current_index] -> frequency)
			break;
		swap(queue -> nodes[parent_index], queue -> nodes[current_index]);
		current_index = parent_index;
		parent_index = (current_index - 1) / 2;
	}

	queue -> size += 1;
}

void init_queue(priority_queue *queue)
{
	queue -> nodes = (node **)malloc(sizeof(node *) * (NUMBER_OF_LETTERS * 2));
	queue -> size = 0;
}

node *make_huffman_tree(int *frequency)
{
	int i, n;
	node *root;
	node *left;
	node *right;
	priority_queue *queue = (priority_queue *)malloc(sizeof(priority_queue));
	
	init_queue(queue);

	for(i = 0; i < NUMBER_OF_LETTERS; i++){
		if(frequency[i] != 0){
			root = (node *)malloc(sizeof(node));
			root -> frequency = frequency[i];
			if(i == NUMBER_OF_LETTERS - 1)
				root -> letter = ' ';
			else
				root -> letter = i + 97;
			root -> left = NULL;
			root -> right = NULL;
			queue -> nodes[queue -> size] = root;
			queue -> size += 1;
		}
	}

	build_min_heap(queue);

	n = queue -> size - 1;
	for(i = 0; i < n; i++){
		root = (node *)malloc(sizeof(node));
		left = extract_min(queue);
		right = extract_min(queue);
		root -> left = left;
		root -> right = right;
		root -> frequency = left -> frequency + right -> frequency;
		insert(queue, root);
	}

	root = extract_min(queue);
	free(queue -> nodes);
	free(queue);
	return root;
}

int is_leaf_node(node *n)
{
	if((n -> left == NULL) && (n -> right == NULL))
		return 1;
	else
		return 0;
}

void pre_order(node *n, table *t, char *enco, int length)
{
	if(n != NULL){
		int i;
		if(is_leaf_node(n)){
			t -> index[t -> size].letter = n -> letter;
			t -> index[t -> size].enco = (char *)malloc(sizeof(char) * (length + 1));
			for(i = 0; i < length; i++)
				t -> index[t -> size].enco[i] = enco[i];
			t -> index[t -> size].enco[length] = '\0';
			t -> size += 1;
		}
		enco[length] = '0';
		pre_order(n -> left, t, enco, length + 1);
		enco[length] = '1';
		pre_order(n -> right, t, enco, length + 1);
	}
}

table *make_table(node *root)
{
	table *t = (table *)malloc(sizeof(table));
	char *enco = (char *)malloc(sizeof(char) * NUMBER_OF_LETTERS);
	int length = 0;

	t -> size = 0;
	t -> index = (table_index *)malloc(sizeof(table_index) * NUMBER_OF_LETTERS);

	pre_order(root, t, enco, length);

	free(enco);
	qsort(t -> index, t -> size, sizeof(table_index), compare_letter);
	return t;
}

char *encode(char c, table *t)
{
	int i;

	for(i = 0; i < t -> size; i++){
		if(t -> index[i].letter == c)
			return t -> index[i].enco;
	}
}

void free_tree(node *root)
{
	if(root -> left != NULL)
		free_tree(root -> left);
	if(root -> right != NULL)
		free_tree(root -> right);
	free(root);
}

void free_table(table *t)
{
	int i;

	for(i = 0; i < t -> size; i++)
		free(t -> index[i].enco);
	free(t -> index);
	free(t);
}

int main()
{
	FILE *fp = fopen("data10.txt", "r");
	char *data = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);
	int n = 0;
	int frequency[NUMBER_OF_LETTERS];
	int i;
	node *root;
	table *t;

	for(i = 0; i < NUMBER_OF_LETTERS; i++)
		frequency[i] = 0;
	
	while(fscanf(fp, "%c", &data[n]) != EOF){
		if(data[n] == ' ')
			frequency[NUMBER_OF_LETTERS - 1] += 1;
		else
			frequency[data[n] - 97] += 1;
		n++;
	}

	fclose(fp);

	root = make_huffman_tree(frequency);
	t = make_table(root);

	fp = fopen("hw08_01_201200737_table.txt","w");
	for(i = 0; i < t -> size; i++)
		fprintf(fp,"%c,%s\n", t -> index[i].letter, t -> index[i].enco);
	fclose(fp);

	fp = fopen("hw08_01_201200737_encoded.txt","w");
	for(i = 0; i < n; i++)
		fprintf(fp,"%s", encode(data[i], t));
	fclose(fp);
	
	free(data);
	free_tree(root);
	free_table(t);
	return 0;
}