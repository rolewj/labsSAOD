#include "stdio.h"
#include "stdlib.h"

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;   
} node;

node* createNode( int value, node *parent){
	node* temp = (node*)malloc(sizeof(node));
	temp->left = temp->right = NULL;
	temp->data = value;
	temp->parent = parent;
	return temp;
}

void insert(node **head, int value){
	node *temp = NULL;
	if (*head == NULL){
		*head = createNode(value, NULL);
		return;
	}
	temp = *head;
	while(temp){
		if(value > temp->data){
			if (temp->right){
				temp = temp->right;
				continue;
			}
			else{
				temp->right = createNode(value, temp);
				return;
			}    
		}
		else if(value < temp->data){
			if(temp->left){
				temp = temp->left;
				continue;
			}
			else{
				temp->left = createNode(value, temp);
				return;
			}
		}
		else{
			return;
		}
	}
}

node* getNode(node* root, int value){
	while(root){
		if(root->data > value){
			root = root->left;
			continue;
		}
		else if(root->data < value){
			root = root->right;
			continue;
		}
		else
			return root;
		}
		return NULL;
}

node* getMax(node* root){
	while (root->right) {
		root = root->right;
	}
	return root;
}

node* getMin(node* root){
	while (root->left){
		root = root->left;
	}
	return root;
}

int main(int argc, char** argv){
	node* root = NULL;
	int value;
	printf("Enter values for the tree: ");
	while(1){
		scanf("%d", &value);
		if (value == 0){
      break;
    }
		insert(&root, value);
	}
  printf("Max number = %d\n", getMax(root)->data);
  printf("Min number = %d\n", getMin(root)->data);
  printf("Enter a value: ");
	while(1){
		scanf("%d", &value);
		if (value == 0){
      break;
    }
		if (getNode(root, value) == NULL){
			printf("Wrong number!\n");
			continue;  
		} 
		printf("The parent of the number %d is %d\n", value, getNode(root, value)->parent->data);
	}
}
