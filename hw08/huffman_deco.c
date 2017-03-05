#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_LETTERS 27

typedef struct node {
	char letter;
	struct node *left;
	struct node *right;
} node;

node *new_node()
{
	node *n = (node *)malloc(sizeof(node));
	n -> letter = NULL;
	n -> left = NULL;
	n -> right = NULL;

	return n;
}

void make_huffman_tree(node *root, char letter, char *enco)
{
	if(enco[0] == '\0' || enco[0] == '\n') {
		root -> letter = letter;
		return;
	}

	if(enco[0] == '0') {
		if(root -> left == NULL) {
			root -> left = new_node();
		}

		make_huffman_tree(root -> left, letter, enco + 1);
	}

	if(enco[0] == '1') {
		if(root -> right == NULL) {
			root -> right = new_node();
		}

		make_huffman_tree(root -> right, letter, enco + 1);
	}
}

int is_leaf_node(node *n)
{
	if((n -> left == NULL) && (n -> right == NULL)) {
		return 1;
	}

	else {
		return 0;
	}
}

void free_tree(node *root)
{
	if(root -> left != NULL) {
		free_tree(root -> left);
	}

	if(root -> right != NULL) {
		free_tree(root -> right);
	}

	free(root);
}

int main()
{
	FILE *fp = fopen("data10_table.txt", "r");
	FILE *write_fp;
	char letter;
	char enco[NUMBER_OF_LETTERS];
	node *root = new_node();
	node *n;

	while(fscanf(fp, "%c,", &letter) != EOF) {
		fgets(enco, sizeof(enco), fp);
		make_huffman_tree(root, letter, enco);
	}

	fclose(fp);

	n = root;
	fp = fopen("data10_encoded.txt" ,"r");
	write_fp = fopen("data10_decoded.txt", "w");
	while(fscanf(fp, "%c", &letter) != EOF) {
		if(letter == '0') {
			n = n -> left;
		}

		else {
			n = n -> right;
		}

		if(is_leaf_node(n)) {
			fprintf(write_fp, "%c", n -> letter);
			n = root;
		}
	}

	fclose(fp);
	fclose(write_fp);
	free_tree(root);

	return 0;
}
