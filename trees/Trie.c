#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h> 
#include <string.h> 

#define MAX_KEYS (26)

// only lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef enum { FALSE, TRUE } bool;

struct node *root = NULL;

struct node
{
	bool isEndOfWord;
	char key;
	struct node *children[MAX_KEYS];
};

bool isLeaf(struct node *ptr)
{
	for(int i = 0; i < MAX_KEYS; i++)
	{
		if(ptr->children[i] != NULL)
			return FALSE;
	}

	return TRUE;
}

bool search(struct node *ptr, const char *text, int sz)
{
	if(ptr == NULL)
		return FALSE;

	if(sz == strlen(text) && ptr->isEndOfWord == TRUE)
		return TRUE;

	int index = CHAR_TO_INDEX(text[sz]);
	return search(ptr->children[index], text, ++sz);
}

void display(struct node *ptr, int level)
{
	if(ptr != NULL)
	{
		for(int i = 0; i < MAX_KEYS; i++)
		{
			if(ptr->children[i] != NULL)
				display(ptr->children[i], level+1);
		}

		for (int j = 0; j < level; j++)
			printf(" ");
		printf("%c\n", ptr->key);
	}
}

void listAllWords(struct node *ptr, char *prefix)
{
	if(ptr != NULL)
	{
		char *new_pref = (char*) malloc(sizeof(prefix) + sizeof(char));
		strcpy(new_pref, prefix);
		new_pref[strlen(prefix)] = ptr->key;

		if(ptr->isEndOfWord == TRUE)
			printf("%s\n", new_pref);

		for(int i = 0; i < MAX_KEYS; i++)
			listAllWords(ptr->children[i], new_pref);
	}
}

struct node *insert(struct node *ptr, const char *text, int sz)
{
	if(sz == strlen(text))
	{
		ptr->isEndOfWord = TRUE;
		return ptr;
	}

	int index = CHAR_TO_INDEX(text[sz]);
	struct node *ch = ptr->children[index];
	if(ch == NULL)
	{
		ch = (struct node*)malloc(sizeof(struct node));
		ch->key = text[sz];

		for(int i = 0; i < MAX_KEYS; i++)
			ch->children[i] = NULL;

		ptr->children[index] = ch;

	}

	return insert(ch, text, ++sz);
}

struct node *deleteElement(struct node *ptr, const char *text, int sz)
{
	if(sz == strlen(text))
	{
		if(ptr->isEndOfWord && isLeaf(ptr))
			return NULL;
		else
		{
			ptr->isEndOfWord = FALSE;
			return ptr;
		}
	}

	int index = CHAR_TO_INDEX(text[sz]);
	ptr->children[index] = deleteElement(ptr->children[index], text, ++sz);

	if(ptr->children[index] == NULL && !ptr->isEndOfWord && isLeaf(ptr))
		return NULL;
	else
		return ptr;
}

int main()
{
	char text[256];
	int option;

	root =  (struct node*)malloc(sizeof(struct node));

	while(1)
	{
		printf("1.Insert\n");
		printf("2.Delete\n");
		printf("3.Display\n");
		printf("4.Search\n");
		printf("5.Quit\n");
		printf("Enter your option : ");
		scanf("%d",&option);

		switch(option)
		{
			case 1:
				printf ("Insert text: ");
				memset(text, 0, 255);
				scanf("%s", text);
				insert(root, text, 0);
				break;
			case 2:
				printf("Enter the word to be deleted : ");
				memset(text, 0, 255);
				scanf("%s", text);

				if(search(root, text, 0))
					deleteElement(root, text, 0);
				else
					printf("word: is not found.\n");
				break;
			case 3:
				if(root==NULL)
				{
					printf("Tree is empty\n");
					continue;
				}

				printf("Tree is :\n");
				display(root, 1);

				printf("Words :\n");
				memset(text, 0, 255);
				listAllWords(root, text);
				break;
			case 4:
				printf("Enter the word to be searched : ");
				memset(text, 0, 255);
				scanf("%s", text);
				if(search(root, text, 0))
					printf("word: is found.\n");
				else
					printf("word: is not found.\n");
				break;
			case 5:
				exit(1);
			default:
				printf("Wrong option\n");
		}
	}
}
