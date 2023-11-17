#include "stack.h"

#define NULL 0

stack::stack() {
	top = NULL;
}

void stack::push(int input) {
	node* prev_node = top;
	top = new node{ input, prev_node };
}

int stack::pop() {
	if (NULL != top) {
		int data = top->data;
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
		return data;
	}
	else{
		return NULL;
	}
}

stack::~stack() {
	while (NULL != top) {
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
	}
}