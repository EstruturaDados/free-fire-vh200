#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// =======================
// Definição da STRUCT
// =======================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// =======================
// Declaração das FUNÇÕES
// =======================
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila[], int numItens);

// =======================
// Função PRINCIPAL
// =======================
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0; // Quantidade atual de itens na mochila
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTARIO =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// =======================
// FUNÇÃO: Inserir item
// =======================
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n--- Cadastro de Item ---\n");
    printf("Nome: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // remove \n

    printf("Tipo (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[*numItens] = novoItem;
    (*numItens)++;

    printf("\nItem adicionado com sucesso!\n");
}

// =======================
// FUNÇÃO: Remover item
// =======================
void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nA mochila esta vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remocao de Item ---\n");
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < *numItens - 1; i++) {
            mochila[i] = mochila[i + 1]; // desloca os próximos itens
        }
        (*numItens)--;
        printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
    } else {
        printf("\nItem nao encontrado!\n");
    }
}

// =======================
// FUNÇÃO: Listar itens
// =======================
void listarItens(Item mochila[], int numItens) {
    printf("\n--- Itens na Mochila ---\n");
    if (numItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    for (int i = 0; i < numItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// =======================
// FUNÇÃO: Buscar item (busca sequencial)
// =======================
void buscarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca de Item ---\n");
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado na mochila.\n");
}
