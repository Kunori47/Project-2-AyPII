#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Estructura de nodo doblemente enlazado
struct Node {
    int data;
    struct Node *ptr;  // Puntero XOR
};

// Función para obtener el XOR de dos direcciones
struct Node* XOR (struct Node* prev, struct Node* next) {
    return (struct Node*) ((intptr_t) (prev) ^ (intptr_t) (next));
}

struct Node* Inicializar(struct Node* list){

    list = malloc(sizeof(struct Node));
    if (list == NULL) {
        perror("Error al reservar memoria para el nodo de la cabeza de la lista");
        exit(EXIT_FAILURE);
    }

    list->data = 0;
    list->ptr = XOR(NULL, NULL);

    return list;

}

int is_empty(struct Node *list){
    return list == NULL;
}

void insertaralprincipio(struct Node** list, int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Error al reservar memoria para el nuevo nodo");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->ptr = XOR(NULL, *list);

    if (*list != NULL) {
        (*list)->ptr = XOR(newNode, (*list)->ptr);
    }

    *list = newNode;
}

void insertaralfinal(struct Node** list, int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Error al reservar memoria para el nuevo nodo");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->ptr = XOR(NULL, NULL);

    if (*list == NULL) {
        *list = newNode;
        return;
    }

    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    while (act != NULL) {
        next = XOR(prev, act->ptr);
        prev = act;
        act = next;
    }

    prev->ptr = XOR(newNode, prev->ptr);
    newNode->ptr = XOR(prev, NULL);

}
void insertarordenado(struct Node** list, int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Error al reservar memoria para el nuevo nodo");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->ptr = XOR(NULL, NULL);

    if (*list == NULL) {
        *list = newNode;
        return;
    }

    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    while((act != NULL) && (act->data <= data)) {
        next = XOR(prev, act->ptr);
        prev = act;
        act = next;
    }

    if(*list == act){

        *list = newNode;

    }
    else
    {
      
        prev->ptr = XOR(newNode, prev->ptr);   

    }
    newNode->ptr = XOR(prev, act);
    if (act != NULL) {
        act->ptr = XOR(newNode, act->ptr);
    }

}

int buscarelemento(struct Node* list, int value) {
    struct Node* act = list;
    struct Node* prev = NULL;
    struct Node* next;

    while (act != NULL) {
        if (act->data == value) {
            // El valor se ha encontrado en la lista
            return 1;
        }

        next = XOR(prev, act->ptr);
        prev = act;
        act = next;
    }

    // El valor no se ha encontrado en la lista
    return 0;
}

int sacarprincipio(struct Node** list) {


    if (*list == NULL) {
        // La lista está vacía
        return -1;
    }

    // Store the node to be deleted
    struct Node* aux_delete = *list;

    // Update the head pointer
    *list = XOR(NULL, aux_delete->ptr);

    // When the linked list
    // contains only one node
    if (*list != NULL) {

        // Update head node address
        (*list)->ptr = XOR(NULL, XOR(aux_delete,(*list)->ptr));

    }

    printf("El primer elemento con numero: %d ha sido eliminado",aux_delete->data);
    free(aux_delete);

    return 0;
    
}

int sacarfinal(struct Node** list) {
    if (*list == NULL) {
        // La lista está vacía
        return -1;
    }

    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    // Traverse XOR linked list
    while (XOR(act->ptr, prev) != NULL){

    // Forward traversal
        next = XOR(prev, act->ptr);

    // Update prev
        prev = act;

    // Update act
        act = next;
    }

    // If the Linked List contains more than 1 node
    
    if (prev != NULL)
        prev->ptr = XOR(XOR(prev->ptr, act), NULL);

    // Otherwise
    else
        *list = NULL;

     printf("El ultimo elemento con numero: %d ha sido eliminado",act->data);
    // Delete the last node from memory
    free(act);
    
   
    // Devolver el elemento eliminado
    return 0;
}

int sacarprimeraocurrencia(struct Node** list, int data) {
    if (*list == NULL) {
        // La lista está vacía
        return -1;
    }

    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    // Recorrer la lista hasta encontrar el elemento
    while (act != NULL && act->data != data) {
        // Obtener el nodo siguiente:
        // XOR de NULL y el nodo anterior
        next = XOR(prev, act->ptr);

        // Actualizar los punteros prev y act
        prev = act;
        
        act = next;
    }

    if (act == NULL) {
        // El elemento no se encuentra en la lista
        return -1;
    }

    if (prev == NULL) {
    
        *list = XOR(NULL, act->ptr);
        (*list)->ptr = XOR(NULL, XOR(act,(*list)->ptr));
        free(act);

    }
    else {
    
        
        
        prev->ptr = XOR(prev, act->ptr);
        prev->ptr->ptr = XOR(XOR(prev,act->ptr),act->ptr);
        free(act);

    }



    return 0;
}


// Función para imprimir la lista doblemente enlazada
void printList (struct Node** list) {
    
    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    while (act != NULL) {
        // Imprimir el valor del nodo actual
        printf("%d ->", act->data);

        // Obtener el nodo siguiente:
        // XOR de NULL y el nodo anterior
        next = XOR(prev, act->ptr);

        // Actualizar los punteros prev y act
        prev = act;
        act = next;
    }
}

// Function to reverse the XOR linked list
struct Node* reverseList(struct Node** list)
{
    struct Node* act = *list;
    struct Node* prev = NULL;
    struct Node* next;

    while (XOR(prev, act->ptr) != NULL) {

          
        next = XOR(prev, act->ptr);

          
        prev = act;

            
        act = next;
    }

    *list = act;
    return *list;
}

int cantidadElementos(struct Node* list) {
    
    struct Node* act = list;
    struct Node* prev = NULL;
    struct Node* next;
    int cant = 0;

    while (act != NULL) {
        // Obtener el nodo siguiente:
        // XOR de NULL y el nodo anterior
        next = XOR(prev, act->ptr);

        // Actualizar los punteros prev y act
        prev = act;
        act = next;
        cant++;
    }
    return cant;
}


int main() {
    
    
    struct Node* list = NULL;
    int option, value, reverse = 0;
    
    do
    {
        printf("\t.:MENU:.\n");
        printf("1. Inicializar lista\n");
        printf("2. Si la lista esta vacia\n");
        printf("3. Insertar al principio\n");
        printf("4. Insertar al final\n");
        printf("5. Insertar Ordenado\n");
        printf("6. Buscar elemento\n");
        printf("7. Sacar principio\n");
        printf("8. Sacar final\n");
        printf("9. Sacar primera ocurrencia\n");
        printf("10. Listar de inicio a fin\n");
        printf("11. Listar de fin a inicio\n");
        printf("12. Cantidad de elementos en lista\n");
        printf("13. Salir\n");
        scanf("%d", &option);

        switch(option)
        {
        case 1:
        Inicializar(list);
        printf("La lista ha sido inicializada correctamente!\n");
        printf("\n");
        break;

        case 2:
        if(is_empty(list)){

            printf("La lista esta vacia\n");

        } else {

            printf("La lista no esta vacia\n");
        }
        printf("\n");
        break;

        case 3:
        printf("Introduzca un valor: ");
        scanf("%d", &value);
        insertaralprincipio(&list, value);
        printf("Elemento Insertado al inicio correctamente");
        printf("\n");
        break;

        case 4:
        printf("Introduzca un valor: ");
        scanf("%d", &value);
        insertaralfinal(&list, value);
        printf("Elemento Insertado al final correctamente\n");
        printf("\n");
        break;

        case 5:
        printf("Introduzca un valor: ");
        scanf("%d", &value);
        insertarordenado(&list, value);
        printf("Elemento insertado de forma ordenada correctamente\n");
        printf("\n");
        break;

        case 6:
        printf("Introduzca un valor para buscarlo en la lista: ");
        scanf("%d", &value);
        if(buscarelemento(list, value)){
            
            printf("El valor %d se ha encontrado en la lista.\n", value);
        
        } else {
        
            printf("El valor %d no se ha encontrado en la lista.\n", value);
        }
        
        printf("\n");
        break;

        case 7:
        printf("Sacando el primer elemento de la lista...\n");
        sacarprincipio(&list);
        printf("\n");
        break;

        case 8:
        printf("Sacando el ultimo elemento de la lista...\n");
        sacarfinal(&list);
        printf("\n");
        break;

        case 9:
        printf("Introduzca un elemento que desea eliminar: ");
        scanf("%d",&value);
        printf("Buscando y eliminando elemento...\n");
        sacarprimeraocurrencia(&list,value);
        break;

        case 10:
        printf("\n");
        if (reverse == 0) {
            printList(&list);
        }
        else {
        
            reverseList(&list);
            printList(&list);
            reverse = 0;
        }
        printf("\n");

        break;
        

        case 11:
        printf("\n");
        if (reverse == 0) {

            reverseList(&list);
            printList(&list);
            reverse = 1;
        
        }
        else {
        
            printList(&list);
        }
        printf("\n");
        break;


        case 12:
        printf("\n");
        printf("La cantidad de elementos de la lista es de: %d",cantidadElementos(list));
        printf("\n");
        break;

        }
    
        
    } while (option !=13);

    return 0;
    
}