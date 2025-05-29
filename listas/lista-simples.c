#include <stdio.h>
#include <stdlib.h>

struct s_no {
    int info;
    struct s_no *prox;
};

int verificar (struct s_no *ptlista, int x) { //para buscar determinado no na lista 
    struct s_no *pont = ptlista;
    while (pont != NULL) {
        if (pont->info == x) {
            return 1;
        }
        pont = pont->prox;
    }
    return 0;
}

void imprimirLista(struct s_no *ptlista) { //para imprimir a lista 
    struct s_no *pont = ptlista;
    while (pont != NULL) {
        printf("%d -> ", pont->info);
        pont = pont->prox;
    }
    printf("NULL\n");
}

void inserirOrdenado(struct s_no **ptlista, int valor) { //para inserir um no na lista (ordenada)
    struct s_no *novo = malloc(sizeof(struct s_no));
    if (novo == NULL) {
        printf("Erro de alocacao\n");
        return;
    }
    novo->info = valor;

    if (*ptlista == NULL || valor < (*ptlista)->info) {
        novo->prox = *ptlista;
        *ptlista = novo;
        return;
    }

    struct s_no *atual = *ptlista;
    while (atual->prox != NULL && atual->prox->info < valor) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

int removerElemento (struct s_no **ptlista, int valor) {
    struct s_no *anterior = NULL; //ponteiro para o no anterior
    struct s_no *atual = *ptlista; //ponteiro para percorrer a lista

    while (atual != NULL) {
        if (atual->info == valor) { //Caso o no a ser removido seja o primeiro da lista
            if (anterior == NULL) {
                *ptlista = atual->prox; //o inicio da lista passa a ser o proximo no
            } else {
                anterior->prox = atual->prox; //pula o no atual
            }
            free(atual); //libera da memoria
            return 1;
        }
        anterior = atual; //avanca para o proximo no
        atual = atual->prox;
    }
    return 0;
}

void liberarLista(struct s_no **ptlista) {
    struct s_no *atual = *ptlista;
    struct s_no *temp;

    while (atual != NULL) {
        temp = atual->prox;
        free(atual);
        atual = temp;
    }

    *ptlista = NULL;
}

int main() {
    struct s_no *ptlista = NULL;
    int opcao, valor;

    do {
        printf("\n-----Menu-----\n");
        printf("1 - Inserir valor na lista\n");
        printf("2- Buscar valor na lista\n");
        printf("3- Remover valor da lista\n");
        printf("4 - Sair\n");
        printf("\n Escolha uma opcao: \n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInforme o valor para inserir: ");
                scanf("%d", &valor);
                inserirOrdenado(&ptlista, valor);
                printf("\nValor inserido.\n");

                printf("Lista atualizada: \n");
                imprimirLista(ptlista);

                break;

            case 2:
                printf("\nQual valor deseja buscar? \n");
                scanf("%d", &valor);
                
                if(verificar(ptlista, valor)) {
                    printf("O valor %d esta na lista.\n", valor);
                } else {
                    printf("O valor %d nao esta na lista.\n", valor);
                }
        
                break;

            case 3:
                printf("\nQual valor deseja remover?\n");
                scanf("%d", &valor);

                if (removerElemento(&ptlista, valor)) {
                    printf("\nO valor %d foi removido\n", valor);
                } else {
                    printf("\nO valor %d nao foi encontrado.\n", valor);
                }

                printf("Lista atualizada: \n");
                imprimirLista(ptlista);

                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    liberarLista(&ptlista);

    return 0;
}
