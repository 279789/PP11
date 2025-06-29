#include <stdio.h>
#include "slist.h"
#include <stdlib.h>

SNode* add_node(SNode *head, int value) {
	SNode *node = malloc(sizeof(SNode));
		
		node->value = value;
		node->next = NULL;

	if (head == NULL) return node; //list empty

	SNode *actual = head;
	while (actual->next != NULL) {

		actual = actual->next;
		
	}
	
	actual->next = node;
	return head;

}



int count_nodes(SNode *head) {
	int count = 0;
	for(SNode *actual = head; actual->next != NULL; actual = actual->next) {
		count++;
	}
	return count;
}


void free_list(SNode *head) {
	SNode *actual = head;
	while (actual != NULL) {
		SNode *next = actual->next;
		free(actual);
		actual = next;
	}
}
	
	




