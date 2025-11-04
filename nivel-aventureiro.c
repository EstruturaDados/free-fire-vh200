#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// =======================
// STRUCTS
// =======================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// =======================
// PROTÓTIPOS (VETOR)
// =======================
void inserirItemVetor(Item mochila[], int *numItens);
void removerItemVetor(Item mochila[], int *numItens);
void listarItensVetor(Item mochila[], int numItens);
void buscarSequencialVetor(Item mochila[], int numItens);
void ordenarVetor(Item mochila[], int numItens);
void buscarBinariaVetor(Item mochila[], int numItens);

// =======================
// PROTÓTIPOS (LISTA)
// =======================
void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
void buscarSequencialLista(No *inicio);

// =======================
// MENU PRINCIPAL
// =======================
int main() {
    int opcaoPrincipal;

    do {
        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("1. Usar mochila com VETOR\n");
        printf("2. Usar mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoPrincipal);
        getchar();

        switch (opcaoPrincipal) {
            case 1: {
                Item mochila[MAX_ITENS];
                int numItens = 0;
                int opcao;

                do {
                    printf("\n--- MOCHILA (VETOR) ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Buscar item (sequencial)\n");
                    printf("5. Ordenar itens\n");
                    printf("6. Buscar item (binaria)\n");
                    printf("0. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &opcao);
                    getchar();

                    switch (opcao) {
                        case 1: inserirItemVetor(mochila, &numItens); break;
                        case 2: removerItemVetor(mochila, &numItens); break;
                        case 3: listarItensVetor(mochila, numItens); break;
                        case 4: buscarSequencialVetor(mochila, numItens); break;
                        case 5: ordenarVetor(mochila, numItens); break;
                        case 6: buscarBinariaVetor(mochila, numItens); break;
                    }
                } while (opcao != 0);
                break;
            }

            case 2: {
                No *inicio = NULL;
                int opcao;

                do {
                    printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
                    printf("1. Inserir item\n");
                    printf("2. Remover item\n");
                    printf("3. Listar itens\n");
                    printf("4. Buscar item (sequencial)\n");
                    printf("0. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &opcao);
                    getchar();

                    switch (opcao) {
                        case 1: inserirItemLista(&inicio); break;
                        case 2: removerItemLista(&inicio); break;
                        case 3: listarItensLista(inicio); break;
                        case 4: buscarSequencialLista(inicio); break;
                    }
                } while (opcao != 0);
                break;
            }

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}

// =======================
// FUNÇÕES - VETOR
// =======================
void inserirItemVetor(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*numItens] = novo;
    (*numItens)++;
    printf("Item adicionado!\n");
}

void removerItemVetor(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarItensVetor(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. %s | %s | Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarSequencialVetor(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    int comparacoes = 0;
    printf("Nome do item a buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado (%d comparacoes): %s | %s | Qtd: %d\n",
                   comparacoes, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado (%d comparacoes)\n", comparacoes);
}

void ordenarVetor(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome!\n");
}

void buscarBinariaVetor(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item a buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int inicio = 0, fim = numItens - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado (%d comparacoes): %s | %s | Qtd: %d\n",
                   comparacoes, mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    printf("Item nao encontrado (%d comparacoes)\n", comparacoes);
}

// =======================
// FUNÇÕES - LISTA ENCADEADA
// =======================
void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    No *atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s | %s | Qtd: %d\n", i++, atual->dados.nome,
               atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nome[30];
    int comparacoes = 0;
    printf("Nome do item a buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = inicio;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado (%d comparacoes): %s | %s | Qtd: %d\n",
                   comparacoes, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item nao encontrado (%d comparacoes)\n", comparacoes);
}
