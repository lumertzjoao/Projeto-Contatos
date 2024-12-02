#include "list.h"

#include <stdio.h>

int main(void) {
    // Criando a lista
    List *L = listCreate();
    
    // Criando os contatos;
    Contacts *contact1 = contactCreate("Carlos Silva", "carlos.silva@email.com", "1234-5678", "123.456.789-00");
    Contacts *contact2 = contactCreate("Ana Souza", "ana.souza@email.com", "9876-5432", "234.567.890-00");
    Contacts *contact3 = contactCreate("Joao Pereira", "joao.pereira@email.com", "1122-3344", "345.678.901-00");

    // Inserindo os contatos na lista;
    listInsert(L, contact3);
    listInsert(L, contact1);
    listInsert(L, contact2);

    
}