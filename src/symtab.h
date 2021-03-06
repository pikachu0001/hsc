
// Symbol table


/*
	REFERENCES:
	https://www.programiz.com/c-programming/c-strings
	http://www.learn-c.org/en/Linked_lists
	https://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files
	https://www.youtube.com/watch?v=EzBTm73_oU8
	https://stackoverflow.com/questions/7751366/malloc-memory-for-c-string-inside-a-structure
	https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
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
	int initialized;
	double value;
	struct node *next;
} Node;





// keep track of the current scope level
int scope = 0;
// head of the symbol table (stack)
Node *head = NULL;




// functions definitions
Node *createUnnamedSymbolForExprAttr(char* type, double value);
void push(char *name, char *type);
void pop();
Node *lookup(char *name);
void increase_scope();
void decrease_scope();




// create a simple unnamed symbol just to keep info for non terminal expression in the expression attribute
Node *createUnnamedSymbolForExprAttr(char *type, double value) {
	Node *node = malloc(sizeof(Node));
	node->type = malloc(sizeof(type) + 1);
	node->name = NULL;
	strcpy(node->type, type);
	node->scope = scope;
	node->initialized = 1;
	node->value = value;
	node->next = NULL;
	return node;
}




// destroy the node of an expression attribute as soon as it is no longer needed eg: after reduce operation
void destroyUnnamedSymbolForExprAttrOnly(Node *node) {
	if (node->name != NULL) {
		/* It's a node in the symbol table ie a variable. Do not drop it */
		return;
	}
	// just flush memory related to the expression attribute which is of type node
	free(node->type);
	free(node);
}




// create a node, set name and type and insert it at the top of the stack
void push(char *name, char *type) {
	// allocate memory for the node and string
	Node *node = malloc(sizeof(Node));
	node->name = malloc(sizeof(name) + 1);	// +1 for the zero-terminator char '\0'
	node->type = malloc(sizeof(type) + 1);
	strcpy(node->name, name);
	strcpy(node->type, type);
	node->scope = scope;
	node->initialized = 0;
	node->value = 0;
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




// lookup: search for a variable with name = name. In case of variables with same name (because of different scopes)
// pick the variable with the greatest scope number ie the first variable with name = name closest to the top of the stack
Node *lookup(char *name) {
	Node *node = head;
	while(node != NULL && strcmp(node->name, name) != 0) {
		node = node->next;
	}
	return node;
}




// increase scope counter
void increase_scope() {
	scope++;
}




// decrease scope counter
void decrease_scope() {
	scope--;
}




#endif
