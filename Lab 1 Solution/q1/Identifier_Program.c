#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
	char* data;
	struct Node* ltree;
	struct Node* rtree;
};

struct Node* head;
struct Node* newTree(char* p) {
	struct Node* n = malloc(sizeof(struct Node));
	n->data = malloc(strlen(p) + 1);
	strcpy(n->data, p);
	n->ltree = n->rtree = NULL;
	return n;
}

struct Node* insert(struct Node* tree, char* p) {
	if (tree == NULL)
		return newTree(p);
	int cmp = strcmp(p, tree->data);
	if (cmp <= 0)
		tree->ltree = insert(tree->ltree, p);
	else
		tree->rtree = insert(tree->rtree, p);
	return tree;
}

void inorder(struct Node* tree) {
	if (tree == NULL)
		return;
	inorder(tree->ltree);
	printf("%s\n", tree->data);
	inorder(tree->rtree);
}

FILE* fp;

int main()
{
	fp = fopen("words.txt", "r");
	char line[200];
	char delim[] = " ";
	int wordCount = 0;

	while (fgets(line, 200, fp) != NULL) 
	{
		char* ptr = strtok(line, delim);

		while (ptr != NULL)
		{
			if (isalpha(ptr[0]) || ptr[0] == '_')
			{
				ptr[0] = tolower(ptr[0]);
				wordCount++;
				head = insert(head, (ptr));
			}

			ptr = strtok(NULL, delim); 
		}
	}

	printf("There are %d identifiers in this file:\n", wordCount);
	inorder(head);

	return 0;
}