


#include <stdio.h>
#include "symtab.h"



int main(int argc, char const *argv[]) {
	Node *l = push("luk");
	set_value(l, 12.6);
	printf("%s\n%i\n%f\n\n", head->name, head->scope, head->value);
	Node *n = push("gio");
	set_value(n, 0);
	printf("%s\n%i\n%f\n\n", head->name, head->scope, head->value);
	pop();
	printf("%s\n%i\n%f\n\n", head->name, head->scope, head->value);
	pop();
	if (head != NULL) {
		printf("%s\n%i\n%f\n\n", head->name, head->scope, head->value);
	} else {
		printf("%s\n\n", "empty");
	}
	return 0;
}