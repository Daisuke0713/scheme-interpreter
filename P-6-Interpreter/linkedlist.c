#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "value.h"
/*
 * linkedlist.c
 *
 */

Value *make_null() {
	Value *null = malloc(sizeof(Value));
	null->type = NULL_TYPE;
	return null;
}

Value *cons(Value *new_car, Value *new_cdr) {
	Value *cons_cell = malloc(sizeof(Value));
	cons_cell->type = CONS_TYPE;
	cons_cell->c.car = new_car;
	cons_cell->c.cdr = new_cdr;
	return cons_cell;
}

Value *car(Value *list) {
	assert(list->type == CONS_TYPE
			&& "ERROR IN LINKEDLIST.C CAR(list)- list much be a type of CONS_TYPE");
	return list->c.car;
}

Value *cdr(Value *list) {
	assert(list->type == CONS_TYPE
			&& "ERROR IN LINKEDLIST.C CDR(list) - list much be a type of CONS_TYPE");
		return list->c.car;
}

bool is_null(Value *list) {
	return list->type == NULL_TYPE;
}

int size(Value *list) {
	int list_size = 0;
	Value *temp = &list;
	while(!is_null(list)) {
		temp = cdr(temp);
		list_size += 1;
	}
	return list_size;
}

void display(Value *list) {
	print("[");
	while(!is_null(list)) {
		switch(car(list)->type) {
			case INTEGER_TYPE:
				print("%i", car(list)->i); break;
			case DOUBLE_TYPE:
				print("%d", car(list)->d); break;
			case STRING_TYPE:
				print("%s", car(list)->s); break;
			case CONS_TYPE:	break;
			case NULL_TYPE: break;
		}

		if(cdr(list)->type != NULL_TYPE) {
			print(", "); // separating comma
		}

		list = cdr(list);
	}
	print("]\n");
}

Value reverse(Value *list) {
	// Need memory allocation for every node of the new list
	Value r_list = make_null();
	while(!is_null(list)) {
		Value new_car = malloc(sizeof(Value));
		new_car->type = car(list)->type;
		switch(car(list)->type) {
			case INTEGER_TYPE:
				new_car->i = car(list)->i; break;
			case DOUBLE_TYPE:
				new_car->d = car(list)->d; break;
			case STRING_TYPE:
				char *string = car(list)->s;
				new_car->s = malloc(sizeof(char) * (strlen(string)+1));
				strcpy(new_car->s, string); break;
			case CONS_TYPE: break;
			case NULL_TYPE: break;
		}
		r_list = cons(new_car, r_list);
		list = cdr(list);
	}
	return r_list;
}

void cleanup(Value *list) {
	// Need to store the next node beforehand for the sake
	// of later freeing
	Value *curr_cell = list;
	Value *next_cell;

	while(!is_null(curr_cell)) {
		next_cell = cdr(curr_cell);
		if(car(curr_cell)->type == STRING_TYPE) {
			// Need to free string
			free(car(curr_cell)->s);
		}
		free(car(curr_cell));
		free(curr_cell);
		curr_cell = next_cell;
	}
	free(curr_cell); // Free the last NULL node
}

int main() {

}
