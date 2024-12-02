#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct _contacts Contacts;
typedef struct _doubly_node DoublyNode, Node;
typedef struct _doubly_linked_list DoublyLinkedList, List;

Contacts *contactCreate(const char *name, const char *email, const char *telephone, const char *cpf);
Node *nodeCreate(Contacts *contact);

List *listCreate();
void destroyContact(Contacts *contact);
void destroyList(List **L_ref);
int listIsEmpty(const List *L);
int listPos(List *L, char *cpf);
void listInsert(List *L, Contacts *contact);
void listGet(List *L, int index);
void listPrint(const List *L);
void listRemove(List *L, Contacts *contact);

size_t listSize(List *L);

void listTable(const List *L);

#endif