#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k, l;
    int seen[10];

    for (i = 0; i < 9; i++) 
    {
        for (k = 0; k < 10; k++) seen[k] = 0;
        for (j = 0; j < 9; j++) 
        {
            int val = n->sudo[i][j];
            if (val != 0) {
                if (seen[val]) return 0;
                seen[val] = 1;
            }
        }
    }

    for (j = 0; j < 9; j++) {
        for (k = 0; k < 10; k++) seen[k] = 0;
        for (i = 0; i < 9; i++) {
            int val = n->sudo[i][j];
            if (val != 0) {
                if (seen[val]) return 0;
                seen[val] = 1;
            }
        }
    }

    for (i = 0; i < 9; i += 3) 
    {
        for (j = 0; j < 9; j += 3) 
        {
            for (k = 0; k < 10; k++) seen[k] = 0;
            for (k = 0; k < 3; k++) 
            {
                for (l = 0; l < 3; l++) 
                {
                    int val = n->sudo[i + k][j + l];
                    if (val != 0) 
                    {
                        if (seen[val]) return 0;
                        seen[val] = 1;
                    }
                }
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
  List* list = createList();
  int i, j;

  for (i = 0; i < 9; i++) 
  {
      for (j = 0; j < 9; j++) 
      {
          if (n->sudo[i][j] == 0) 
          {
              for (int k = 1; k <= 9; k++) 
              {
                  Node* new = copy(n);
                    new->sudo[i][j] = k;
                    if (is_valid(new)) pushBack(list, new);
        
                    else free(new);
                    
              }
                return list;
                
          }
      }
  }

    return list;
}


int is_final(Node* n){
  int i, j;
  for (i = 0; i < 9; i++) 
  {
      for (j = 0; j < 9; j++) 
      {
          if (n->sudo[i][j] == 0) return 0;
      }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){

    Stack* stack = createStack();
    push(stack, initial);

    while (!is_empty(stack)) 
    {
        Node* current = top(stack);
        pop(stack);
        (*cont)++;

        if (is_final(current)) return current;

        List* adj = get_adj_nodes(current);
        void* ptr = first(adj);
        while (ptr) 
        {
            Node* child = (Node*) ptr;

            if (is_valid(child)) push(stack, child);
            else free(child);  
            ptr = next(adj);
        }

        clean(adj);
        free(adj);
    }
        

    return NULL;
}






/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/