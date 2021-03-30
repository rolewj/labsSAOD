#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

typedef struct ListElement {
	int value;
	struct ListElement* to_tail;
	struct ListElement* to_head;
} ListElement;

typedef struct {
	ListElement* head;
	ListElement* tail;
} List;

List Create(){
	List a;
	a.head = NULL;
	a.tail = NULL;
	return a;
}

void add_head(List* list, int value) {
	ListElement* t = (ListElement*) malloc(sizeof(ListElement));
	t->value = value;
	t->to_tail = list->head;
	t->to_head = NULL;
	list->head = t;
	if(t->to_tail == NULL) {
		list->tail = t;
	}
	else {
		t->to_tail->to_head = t;
	}
}

void add_tail(List* list, int value) {
	ListElement* t = (ListElement*) malloc(sizeof(ListElement));
	t->value = value;
	t->to_head = list->tail;
	t->to_tail = NULL;
	list->tail = t;
	if(t->to_head == NULL) {
		list->head = t;
	}
	else {
		t->to_head->to_tail = t;
	}
}

int popHead(List* list, int* c) {
	ListElement* head = list->head;
	if(head == NULL) {
		return 0;
	}
	*c = head->value;
	list->head = head->to_tail;
	if(list->head == NULL) {
		list->tail = NULL;
	}
	else {
		list->head->to_head = NULL;
	}
	free(head);
	return 1;
}

int popTail(List* list, int* c) {
	ListElement* tail = list->tail;
	if(tail == NULL) {
		return 0;
	}
	*c = tail->value;
	list->tail = tail->to_head;
	if(list->tail == NULL) {
		list->head = NULL;
	}
	else {
		list->tail->to_tail = NULL;
	}
	free(tail);
	return 1;
}

int* getHead(List* list) {
	if(list->head != NULL) {
		return &list->head->value;
	} 
	else {
		return NULL;
	}
}

int* getTail(List* list) {
	if(list->tail != NULL) {
		return &list->tail->value;
	}
	else {
		return NULL;
	}
}

int is_empty(List* list) {
	return list->head == NULL;
}

void deduplicate(List* list) {
	ListElement* from = list->head;
	while(from != NULL) {
		ListElement* next = from->to_tail;
		while(next != NULL) {
			ListElement* next_to_tail = next->to_tail;
			if(next->value == from->value) {
				next->to_head->to_tail = next_to_tail;
				if (next_to_tail == NULL) {
					list->tail = next->to_head;
				}
				else {
					next_to_tail->to_head = next->to_head;
				}
				free(next);
			}
			next = next_to_tail;
		}
		from = from->to_tail;
	}
}

int* get_at_from_head(List* list, int idx) {
	ListElement* to_tail = list->head;
	while(1) {
		if(to_tail == NULL) {
			return NULL;
		}
		if(idx == 0) {
			return &to_tail->value;
		}
		to_tail = to_tail->to_tail;
		idx--;
	}
}

int* get_at_from_tail(List* list, int idx) {
	ListElement* to_head = list->tail;
	while(1) {
		if(to_head == NULL) {
			return NULL;
		}
		if(idx == 0) {
			return &to_head->value;
		}
		to_head = to_head->to_head;
		idx--;
	}
}

int Palindrome(List* list) {
	ListElement* to_head = list->tail;
	ListElement* to_tail = list->head;
	while(1) {
		if(to_head == NULL) {
			return 1;
		}
		if(to_head->value != to_tail->value) {
			return 0;
		}
		to_head = to_head->to_head;
		to_tail = to_tail->to_tail;
	}
}

void print_list(List* list) {
	printf("\"");
	ListElement* to_tail = list->head;
	while(to_tail != NULL) {
		printf("%d ", to_tail->value);
		to_tail = to_tail->to_tail;
	}
	printf("\"\n");
}

void clear_list(List* list) {
	while(list->head != NULL) {
		ListElement* current = list->head;
		list->head = list->head->to_tail;
		free(current);
	}
	list->tail = NULL;
}

int main(int argc, char** argv) {
	List list = Create();
	while(1) {
		print_list(&list);
		char input[80];
		scanf("%s", input);
		if(strcmp(input, "pop_head") == 0) {
			int value;
			if(popHead(&list, &value)) {
				printf("%d\n", value);
			}
			else {
				printf("List is empty\n");
			}
		}
		else if(strcmp(input, "pop_tail") == 0) {
			int value;
			if(popTail(&list, &value)) {
				printf("%d\n", value);
			}
			else {
				printf("List is empty\n");
			}
		}
		else if(strcmp(input, "get_at_head") == 0) {
			int idx;
			scanf("%d", &idx);
			int* value = get_at_from_head(&list, idx);
			if(value != NULL) {
				printf("%d\n", *value);
			}
			else {
				printf("Out of bounds\n");
			}
		}
		else if(strcmp(input, "get_at_tail") == 0) {
			int idx;
			scanf("%d", &idx);
			int* value = get_at_from_tail(&list, idx);
			if(value != NULL) {
				printf("%d\n", *value);
			}
			else {
				printf("Out of bounds\n");
			}
		}
		else if(strcmp(input, "add_head") == 0) {
			int value;
			scanf("%d", &value);
			add_head(&list, value);
		}
		else if(strcmp(input, "add_tail") == 0) {
			int value;
			scanf("%d", &value);
			add_tail(&list, value);
		}
		else if(strcmp(input, "dedupe") == 0) {
			deduplicate(&list);
		}
		else if(strcmp(input, "clear") == 0) {
			clear_list(&list);
		}
		else if(strcmp(input, "palindrome") == 0) {
			printf("%s\n", Palindrome(&list) ? "yes" : "no");
		}
		else if(strcmp(input, "exit") == 0) {
			break;
		}
		else {
			printf("Unknown command\n");
		}
	}
	clear_list(&list);
	return 0;
}
