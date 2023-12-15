#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/* DO NOT EDIT THE LINES BELOW */
#define STRING_MAX 1024

typedef struct node {
	char *name;
	int lines;
	int runtime;
	int memory_usage;

	struct node *next;
} Node;

typedef struct linked_list {
	Node *head;
} LinkedList;

void readInputString(char *, int);
void readInputNumber(int *);
void readInputChar(char *);

LinkedList * newList();
char getCommand();

void handleInsert(LinkedList *);
void handleDelete(LinkedList *);
void handleSearch(LinkedList *);
void handlePrint(LinkedList *);
void handleQuit(LinkedList *);

Node *createNode(char[], int, int, int, Node *);
bool insertAtFront(LinkedList *, char[], int, int, int);
bool insertIntoOrderedList(LinkedList *, char[], int, int, int);


int main() {
	LinkedList *list = newList();
	char command = '\0';

	printf("Experimental database entry\n");

	while (command != 'Q') {
		command = getCommand();

		switch (command) {
			case 'I':
				handleInsert(list);
				break;
			case 'D':
				handleDelete(list);
				break;
			case 'S':
				handleSearch(list);
				break;
			case 'P':
				handlePrint(list);
				break;
			case 'Q':
				handleQuit(list);
				break;
		}
	}

	free(list);
	return 0;
}
/* DO NOT EDIT THE LINES ABOVE */

void handleInsert(LinkedList *list) {
	int characters, lines, runtime, memory;

	printf("\nNumber of characters in file name: ");
	readInputNumber(&characters);
	char *name = (char *)malloc(sizeof(char) * characters + 1);

	printf("File name: ");
	readInputString(name, characters + 1);
	
	printf("Number of lines in CSV file: ");
	readInputNumber(&lines);

	printf("Experiment runtime (ms): ");
	readInputNumber(&runtime);

	printf("Experiment memory usage (B): ");
	readInputNumber(&memory);

	if (insertIntoOrderedList(list, name, lines, runtime, memory)) {
	} else {
		printf("\nAn entry with that file name already exists.\n");
	}
}


void handleDelete(LinkedList *list) {
	char *name = (char *)malloc(sizeof(char) * STRING_MAX);
	printf("\nEnter a file name to delete: ");
	readInputString(name, STRING_MAX);

	Node *current = list->head;

	if (current == NULL) {
		printf("An entry for file <%s> does not exist.", name);
	} else if (strcmp(name, current->name) == 0 && current->next == NULL) {
		printf("Deleting entry for CSV file <%s>", name);
		free(current->name);
		free(current);
		list->head = NULL;
	} else if (strcmp(name, current->name == 0 && current->next != NULL)) {
		printf("Deleting entry for CSV file <%s>", name);
		Node *newHead = list->head->next;
		free(list->head->name);
		free(list->head);
		list->head = newHead;
	} else {
		while(current->next != NULL) {
			if (strcmp(name, current->next->name) == 0) {
				Node *temp = current->next;
				current->next = temp->next;
				printf("Deleting entry for CSV file <%s>", name);
				free(temp->name);
				free(temp);
				break;
			} else {
				current = current->next;
			}
			
			if (current->next == NULL) {
				printf("An entry for file <%s> does not exist.\n", name);
			}
		} 
		free(name);
	}
}

void handleSearch(LinkedList *list) {
	char *name = (char *)malloc(sizeof(char) * STRING_MAX);
	printf("\nEnter a file name to find: ");
	readInputString(name, STRING_MAX);

	Node *current = list->head;

	if (current == NULL) {
		printf("An entry for file <%s> does not exist.\n", name);
	} else if (strcmp(name, current->name) == 0) {
		printf("File <%s>\nLines: %d\nRuntime (ms): %d\nMemory usage (B): %d\nThroughput: %.2f\n", name, current->lines, current->runtime, current->memory_usage, (float)(current->lines)/((current->runtime)/1000));
	} else {
		while(current->next != NULL) {
			if (strcmp(name, current->next->name) == 0) {
				printf("File <%s>\nLines: %d\nRuntime (ms): %d\nMemory usage (B): %d\nThroughput: %.2f\n", name, current->lines, current->runtime, current->memory_usage, (float)(current->lines)/((current->runtime)/1000));
				break;
			} else {
				current = current->next;
			}

			if (current->next == NULL) {
				printf("An entry for file <%s> does not exist.\n", name);
			}
		} 
	}
	free(name);
}

void handlePrint(LinkedList *list) {
	Node *current = list->head;

	printf("\nData entries:");
	if (current == NULL) {
		printf("\nThere are no data entries.\n");
	} else {
		while (current->next != NULL) {
			printf("File <%s>\nLines: %d\nRuntime (ms): %d\nMemory usage (B): %d\nThroughput: %.2f\n", current->name, current->lines, current->runtime, current->memory_usage, (current->lines)/((current->runtime)/1000));
			current = current->next;
		}
	}
}

void handleQuit(LinkedList *list) {
	if (list->head == NULL) {
	} else {
		while (list->head != NULL) {
			printf("Deleting entry for CSV file <%s>\n", list->head->name);
			Node *newHead = list->head->next;
			free(list->head);
			list->head = newHead;
		}
	}
	list->head = NULL;
}

Node *createNode(char nameInput[], int linesInput, int runtimeInput, int memoryInput, Node *nextInput) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	if (newNode != NULL) {
		newNode->name = nameInput;
		newNode->lines = linesInput;
		newNode->runtime = runtimeInput;
		newNode->memory_usage = memoryInput;
		newNode->next = nextInput;
	}
	return newNode;
}

bool insertAtFront(LinkedList *list, char nameInput[], int linesInput, int runtimeInput, int memoryInput) {
	Node *current = list->head;
	Node *temp = createNode(nameInput, linesInput, runtimeInput, memoryInput, current);
	if (temp == NULL) {
		return false;
	}
	temp->next = list->head;
	list->head = temp;
	return true;
}


bool insertIntoOrderedList(LinkedList *orderedList, char nameInput[], int linesInput, int runtimeInput, int memoryInput) {
	Node *current = orderedList->head;

	if (current == NULL) { // If list is empty OR the name is greater than first name, insert at front!
		return insertAtFront(orderedList, nameInput, linesInput, runtimeInput, memoryInput);
	} else if (strcmp(nameInput, current->name) == 0) { // MAN THE NAMES ARE IDENTICAL... AINT NO WAY
		return false;
	} else if (strcmp(nameInput, current->name) < 0) {
		return insertAtFront(orderedList, nameInput, linesInput, runtimeInput, memoryInput);
	}

	while(current->next != NULL) { // Value to insert is larger than next element in list
		if (strcmp(nameInput, current->next->name) == 0) { // Nuff said...
			return false;
		} else if (strcmp(nameInput, current->next->name) > 0) {
			break;
		} else {
			current = current->next; // We go next...
		}
	}

	// Insert when these statements are not true
	Node *newNode = createNode(nameInput, linesInput, runtimeInput, memoryInput, current->next);
	if (newNode == NULL) {
		return false;
	}

	newNode->next = current->next;
	current->next = newNode;
	return true;
}

/* DO NOT EDIT THE LINES BELOW */
void readInputString(char *str, int length) {
	int i = 0;
	char c;

	while (i < length && (c = getchar()) != '\n') {
		str[i++] = c;
	}

	str[i] = '\0';
}

void readInputNumber(int *number) {
	char buf[STRING_MAX];
	readInputString(buf, STRING_MAX);
	*number = (int)strtol(buf, (char **)NULL, 10);
}

void readInputChar(char *character) {
	char buf[2];
	readInputString(buf, 3);
	*character = buf[0];
}

LinkedList * newList() {
	LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
	list->head = NULL;
	return list;
}

char getCommand() {
	char command;

	printf("\nSupported commands are:\n");
	printf("  I - Insert\n");
	printf("  D - Delete\n");
	printf("  S - Search\n");
	printf("  P - Print\n");
	printf("  Q - Quit\n");

	printf("\nPlease select a command: ");
	readInputChar(&command);

	while (command != 'I' && command != 'D' && command != 'S' && command != 'P' && command != 'Q') {
		printf("Invalid command <%c>, please select a command: ", command);
		readInputChar(&command);
	}

	return command;
}
/* DO NOT EDIT THE LINES ABOVE */
