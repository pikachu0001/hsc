
// Yacc util c functions


/*
	REFERENCES:
	https://www.programiz.com/c-programming/c-strings
	http://www.learn-c.org/en/Linked_lists
	https://stackoverflow.com/questions/1653958/why-are-ifndef-and-define-used-in-c-header-files
	https://www.youtube.com/watch?v=EzBTm73_oU8
	https://stackoverflow.com/questions/7751366/malloc-memory-for-c-string-inside-a-structure
	https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
*/




// include this .h file only once aka if YACCUTIL has not been never defined yet
#ifndef YACCUTIL
#define YACCUTIL




// constants (must match token in lex file)
#ifndef BOOLEAN
#define BOOLEAN "boolean"
#endif
#ifndef REAL
#define REAL "real"
#endif




// function definitions
extern int yylineno;
extern void yyerror(const char *string);
extern void write_string(char *string);
extern void write_expression(Node *node);
extern void declare_variable(char *name, char* type);
extern void assign_to_variable(char *name, Node *exprattr);
extern void pop_variables_at_scope_closed();
extern Node *get_variable_for_exprattr_transmission(char *name);
extern Node *binary_operation(Node *x, Node *y, char *type, char *op);
extern double binary_operation_get_value(double x, double y, char *op);
extern Node *unary_operation(Node *x, char *type, char *op);
extern double unary_operation_get_value(double x, char *op);
extern Node *op_add(Node *x, Node *y);
extern Node *op_sub(Node *x, Node *y);
extern Node *op_mul(Node *x, Node *y);
extern Node *op_div(Node *x, Node *y);
extern Node *op_uminus(Node *x);
extern Node *op_and(Node *x, Node *y);
extern Node *op_or(Node *x, Node *y);
extern Node *op_not(Node *x);




void yyerror(const char *str) {
	fprintf(stderr, "\x1B[31mERROR near line %d:\x1B[33m %s\x1B[0m\n", yylineno, str);
	exit(0);
}




void write_string(char *string) {
	printf("%s", string);
}




void write_expression(Node *exprattr) {
	// if exprattr is a variable ie a pointer to a node in the symbol table (node->node != NULL), then check if it has been initialized
	// if exprattr is a temporary unnamed exprattr (node->name == NULL), then we are sure it has a value so we do nothing... just continue
	if (exprattr->name != NULL && exprattr->initialized == 0) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot get the value. The variable \"%s\" has not been initialized", exprattr->name);
		yyerror(error);
	}
	if (strcmp(exprattr->type, BOOLEAN) == 0) {
		if (exprattr->value > 0) {
			printf("true");
		} else {
			printf("false");
		}
	} else if (strcmp(exprattr->type, REAL) == 0) {
		printf("%f", exprattr->value);
	}
	destroyUnnamedSymbolForExprAttrOnly(exprattr);
}




void declare_variable(char *name, char* type) {
	// check if there exists a variable already declared with the same name and scope equals to the current one
	// if not, create a new entry in the symbol table with name and type, otherwise raise an error
	Node *node = lookup(name);
	if (node != NULL && node->scope == scope) {
		char *error = malloc(sizeof(100));
		sprintf(error, "The variable \"%s\" has been already declared in the current scope", name);
		yyerror(error);
	}
	push(name, type);
}




void assign_to_variable(char *name, Node *exprattr) {
	// assign an expression to a variable only if the variable has been previously declared
	// if not, raise an error
	Node *node = lookup(name);
	if (node == NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot assign the value. The variable \"%s\" has not been previously declared", name);
		yyerror(error);
	}
	// if exprattr is a variable ie a pointer to a node in the symbol table (node->node != NULL), then check if it has been initialized
	// if exprattr is a temporary unnamed exprattr (node->name == NULL), then we are sure it has a value so we do nothing... just continue
	if (exprattr->name != NULL && exprattr->initialized == 0) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot get the value. The variable \"%s\" has not been initialized", exprattr->name);
		yyerror(error);
	}
	// now set the value according to the type. Raise an error we try to assign to a variable an expression whose type
	// is not equal to the one of the variable.
	if (strcmp(node->type, exprattr->type) == 0) {
		node->value = exprattr->value;
		node->initialized = 1;
	} else {
		char *error = malloc(sizeof(100));
		sprintf(error, "Assigning a \"%s\" expression to the variable \"%s\" of type \"%s\" is not allowed", exprattr->type, name, node->type);
		yyerror(error);
	}
	destroyUnnamedSymbolForExprAttrOnly(exprattr);
}




void pop_variables_at_scope_closed() {
	while(head->scope == scope) {
		pop();
	}
	decrease_scope();
}




Node *get_variable_for_exprattr_transmission(char *name) {
	// transmit the node pointer to a variable to an exprattr only if the variable exists. The first occurrence of name will be picked up
	// which is also what we want, ie the one with higher scope (the one with scope closest to the current scope). If not, raise an error
	Node *node = lookup(name);
	if (node == NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot get the value. The variable \"%s\" has not been previously declared", name);
		yyerror(error);
	}
	return node;
}




Node *binary_operation(Node *x, Node *y, char *type, char *op) {
	if (strcmp(x->type, type) == 0 && strcmp(y->type, type) == 0) {
		double value = binary_operation_get_value(x->value, y->value, op);
		Node *exprattr = createUnnamedSymbolForExprAttr(type, value);
		destroyUnnamedSymbolForExprAttrOnly(x);
		destroyUnnamedSymbolForExprAttrOnly(y);
		return exprattr;
	}
	char *error = malloc(sizeof(100));
	sprintf(error, "\"%s\" operation not allowed between \"%s\" and \"%s\"", op, x->type, y->type);
	yyerror(error);
}




double binary_operation_get_value(double x, double y, char *op) {
	if (strcmp(op, "+") == 0)	return x + y;
	if (strcmp(op, "-") == 0)	return x - y;
	if (strcmp(op, "*") == 0)	return x * y;
	if (strcmp(op, "/") == 0)	return x / y;
	if (strcmp(op, "&&") == 0)	return x && y;
	if (strcmp(op, "||") == 0)	return x || y;
}




Node *unary_operation(Node *x, char *type, char *op) {
	if (strcmp(x->type, type) == 0) {
		x->value = unary_operation_get_value(x->value, op);
		return x;	// no need to create a new node. Since it's a unary operation, modify the original node and return the same ponter back
	}
	char *error = malloc(sizeof(100));
	sprintf(error, "\"%s\" operation not allowed for \"%s\"", op, x->type);
	yyerror(error);
}




double unary_operation_get_value(double x, char *op) {
	if (strcmp(op, "um") == 0)	return -x;
	if (strcmp(op, "!") == 0) 	return !x;
}




Node *op_add(Node *x, Node *y) {
	return binary_operation(x, y, REAL, "+");
}




Node *op_sub(Node *x, Node *y) {
	return binary_operation(x, y, REAL, "-");
}




Node *op_mul(Node *x, Node *y) {
	return binary_operation(x, y, REAL, "*");
}




Node *op_div(Node *x, Node *y) {
	return binary_operation(x, y, REAL, "/");
}




Node *op_uminus(Node *x) {
	return unary_operation(x, REAL, "um");
}




Node *op_and(Node *x, Node *y) {
	return binary_operation(x, y, BOOLEAN, "&&");
}




Node *op_or(Node *x, Node *y) {
	return binary_operation(x, y, BOOLEAN, "||");
}




Node *op_not(Node *x) {
	return unary_operation(x, BOOLEAN, "!");
}




#endif
