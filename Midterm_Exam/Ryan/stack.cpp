#include "stack.h"

#define NULL 0

stack::stack() {
	top = NULL;
}

void stack::push(POINT startPoint, POINT endPoint, Fig fig) {
	node* prev_node = top;
	top = new node{ startPoint, endPoint,fig , prev_node };
}

bool stack::pop(POINT* startPoint, POINT* endPoint, Fig* fig) {
	if (NULL != top) {
		*startPoint = top->startPoint;
		*endPoint = top->endPoint;
		*fig = top->fig;
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
		return 1;
	}
	else {
		return 0;
	}
}
stack::~stack() {
	while (NULL != top) {
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
	}
}
