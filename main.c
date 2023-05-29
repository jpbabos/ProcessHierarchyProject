#include <stdio.h>
#include <stdlib.h>


/*constants and structures*/
/******************************************************************************************/
#define MAX_PROCESSES 100

struct node1{
    int id;
    struct node1* link;
};

typedef struct node1 linked_list_type;

struct node2{
    int parent;
    linked_list_type* children;
};

typedef struct node2 pcb_type;

pcb_type* pcb_array[MAX_PROCESSES];
/******************************************************************************************/


/*Procedure to print hierarchy process*/
/******************************************************************************************/
void display_process(){
    linked_list_type* current_child;

    for(int i = 0; i < MAX_PROCESSES; i++){ //goes through each process and prints its attributes, and if the process has children, it goes down that line as well
        if(pcb_array[i] != NULL){
            printf("Process id: %d\n", i);
            printf("\tParent process: %d\n", pcb_array[i]->parent);
            current_child = pcb_array[i]->children;
            while(current_child != NULL){
                printf("\tChild process: %d\n", current_child->id);
                current_child = current_child->link;
            }
        }
    }
}
/******************************************************************************************/


/*Option one*/
/******************************************************************************************/
void initialize_process(){
    int i;
    pcb_array[0] = (pcb_type *) malloc(sizeof (pcb_type)); //allocate memory for pcb a [0]
    pcb_array[0]->parent = 0;
    pcb_array[0]->children = NULL;
    for (i = 1; i < MAX_PROCESSES; i++){ //sets all other pcbs to null
        pcb_array[i] = NULL;
    }
    display_process();
}
/******************************************************************************************/

/*Option two*/
/******************************************************************************************/
void create_new_child(){
    int p, q = 1;
    linked_list_type* new_child_node;
    linked_list_type* current_child;

    printf("Enter parent process id:  ");
    scanf("%d", &p);

    if(pcb_array[p] == NULL){
        printf("Process does not exist\n");
        return;
    }

    while((q < MAX_PROCESSES) && (pcb_array[q] != NULL)){
        q++;
    }
    if(q == MAX_PROCESSES){
        printf("No more available PCBs");
    }
    pcb_array[q] = (pcb_type *) malloc(sizeof (pcb_type));
    new_child_node = (linked_list_type *) malloc(sizeof (linked_list_type)); //creates memory for new child
    pcb_array[q]->parent = p; //records the parent's index at p in pcb[q]
    pcb_array[q]->children = NULL;

    new_child_node->id = q;
    new_child_node->link = NULL;

    if(pcb_array[p]->children == NULL){ //if the parent does not have any other children
        pcb_array[p]->children = new_child_node;
        display_process();
        return;
    }

    current_child = pcb_array[p]->children; //finds the last child and creates a link from that to the new child
    while(current_child->link != NULL){
        current_child = current_child->link;
    }
    current_child->link = new_child_node;

    display_process();
}
/******************************************************************************************/


/*Recursive procedure to delete children processes*/
/******************************************************************************************/
void destroy_children(linked_list_type* node){
    int q;

    if(node == NULL){
        return;
    }
    destroy_children(node->link); //goes through each child and deletes it and frees up the memory
    q = node->id;
    destroy_children(pcb_array[q]->children);

    free(pcb_array[q]);
    pcb_array[q] = NULL;
    free(node);
    node = NULL;
}
/******************************************************************************************/


/*Option three*/
/******************************************************************************************/
void destroy_children_of_parent_process(){
    int p;

    printf("Enter the parent process whose descendents are to be destroyed:");
    scanf("%d", &p);
    destroy_children(pcb_array[p]->children);
    pcb_array[p]->children = NULL;

    display_process();
}
/******************************************************************************************/


/*Option 4*/
/******************************************************************************************/
void quit(){
    for(int i = 0; i < MAX_PROCESSES; i++){
        if(pcb_array[i] != NULL){
            if(pcb_array[i]->children != NULL){
                destroy_children(pcb_array[i]->children);
            }
        }
    }
}
/******************************************************************************************/


/*Main method*/
/******************************************************************************************/
int main(){
    int choice = 0;

    while(choice != 4){
        printf("*********************************************************\n");
        printf("Welcome to Process Creation Hierarchy!\n\n");
        printf("Please choose one of the options below:\n");
        printf("1. Initialize process hierarchy\n");
        printf("2. Create a new child process\n");
        printf("3. Destroy all descendants of a parent process\n");
        printf("4. Quit\n");
        printf("Selection:");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                initialize_process();
                break;
            case 2:
                create_new_child();
                break;
            case 3:
                destroy_children_of_parent_process();
                break;
        }
    }
    quit();
    printf("Have a great day!");
}
/******************************************************************************************/