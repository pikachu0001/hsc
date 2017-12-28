
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




// include constant only once (must match token in lex file)

#ifndef BOOLEAN
#define BOOLEAN "boolean"
#endif
#ifndef REAL
#define REAL "real"
#endif
#ifndef BOOL_TRUE
#define BOOL_TRUE "true"
#endif
#ifndef BOOL_FALSE
#define BOOL_FALSE "false"
#endif




// stdlib.h used for malloc()
#include <stdlib.h>
// string.h for strcpy()
#include <string.h>




// define node structure of a linked list
typedef struct node {
	char *name;
	char *type;
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
Node *createUnnamedSymbolForExprAttr(char* type, double value);
void push(char *name, char *type);
void pop();
int set_double_value(Node *node, double value);
int set_boolean_value(Node *node, char* boolean);
void increase_scope();
void decrease_scope();
Node *lookup(char *name);




// create a simple symbol just to keep info for non terminal expression
Node *createUnnamedSymbolForExprAttr(char *type, double value) {
	Node *node = malloc(sizeof(Node));
	node->type = malloc(sizeof(type) + 1);
	node->value = value;
	strcpy(node->type, type);
	return node;
}




// destroy the node of a Expr attr as soon as it is no longer needed eg: after reduce operation
void destroyUnnamedSymbolForExprAttrOnly(Node *node) {
	if (node->name != NULL) {
		/* It's a node in the symbol table ie a variable. Do not drop it */
		return;
	}
	free(node->type);
	free(node);
}




// create a node, set name and type, push it to the symbol table as head
void push(char *name, char *type) {
	// allocate memory for the node and char[]
	Node *node = malloc(sizeof(Node));
	node->name = malloc(sizeof(name) + 1);	// +1 for the zero-terminator char '\0'
	node->type = malloc(sizeof(type) + 1);
	// set attributes of the node
	node->scope = scope;
	strcpy(node->name, name);
	strcpy(node->type, type);
	// add node as head of the linked list and return pointer to it
	node->next = head;
	head = node;
}




// pop a node from the list ie remove as head
void pop() {
	if (head != NULL) {
		Node *node = head;
		head = head->next;
		free(node->name);
		free(node->type);
		free(node);
	}
}




// here some setters used by yacc to set some variable attrs according to some fired productions


// set double value
int set_double_value(Node *node, double value) {
	// "real" must match element in regex for type in *.lex
	if (strcmp(node->type, REAL) != 0) {
		return 0;
	}
	node->value = value;
	return 1;
}

// set boolean value
int set_boolean_value(Node *node, char* boolean) {
	if (strcmp(node->type, BOOLEAN) != 0) {
		return 0;
	}
	if (strcmp(boolean, BOOL_TRUE) == 0) {
		node->value = 1;
		return 1;
	}
	if (strcmp(boolean, BOOL_FALSE) == 0) {
		node->value = 0;
		return 1;
	}
	return 0;
}

// increase scope counter
void increase_scope() {
	scope++;
}

// decrease scope
void decrease_scope() {
	scope--;
}




// lookup
Node *lookup(char *name) {
	Node *node = head;
	while(node != NULL && node->scope == scope && strcmp(node->name, name) != 0) {
		node = node->next;
	}
	return node;
}




#endif
