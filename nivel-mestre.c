#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ============================
// ESTRUTURA PRINCIPAL
// ============================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ============================
// FUNÇÃO AUXILIAR DE TROCA
// ============================
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ============================
// FUNÇÃO PARA EXIBIR OS COMPONENTES
// ============================
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("----------------------------\n");
}

// ============================
// BUBBLE SORT – ordena por NOME
// ============================
int bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0)
                trocar(&v[j], &v[j + 1]);
        }
    }
    return comparacoes;
}

// ============================
// INSERTION SORT – ordena por TIPO
// ============================
int insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            v[j + 1] = v[j];
            j--;
            comparacoes++;
        }
        v[j + 1] = chave;
    }
    return comparacoes;
}

// ============================
// SELECTION SORT – ordena por PRIORIDADE
// ============================
int selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        trocar(&v[i], &v[min]);
    }
    return comparacoes;
}

// ============================
// BUSCA BINÁRIA POR NOME
// ============================
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int inicio = 0, fim = n - 1, comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) {
            printf("\n✅ Componente '%s' encontrado na posição %d!\n", chave, meio);
            printf("Comparações realizadas: %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n❌ Componente '%s' não encontrado.\n", chave);
    printf("Comparações realizadas: %d\n", comparacoes);
    return -1;
}

// ============================
// FUNÇÃO PARA MEDIR TEMPO DE EXECUÇÃO
// ============================
double medirTempo(int (*algoritmo)(Componente[], int), Componente v[], int n, int *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = algoritmo(v, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ============================
// FUNÇÃO PRINCIPAL
// ============================
int main() {
    Componente componentes[MAX];
    int n = 0, opcao;
    char chave[30];

    printf("=== TORRE DE RESGATE – MISSÃO FINAL ===\n");

    // CADASTRO DOS COMPONENTES
    printf("\nQuantos componentes deseja cadastrar (máx. %d)? ", MAX);
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n=== MENU DE ESTRATÉGIAS ===\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente por Nome (Busca Binária)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        int comparacoes;
        double tempo;

        switch (opcao) {
            case 1:
                tempo = medirTempo(bubbleSortNome, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por NOME.\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 2:
                tempo = medirTempo(insertionSortTipo, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por TIPO.\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 3:
                tempo = medirTempo(selectionSortPrioridade, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por PRIORIDADE.\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 4:
                printf("\nDigite o nome do componente a buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                buscaBinariaPorNome(componentes, n, chave);
                break;

            case 0:
                printf("\nEncerrando a missão... 🛰️\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
