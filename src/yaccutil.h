
// Yacc util c functions



extern void yyerror(const char *string);
extern void write_string(char *string);
extern void write_expression(Node *node);
extern void declare_variable(char *name, char* type);
extern void assign_to_variable(char *name, double value);
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




// constants (must match token in lex file)
#ifndef BOOLEAN
#define BOOLEAN "boolean"
#endif
#ifndef REAL
#define REAL "real"
#endif




void yyerror(const char *str) {
	fprintf(stderr, "\x1B[31mERROR!\x1B[33m %s\x1B[0m\n", str);
	exit(0);
}



void write_string(char *string) {
	printf("%s", string);
}




void write_expression(Node *node) {
	if (strcmp(node->type, BOOLEAN) == 0) {
		if (node->value > 0) {
			printf("true");
		} else {
			printf("false");
		}
	} else if (strcmp(node->type, REAL) == 0) {
		printf("%f", node->value);
	}
	destroyUnnamedSymbolForExprAttr(node);
}




void declare_variable(char *name, char* type) {
	// check if there exists a variable already declared with the same name and scope equals to the current one
	// if not, create a new entry in the symbol table with name and type, otherwise raise an error
	Node *node = lookup(name);
	if (node != NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "The variable \"%s\" has been already declared in the current scope", name);
		yyerror(error);
	}
	push(name, type);
	// TESTS:
	// + already declared variable: passed
	// + not valid type: passed (already blocked by lex via syntax error)
}




void assign_to_variable(char *name, double value) {
	// assign a value to a variable only if the variable has been previously declared in the current scope
	// if not, raise an error
	Node *node = lookup(name);
	if (node == NULL) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot assign the value. The variable \"%s\" has not been declared in the current scope", name);
		yyerror(error);
	}
	// now set the value (double). In case of variable of type boolean, we have to check if the double value
	// received by lex [double parse_boolean(char *boolean)] is either 0 or 1. If not, we are trying to assign
	// a real/double value to a boolean variable, which is not allowed. In this case, raise an error
	if (strcmp(node->type, BOOLEAN) == 0 && (value != 0 || value != 1)) {
		char *error = malloc(sizeof(100));
		sprintf(error, "Cannot assign a real value \"%f\" to the boolean variable \"%s\"", value, name);
		yyerror(error);
	}
	// set_value(node, value);
	// TESTS:
	// + assign to undeclared variable: passed
	// + assign valid value ie real or boolean: 
}




Node *binary_operation(Node *x, Node *y, char *type, char *op) {
	if (strcmp(x->type, type) == 0 && strcmp(x->type, type) == 0) {
		double value = binary_operation_get_value(x->value, y->value, op);
		Node *exprattr = createUnnamedSymbolForExprAttr(type, value);
		destroyUnnamedSymbolForExprAttr(x);
		destroyUnnamedSymbolForExprAttr(y);
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
