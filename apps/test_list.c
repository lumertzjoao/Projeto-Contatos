#include "list.h"

#include <stdio.h>

int main() {
    // Criação da lista
    List *contactList = listCreate();

    // Criação de alguns contatos
    Contacts *contact1 = contactCreate("Carlos Silva", "carlos.silva@email.com", "1234-5678", "123.456.789-00");
    Contacts *contact2 = contactCreate("Ana Souza", "ana.souza@email.com", "9876-5432", "234.567.890-00");
    Contacts *contact3 = contactCreate("Joao Pereira", "joao.pereira@email.com", "1122-3344", "345.678.901-00");

    // Inserindo os contatos na lista
    listInsert(contactList, contact1);
    listInsert(contactList, contact2);
    listInsert(contactList, contact3);

    // Imprimindo a lista antes da remoção
    printf("Lista de contatos antes da remocao:\n");
    listPrint(contactList);

    // Removendo um contato (vamos usar o CPF para identificar e remover)
    listRemove(contactList, contact2);

    // Imprimindo a lista após a remoção
    printf("\nLista de contatos após a remoção:\n");
    listPrint(contactList);

    // Limpando a memória
    destroyList(&contactList);

    return 0;
}