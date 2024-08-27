#include <stdio.h>
#include <stdlib.h>
#include "list.h"



// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%d", current->data);
		current = current->next;
		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

void list_test() {

	int numbers[5] = { 5, 3, 7, 2, 0 };

	List my_list = new_list();
	printf("Testing insert_at_front...\n");
	for (int i = 0; i < 5; i++) {
		insert_at_front(&my_list, numbers[i]);
	}

	printf("Expected: %d, %d, %d, %d, %d\n", numbers[4], numbers[3], numbers[2], numbers[1], numbers[0]);
	printf("Result: ");
	print_list(&my_list);
}

void option_insert(List* my_list) {
	int number;

	printf("Give an int to add to list\n");
	scanf_s("%d", &number);
	insert_at_front(my_list, number);
}

void option_delete(List* my_list) {
	int number = 0;

	printf("Give an int to remove from list\n");
	scanf_s("%d", &number);
	delete_list(my_list, number);
}

void option_print(List* my_list) {
	print_list(my_list);

}

void reverse(List* my_list) {
	ListNodePtr prev = NULL;
	ListNodePtr current = my_list->head;
	ListNodePtr next = NULL;

	while (current != NULL) {
		next = current->next;    // Store next node
		current->next = prev;    // Reverse the current node's pointer
		prev = current;          // Move pointers one position ahead
		current = next;
	}
	my_list->head = prev;

}

void merge(List* list1, List* list2) {
	List merged_list = new_list();
	ListNodePtr current1 = list1->head;
	ListNodePtr current2 = list2->head;
	ListNodePtr prev1 = NULL;
	ListNodePtr prev2 = NULL;

	while (current1 != NULL && current2 != NULL) {
		if (current1->data < current2->data) {
			// insert current1 into list
			insert_in_order(&merged_list, current1->data);
			current1 = current1->next;

		} else {                
			// insert current2 into list
			insert_in_order(&merged_list, current2->data);
			current2 = current2->next;
		}
	}

	// If there are remaining elements in list1
	while (current1 != NULL) {
		insert_in_order(&merged_list, current1->data);
		current1 = current1->next;
	}

	// If there are remaining elements in list2
	while (current2 != NULL) {
		insert_in_order(&merged_list, current2->data);
		current2 = current2->next;
	}

	// Assign merged list to list1
	list1->head = merged_list.head;
}

void list_adhoc_test() {

	List my_list = new_list();
	int quit = 0;


	while (!quit) {
		int option;
		printf("Select your option:\n ");
		printf("1: Exit \n");
		printf("2: Insert data \n");
		printf("3: Delete data \n");
		printf("4: Print list \n");
		scanf_s("%d", &option);

		switch (option) {
		case 1:
			quit = 1;
			break;
		case 2:
			option_insert(&my_list);
			break;
		case 3:
			option_delete(&my_list);
			break;
		case 4:
			option_print(&my_list);
			break;
		default:
			printf("Invalid choice, PLease enter a number between 0 and 3.\n");
			break;
		}	
		
	}


}