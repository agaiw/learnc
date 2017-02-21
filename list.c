#include <stdio.h>
#include <stdlib.h>

typedef struct element {

  int value;
  struct element* next_p;

} element_t;

void list_init(element_t** list);

void list_add(element_t** list, int value);

void list_print(element_t* list);

void main() {

  element_t* lista;
  list_init(&lista);
  list_add(&lista, 10);
  list_add(&lista, 20);
  list_add(&lista, 30);
  list_print(lista);

}

void list_init(element_t** list) {

  *list = NULL;

}

void list_add(element_t** list, int value) {

  element_t* current = *list;

  if ((*list)== NULL) {

     (*list) = malloc(sizeof(element_t));
     (*list)->value = value;
     (*list)->next_p = NULL;
     return;
  }

  while(1) {

    if (current->next_p == NULL) {

      element_t* new = malloc(sizeof(element_t));
      new->value = value;
      new->next_p = NULL;
      current->next_p = new;
      return;
    }    

    current = current->next_p;

  }
}

void list_print(element_t* list) {

  element_t* current = list;

  while (current != NULL) {

    printf("%d ", current->value);
    current = current->next_p;

  };

    printf("\n");
}
