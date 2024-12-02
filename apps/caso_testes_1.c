#include "list.h"

#include <stdio.h>

int main(void)
{
    // Criação da Lista;
    List *L = listCreate();

    // Criando os contatos;
    Contacts *c1 = contactCreate("Alice", "alice@example.com", "123456789", "999.999.999-99");
    Contacts *c2 = contactCreate("Bob", "bob@example.com", "987654321", "555.555.555-55");
    Contacts *c3 = contactCreate("Charlie", "charlie@example.com", "456123789", "666.666.666-66");
    Contacts *c4 = contactCreate("Dave", "dave@example.com", "741852963", "333.333.333-33");
    Contacts *c5 = contactCreate("Eve", "eve@example.com", "852963741", "888.888.888-88");
    Contacts *c6 = contactCreate("Carlos", "carlos@gmail.com", "326547898", "222333666625");

    listInsert(L, c1); // Final, lista vaiza inicialmente.
    listInsert(L, c2); // Final
    listInsert(L, c3); // Meio
    listInsert(L, c4); // Começo
    listInsert(L, c5); // Entre começo e meio
    listInsert(L, c6);
    // Imprimindo a lista
    puts("Lista mostrando os ponteiros:");
    listPrint(L);

    puts("Tabela da lista mostrando os valores:");
    listTable(L);

    puts("");
    listGet(L, 2);

    destroyList(&L);
    return 0;
}