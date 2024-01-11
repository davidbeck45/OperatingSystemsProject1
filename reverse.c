#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void insert(char* data);
void FrLL(struct Node* head);

void insert(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL){
        fprintf(stderr,"error: malloc failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

static void reverseTheFile() {
    struct Node* current = head;
    struct Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        head = temp->prev;
    }
}

// void printList() {
//     struct Node* current = head;

//     while (current != NULL) {
//         printf("%s", current->data);
        
//         current = current->next;
//     }
    
// }
void FrLL(struct Node* head){
    struct Node* temp;
    while(head!=NULL){
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);

    }
}

int main(int argc, char* argv[]) {
    
   if( argc < 2 || argc > 3) {
      fprintf( stderr, "usage: reverse <input> <output>\n");
      return 1;
   }

   
   
    
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf( stderr, "error: cannot open file '%s'\n", argv[1]);
        return 1;
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        // if(read == NULL){
        //     return 1;
        // }
        insert(line);
        line = NULL;
    }
    fclose(fp);
    if (line) {
        free(line);
    }
	
    reverseTheFile();
  
    if(argc ==2){
        struct Node* current = head;

        while (current != NULL) {
            printf("%s", current->data);
        
            current = current->next;
    }
        FrLL(current);
    }
    
    if (argc == 3){
        
    int i;
    for (i = 0; argv[1][i] != '\0' && argv[2][i] != '\0'; i++) {
        if (argv[1][i] != argv[2][i]) {
            
            continue;
        }
    }
    if (argv[1][i] == '\0' && argv[2][i] == '\0') {
        fprintf(stderr, "error: input and output file must differ\n");
        return 1;
    } else {
        FILE* outputFile = fopen(argv[2], "w");
    
        if (!outputFile) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        return 1;
        }else{
        struct Node* temp = head;
        while(temp != NULL) {
            fprintf(outputFile, "%s", temp->data);
            temp = temp->next;
        }
        free(temp);
        
        

        fclose(outputFile);
        return 0;
        }
        
        
        
    }

   }
    
    
}