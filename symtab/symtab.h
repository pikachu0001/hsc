
// Symbol table


/*
	REFERENCES:
	https://www.programiz.com/c-programming/c-strings
	http://www.learn-c.org/en/Linked_lists
	https://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files
	https://www.youtube.com/watch?v=EzBTm73_oU8
	https://www.daniweb.com/programming/software-development/threads/389491/unterminated-ifndef
	https://stackoverflow.com/questions/7751366/malloc-memory-for-c-string-inside-a-structure

*/



// include this .h file only once aka if SYMTAB has not been never defined yet
#ifndef SYMTAB
#define SYMTAB



// stdlib.h used for malloc()
#include <stdlib.h>
// string.h for strcpy()
#include <string.h>




// define node structure of a linked list
typedef struct node {
	char *name;
	int scope;
	double value;
	struct node *next;
} Node;




// initialize global variables since they are used by both lex and yacc
// set scope level to 0
int scope = 0;
// set head of the symbol table to null
Node *head = NULL;
// functions declaration: in this the order of writing functions does not matter
Node *push(char *name);
Node *lookup(char *name);
void pop();
void set_value(Node *node, double value);



// create a node and set just the name and push it to the list ie add as head
Node *push(char *name) {
	Node *node = lookup(name);
	if (node != NULL) {
		return node;
	}
	node = malloc(sizeof(Node));
	node->name = malloc(sizeof(name) + 1);	// +1 for the zero-terminator char '\0' 
	strcpy(node->name, name);
	node->scope = scope;
	node->next = head;
	head = node;
	return node;
}



// pop a node from the list ie remove as head
void pop() {
	if (head != NULL) {
		Node *node = head;
		head = head->next;
		free(node->name);
		free(node);
	}
}



// here some setters used by yacc to set some variables according to some fired productions
// set some values of some previously pushed but not fully initialized variables by the lexer
// in the symbol table

// set double value
void set_value(Node *node, double value) {
	node->value = value;
}



// lookup
Node *lookup(char *name) {
	Node *node = head;
	while(node != NULL && strcmp(node->name, name) != 0) {
		node = node->next;
	}
	return node;
}



#endif
