#include <stdio.h>
#include <stdlib.h>

struct no {
    int info;
    struct no *prox;
};

// Cria um novo nó com o valor informado
struct no* criar_novo_no(int valor) {
    struct no* novo = (struct no*)malloc(sizeof(struct no));
    novo->info = valor;
    novo->prox = NULL;
    return novo;
}

// Adiciona nó no final da lista
void adicionar_no(struct no** lista, int valor) {
    struct no* novo = criar_novo_no(valor);
    if (*lista == NULL) {
        *lista = novo;
    } else {
        struct no* atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Encontra elementos repetidos entre duas listas
struct no* encontrar_repetidos(struct no* lista1, struct no* lista2) {
    struct no* repetidos = NULL;
    struct no *aux1 = lista1, *aux2;

    while (aux1 != NULL) {
        aux2 = lista2;
        while (aux2 != NULL) {
            if (aux1->info == aux2->info) {
                // Verifica se já foi adicionado
                struct no* temp = repetidos;
                int ja_existe = 0;
                while (temp != NULL) {
                    if (temp->info == aux1->info) {
                        ja_existe = 1;
                        break;
                    }
                    temp = temp->prox;
                }
                if (!ja_existe) {
                    adicionar_no(&repetidos, aux1->info);
                }
            }
            aux2 = aux2->prox;
        }
        aux1 = aux1->prox;
    }
    return repetidos;
}

// Imprime a lista
void imprimir_lista(struct no* lista) {
    while (lista != NULL) {
        printf("%d -> ", lista->info);
        lista = lista->prox;
    }
    printf("NULL\n");
}

int main() {
    struct no *lista1 = NULL, *lista2 = NULL;
    int n1, n2, valor, i;

    // Entrada da Lista 1
    printf("Quantos valores deseja inserir na Lista 1? ");
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        printf("Digite o valor %d da Lista 1: ", i + 1);
        scanf("%d", &valor);
        adicionar_no(&lista1, valor);
    }

    // Entrada da Lista 2
    printf("\nQuantos valores deseja inserir na Lista 2? ");
    scanf("%d", &n2);
    for (i = 0; i < n2; i++) {
        printf("Digite o valor %d da Lista 2: ", i + 1);
        scanf("%d", &valor);
        adicionar_no(&lista2, valor);
    }

    // Exibe as listas
    printf("\nLista 1: ");
    imprimir_lista(lista1);

    printf("Lista 2: ");
    imprimir_lista(lista2);

    // Encontra e exibe os repetidos
    struct no* repetidos = encontrar_repetidos(lista1, lista2);

    printf("Elementos repetidos: ");
    imprimir_lista(repetidos);

    return 0;
}
