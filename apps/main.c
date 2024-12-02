#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void limparBuffer();
void exibirElemento(List *L);
void trocarTela(List *L, int o);
void exibirMenu();
void removerContato(List *L);
void run(List *L);
void adicioarContato(List *L);
void exibirTudo(List *L);

int option = 0;

int main(void) {
    List *L = listCreate();
    while (option != 5) {
        run(L);
        option = 0;
    }
}

void run(List *L) {
    trocarTela(L, option);
}

void trocarTela(List *L, int o) {
    switch (o)
    {
    case 1:
        exibirElemento(L);
        break;
    case 2:
        adicioarContato(L);
        break;
    case 3:
        removerContato(L);
        break;
    case 4:
        exibirTudo(L);
        break;
    case 5:
        exit(EXIT_SUCCESS);
        break;
    default:
        exibirMenu();

        printf("Digite a opção desejada: ");
        scanf("%d", &option);

        system("clear || cls"); 

        trocarTela(L, option);
        break;
    }
}

void exibirMenu() {
    puts("---------- MENU ----------");
    puts("1 - Exibir contato");
    puts("2 - Adicionar contato");
    puts("3 - Retirar contato");
    puts("4 - Exibir todos os contatos");
    puts("5 - Sair\n");
}

void exibirElemento(List *L) {
    if (listIsEmpty(L)) {
        puts("Lista está vazia\n");
        return;
    } else {
        int i = 0;
        printf("Informe o índice do contato que deseja ver: ");
        scanf("%d", &i);
        listGet(L, i);
    }
}

void removerContato(List *L) {
    if (listIsEmpty(L)) {
        puts("Lista está vazia\n");
        return;
    } else {
        int i = 0;
        printf("Informe o índice do contato que deseja remover: ");
        scanf("%d", &i);
        listRemove(L, i);
    }
}

void exibirTudo(List *L) {
    if (listIsEmpty(L)) {
        puts("Lista está vazia\n");
        return;
    } else listTable(L);
}

void adicioarContato(List *L) {
    char *name = NULL, *email = NULL, *telephone = NULL, *cpf = NULL;
    size_t buffer_size = 0;
    
    // Solicita o nome
    printf("Informe o nome do contato: ");
    limparBuffer(); // Garante que o buffer esteja limpo antes de capturar entrada
    getline(&name, &buffer_size, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove o caractere de nova linha

    // Solicita o e-mail
    printf("Informe o e-mail do contato: ");
    buffer_size = 0; // Redefine buffer para a próxima captura
    getline(&email, &buffer_size, stdin);
    email[strcspn(email, "\n")] = '\0';

    // Solicita o telefone
    printf("Informe o telefone do contato: ");
    buffer_size = 0;
    getline(&telephone, &buffer_size, stdin);
    telephone[strcspn(telephone, "\n")] = '\0';

    // Solicita o CPF
    printf("Informe o CPF do contato: ");
    buffer_size = 0;
    getline(&cpf, &buffer_size, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    Contacts *contato = contactCreate(name, email, telephone, cpf);
    listInsert(L, contato);

    puts("Contato adicionado com sucesso!\n");

    free(name);
    free(email);
    free(telephone);
    free(cpf);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Descarta caracteres até o final da linha
}