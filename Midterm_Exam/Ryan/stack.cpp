#include "stack.h"

#define NULL 0

stack::stack() {
	top = NULL;
}

void stack::push(POINT startPoint, POINT endPoint, Fig fig) {
	node* prev_node = top;
	top = new node{ startPoint, endPoint, fig, prev_node };
}

void stack::pop(POINT* startPointP, POINT* endPointP, Fig* figP) {
	if (NULL != top) {
		*startPointP = top->startPoint;
		*endPointP = top->endPoint;
		*figP = top->fig;
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
	}
	else {
		
		figP->Fig::Fig();
	}
}

stack::~stack() {
	while (NULL != top) {
		node* prev_node = top->prev_node;
		delete top;
		top = prev_node;
	}
}