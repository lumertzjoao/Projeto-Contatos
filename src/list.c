#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct _contacts 
{
    char *name;
    char *email;
    char *telephone;
    char *cpf;
} Contacts;

typedef struct _doubly_node 
{
    Contacts *contact;
    struct _doubly_node *prev;
    struct _doubly_node *next;
} DoublyNode, Node;

typedef struct _doubly_linked_list
{
    Node *begin;
    Node *end;
    size_t size;
} DoublyLinkedList, List;

Contacts *contactCreate(const char *name, const char *email, const char *telephone, const char *cpf) {
    Contacts *contact = (Contacts*) malloc(sizeof(Contacts));

    if (!contact) {
        fprintf(stderr, "Erro ao alocar memória para o contato.\n");
        exit(EXIT_FAILURE);
    }

    // Alocar e copiar strings
    contact -> name = _strdup(name);
    contact -> email = _strdup(email);
    contact -> telephone = _strdup(telephone);
    contact -> cpf = _strdup(cpf);

    return contact;
}

Node *nodeCreate(Contacts *contact) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Erro ao alocar memória para o nó.\n");
        exit(EXIT_FAILURE);
    }

    // Associar o contato (sem copiar, usando o mesmo ponteiro);
    node -> contact = contact;
    node -> prev = NULL;
    node -> next = NULL;

    return node;
}

List *listCreate() {
    List *list = (List*) malloc (sizeof(List));

    if (!list) {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        exit(EXIT_FAILURE);
    }

    list -> begin = NULL;
    list -> end = NULL;
    list -> size = 0;

    return list;
}

void destroyContact(Contacts *contact) {
    if (contact) {
        free(contact -> name);
        free(contact -> email);
        free(contact -> telephone);
        free(contact -> cpf);
        free(contact);
    }
}

void destroyList(List **L_ref) {
    List *L = *L_ref;
    Node *p = L -> begin;

    while (p != NULL) {
        Node *aux = p;
        p = p -> next;
        destroyContact(aux -> contact);
        free(aux);
    }

    free(L);
    *L_ref = NULL;
}

int listIsEmpty(const List *L) {
    return L -> size == 0;
}

int listPos(List *L, char *cpf) {
    Node *p = L -> begin;
    int position = 0;

    while (p != NULL) {
        int cmp = strcmp(cpf, p -> contact -> cpf);

        if (cmp > 0) {
            return position;
        }

        p = p -> next;
        position++;
    }

    return position;
}

void listInsert(List *L, Contacts *contact) {
    Node *p = nodeCreate(contact);

    if (listIsEmpty(L)) {
        L -> begin = L -> end = p;
        p -> prev = p -> next = NULL;
    } else {
        int pos = listPos(L, contact -> cpf);
        Node *current = L -> begin;
        int i = 0;

        while (current != NULL && i < pos) {
            current = current -> next;
            i++;
        }

        if (current == L -> begin) {
            p -> next = L -> begin;
            p -> prev = NULL;
            L -> begin -> prev = p;
            L -> begin = p;
        }
        else if (current == NULL) {
            p -> prev = L -> end;
            p -> next = NULL;
            L -> end -> next = p;
            L -> end = p;
        }
        else {
            p -> prev = current -> prev;
            p -> next = current;
            current -> prev -> next = p;
            current -> prev = p;
        }
    }

    L -> size++;
}

void listGet(List *L, int index) {
    if (listIsEmpty(L)) {
        fprintf(stderr, "ERRO no método 'listGet'\n");
        fprintf(stderr, "Lista está vazia\n");
    } else if (index < 0 || index >= L -> size) {
        fprintf(stderr, "ERRO no método 'listGet'\n");
        fprintf(stderr, "Index '%d' inválido\n", index);
        fprintf(stderr, "Tente um índex entre [0, %d]\n", L -> size - 1);
    } else {
        Node *p = L -> begin;
        
        for (int i = 0; i != index; i++) p = p -> next;

        puts("Contato:");
        printf("Nome: %s\n", p -> contact -> name);
        printf("Email: %s\n", p -> contact -> email);
        printf("Telefone: %s\n", p -> contact -> telephone);
        printf("CPF: %s\n", p -> contact -> cpf);
        puts("");
        
        printf("Proximo contato: ");
        if (p -> next == NULL) printf("NULL\n"); 
        else printf("%s\n", p -> next -> contact -> name);

        printf("Contato anterior: ");
        if (p -> prev == NULL) printf("NULL\n");
        else printf("%s\n", p -> prev -> contact -> name);
    }
}

void listPrint(const List *L) {
    Node *p = L -> begin;

    printf("L -> ");

    while (p != NULL)
    {
        printf("%s -> ", p -> contact -> cpf);
        p = p -> next;
    }
    printf("NULL\n");

    if (L -> end == NULL) printf("L -> end = NULL");
    else printf("L -> end = %s\n", L -> end -> contact -> cpf);

    printf("Size: %u\n", L -> size);
    puts("");
}

void listRemove(List *L, int index) {

    if (listIsEmpty(L)) {
        fprintf(stderr, "ERRO no método 'listRemove'\n");
        fprintf(stderr, "Lista está vazia\n");
    }

    if (index < 0 || index >= L->size) {
        fprintf(stderr, "ERRO no método 'listRemove'\n");
        fprintf(stderr, "Index '%d' inválido\n", index);
        fprintf(stderr, "Tente um índex entre [0, %d]\n", L -> size - 1);
    }

    Node *current = L->begin;
    int i = 0;

    // Localizar o nó na posição fornecida
    while (i < index) {
        current = current->next;
        i++;
    }

    // Atualizar os ponteiros para remover o nó
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        L->begin = current->next; // Atualizar o início da lista se for o primeiro nó
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        L->end = current->prev; // Atualizar o final da lista se for o último nó
    }

    // Liberar memória do nó removido
    destroyContact(current->contact);
    free(current);

    L->size--;
    printf("Elemento removido com sucesso.\n");
}
 
size_t listSize(List *L) {
    return L -> size;
}

void listTable(const List *L) {
    Node *p = L -> begin;
    printf("Nome\t\tEmail\t\t\tTelefone\tCPF\n");


    while (p != NULL) {
        Contacts *contact = p -> contact;
        printf("%-8s\t%-20s\t%s\t%s\n", 
            contact->name,
            contact->email,
            contact->telephone,
            contact->cpf
        );
        p = p -> next;
    }
}