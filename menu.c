//menu

#include <stdio.h>
#include <stdlib.h>

struct s_no {
    int info;
    struct s_no *prox;
    struct s_no *ant;  // usado para a lista dupla
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//funcoes para a lista simplesmente encadeada
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

int verificarSimples (struct s_no *ptlista, int x) { //para buscar determinado no na lista 
    struct s_no *pont = ptlista;
    while (pont != NULL) {
        if (pont->info == x) {
            return 1;
        }
        pont = pont->prox;
    }
    return 0;
}

void imprimirListaSimples(struct s_no *ptlista) { //para imprimir a lista 
    struct s_no *pont = ptlista;
    while (pont != NULL) {
        printf("%d -> ", pont->info);
        pont = pont->prox;
    }
    printf("NULL\n");
}

void inserirOrdenadoSimples(struct s_no **ptlista, int valor) { //para inserir um no na lista (ordenada)
    struct s_no *novo = malloc(sizeof(struct s_no));
    if (novo == NULL) {
        printf("Erro de alocacao\n");
        return;
    }
    novo->info = valor;
    novo->prox = NULL;

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

int removerElementoSimples (struct s_no **ptlista, int valor) {
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

void liberarListaSimples(struct s_no **ptlista) {
    struct s_no *atual = *ptlista;
    struct s_no *temp;

    while (atual != NULL) {
        temp = atual->prox;
        free(atual);
        atual = temp;
    }

    *ptlista = NULL;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuListaSimples (struct s_no **ptlista) {
    int valor;
    int opcao;

    do {
        printf("\n-----LISTA SIMPLESENTE ENCADEADA-----\n");
        printf("1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Buscar\n");
        printf("4- Voltar para o menu principal\n");
        scanf("%d", &opcao);

        switch(opcao) {
    
            case 1:
                printf("\nInforme o valor para inserir: ");  //funcao para inserir um no na lista
                scanf("%d", &valor);
                inserirOrdenadoSimples(ptlista, valor);
                printf("\nValor inserido.\n");

                printf("Lista atualizada: \n");
                imprimirListaSimples(*ptlista);
                break;

            case 2:
                printf("\nQual valor deseja remover?\n");   //funcao para remover um no na lista
                scanf("%d", &valor);

                if (removerElementoSimples(ptlista, valor)) {   //passa o ponteiro da lista 
                    printf("\nO valor %d foi removido\n", valor);
                } else {
                    printf("\nO valor %d nao foi encontrado.\n", valor);
                }

                printf("Lista atualizada: \n");
                imprimirListaSimples(*ptlista);
                break;

            case 3:
                printf("\nQual valor deseja buscar? \n");   //funcao para buscar um no na lista 
                scanf("%d", &valor);
                
                if(verificarSimples(*ptlista, valor)) {    //passa o ponteiro da lista 
                    printf("O valor %d esta na lista.\n", valor);
                } else {
                    printf("O valor %d nao esta na lista.\n", valor);
                }
                break;

            case 4:
                break;

            default:
                printf("Informe uma opcao valida.\n");
        }
    }while (opcao != 4);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//funcoes para a lista circular
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

int verificarCircular (struct s_no *ultimo, int x) { 

    if (ultimo == NULL) {
        return 0; 
    }

    struct s_no *atual = ultimo->prox; // Começa do primeiro nó

    do {
        if (atual->info == x) {
            return 1; 
        }
        atual = atual->prox;
    } while (atual != ultimo->prox); // Continua até voltar ao início

    return 0;
}

void imprimirListaCircular(struct s_no *ultimo) {  
    if (ultimo == NULL) {
        printf("Lista vazia\n");
        return;	
    }

    struct s_no *atual = ultimo->prox; // Começa do primeiro nó
        
    do {
        printf("%d ", atual->info);
        atual = atual->prox;    

    } while (atual != ultimo->prox); // Continua até voltar ao início

    printf("\n");
}

void inserirOrdenadoCircular(struct s_no **ultimo, int valor) { 
    struct s_no *novo = malloc(sizeof(struct s_no));
    if (novo == NULL) {  //VERIFICAR ESSA PARTE
        printf("Erro de alocacao\n");
        return;
    }
    novo->info = valor;

    if (*ultimo == NULL) {
        novo->prox = novo; // O nó aponta para ele mesmo
        *ultimo = novo; // O último nó é o novo nó
        return;
    }

    struct s_no *atual = (*ultimo)->prox; // Começa do primeiro nó
    struct s_no *anterior = *ultimo; // O último nó é o anterior

    if (valor < atual->info) { // Caso o novo valor seja menor que o primeiro
        novo->prox = atual;
        anterior->prox = novo; // O último nó agora aponta para o novo nó
        return;
    }

    while (atual != *ultimo && atual->info < valor) {
        anterior = atual;
        atual = atual->prox;
    }

    // Caso inserir depois do último elemento (valor maior que todos)
    if (atual == *ultimo && valor > atual->info) {
        novo->prox = atual->prox;
        atual->prox = novo;
        *ultimo = novo;  // atualiza o último
    } else {

        novo->prox = atual;
        anterior->prox = novo;
    }
}

int removerElementoCircular (struct s_no **ultimo, int valor) {

    if (*ultimo == NULL) {
        return 0; // Lista vazia
    }

    struct s_no *anterior = *ultimo; //ponteiro para o no anterior
    struct s_no *atual = (*ultimo)->prox; //ponteiro para percorrer a lista

    do {
        if (atual->info == valor) {
            if (atual == anterior) { // lista com 1 elemento
                *ultimo = NULL;
            } else {
                anterior->prox = atual->prox;
                if (atual == *ultimo) {
                    *ultimo = anterior; // atualiza último se remover o último
                }
            }
            free(atual);
            return 1; //encontrado e removido
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != (*ultimo)->prox);

    return 0; // não encontrado
}

void liberarListaCircular(struct s_no **ultimo) {

    if (*ultimo == NULL) {
        return; // Lista vazia
    }

    struct s_no *atual = (*ultimo)->prox; // Começa do primeiro nó
    struct s_no *temp;

    while (atual != *ultimo) { // Percorre a lista
        temp = atual;
        atual = atual->prox; // Avança para o próximo nó
        free(temp);
    }

    free(*ultimo); // Libera o último nó
    *ultimo = NULL;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuListaCircular (struct s_no **ptlista) {
    int opcao, valor;

    do { 
        printf("\n-----LISTA CIRCULAR-----\n");
        printf("1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Buscar\n");
        printf("4- Voltar para o menu principal\n");
        scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("\nInforme o valor para inserir: ");
            scanf("%d", &valor);
            inserirOrdenadoCircular(ptlista, valor);
            printf("\nValor inserido.\n");

            printf("\nLista atualizada: \n");
            imprimirListaCircular(*ptlista);

            break;

        case 2:
            printf("\nQual valor deseja remover? \n");
            scanf("%d", &valor);

            if (removerElementoCircular(ptlista, valor)) {
                printf("\nO valor %d foi removido\n", valor);
            } else {
                printf("\nO valor %d nao foi encontrado.\n", valor);
            }

            printf("Lista atualizada: \n");
            imprimirListaCircular(*ptlista);
        
            break;
        
        case 3:
            printf("\nQual valor deseja buscar?\n");
            scanf("%d", &valor);

            if(verificarCircular(*ptlista, valor)) {
                printf("\nO valor %d esta na lista.\n", valor);
            } else {
                printf("\nO valor %d nao esta na lista.\n", valor);
            }

            printf("Lista: \n");
            imprimirListaCircular(*ptlista);
            
            break;
        
        case 4:
            break;

        default:
            printf("Informe uma opcao valida\n");
    } 
    }  while (opcao != 4);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//funcoes para a lista dupla
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------


struct s_no* criarListaDupla () { //precisa criar para a lista duplamente encadeada, ja que ela precisa de um no cabeca
    struct s_no *cabeca = malloc(sizeof(struct s_no));   //cabeca vai ser o primeiro no da lista
    if (!cabeca) { 
        printf("Erro de alocacao\n");
        exit(1);
    }
    cabeca->prox = cabeca;
    cabeca->ant = cabeca;
    return cabeca;  //retorna a cabeca da lista, ou seja, o primeiro no
}

void inserirDupla (struct s_no *cabeca, int valor) {
    struct s_no *novo = malloc(sizeof(struct s_no));
    if (!novo) {
        printf("Erro de alocacao\n");
        return;
    }
    novo->info = valor;

    struct s_no *ultimo = cabeca->ant;  // O último nó é o nó anterior ao cabeçalho

    novo->prox = cabeca;  // O novo nó aponta para a cabeca 
    novo->ant = ultimo;  // O novo nó aponta para o último nó

    ultimo->prox = novo;
    cabeca->ant = novo;
}

struct s_no* buscarDupla (struct s_no *cabeca, int valor) {
    struct s_no *atual = cabeca->prox;  // Começa do primeiro nó

    while (atual != cabeca) {  //enquanto não chegar na cabeca, ou seja, enquanto não voltar ao inicio
        if (atual->info == valor)
            return atual;
        atual = atual->prox;
    }
    return NULL;  //retorna NULL se não encontrar o valor
}

int removerDupla (struct s_no *cabeca, int valor) {
    struct s_no *no = buscarDupla(cabeca, valor);  

    if (!no) {
       return 0;   //retorna 0 se o no não foi encontrado
    } 

    no->ant->prox = no->prox;
    no->prox->ant = no->ant;

    free(no);  //desaloca o no da memoria se for encontrado

    return 1; //retorna 1 se o no foi removido com sucesso
}

void imprimirListaDupla (struct s_no *cabeca) {
    struct s_no *atual = cabeca->prox;

    printf("-> ");
    if (atual == cabeca) {
        printf("Lista vazia\n");
        return;
    }

    while (atual != cabeca) {
        printf("%d ", atual->info);
        atual = atual->prox;
    }
    printf("\n");
}

void liberarListaDupla(struct s_no *cabeca) {  //precisa liberar a lista 
    struct s_no *atual = cabeca->prox; // Começa do primeiro nó

    while (atual != cabeca) {
        struct s_no *temp = atual->prox;  // Armazena o próximo nó
        free(atual); // Libera o nó atual
        atual = temp;
    }
    free(cabeca);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuListaDupla (struct s_no *cabeca) {
    int opcao, valor;

    do {
        printf("\n-----LISTA DUPLAMENTE ENCADEADA-----\n");
        printf("1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Buscar\n");
        printf("4- Voltar para o menu principal\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInforme o valor para inserir: ");
                scanf("%d", &valor);
                inserirDupla(cabeca, valor);
                printf("Valor inserido.\n");

                printf("Lista atualizada: \n");
                imprimirListaDupla(cabeca);

                break;

            case 2:
                printf("\nQual valor deseja remover? \n");
                scanf("%d", &valor);

                if (removerDupla(cabeca, valor)) {
                   printf("Valor %d removido.\n", valor);
                } else {
                    printf("Valor %d nao encontrado.\n", valor);
                }

                printf("Lista atualizada: \n");
                imprimirListaDupla(cabeca);
                
                break;

            case 3:
                printf("\nInforme o valor para buscar: ");
                scanf("%d", &valor);

                if (buscarDupla(cabeca, valor)) {
                    printf("Valor %d encontrado.\n", valor);
                }  else {
                    printf("Valor %d nao encontrado.\n", valor);
                }

                break;

            case 4:
                break;

            default:
                printf("Informe uma opcao valida\n");
        } 
    }  while (opcao != 4);  
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//funcoes para a fila
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Fila {
    struct s_no *inicio;
    struct s_no *final;
};

void inserirFila (struct Fila *fila, int valor ) {
    struct s_no *novo = (struct s_no *) malloc(sizeof(struct s_no));
    novo->info = valor;
    novo->prox = NULL;

    if (fila->final == NULL) {
        fila->inicio = novo;
    } else {
        fila->final->prox = novo;
    }

    fila->final = novo;

}

int removerFila (struct Fila *fila) {
    if (fila->inicio  == NULL) {
        printf("Fila vazia\n");
        return 0;
    }
    struct s_no *temp = fila->inicio;
    int valor;

    valor = temp->info;
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) { //se a fila ficou vazia
        fila->final = NULL;
    }

    free(temp); //libera da memoria
    printf("Valor %d removido da fila\n", valor);
    return valor;
}

void imprimirFila (struct Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia\n");
        return;
    }

    struct s_no *temp = fila->inicio;

    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->prox;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuFila (struct Fila *fila) {

    int opcao, valor;

    do {
        printf("\n-----FILA-----\n");
        printf("1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Voltar ao menu principal\n");
        scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("\nInforme o valor para inserir: ");
            scanf("%d", &valor);

            inserirFila(fila, valor);
            printf("\nValor inserido.\n");
            printf("Fila atualizada: \n");
            imprimirFila(fila);
            printf("\n");

            break;

        case 2:
            valor = removerFila(fila);
                if (valor != -1) {
                    printf("Valor %d removido da fila.\n", valor);
                    printf("Fila atualizada: \n");
                    imprimirFila(fila);
                    printf("\n");
                }
            break;
            
        case 3:
            break;

        default:
            printf("Informe uma opcao valida\n");
    }
    } while (opcao != 3);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//funcoes para a fila
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Pilha {
    struct s_no *topo;
};

void inserirPilha(struct Pilha *pilha, int valor) {
    struct s_no *novo = (struct s_no*) malloc(sizeof(struct s_no));
    novo->info = valor;
    novo->prox = pilha->topo;  // novo nó aponta para o topo atual
    pilha->topo = novo;        // topo agora é o novo nó
}

int removerPilha(struct Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia\n");
        return 0; // código de erro
    }
    struct s_no *temp = pilha->topo;
    int valor = temp->info;

    pilha->topo = pilha->topo->prox;  // atualiza topo para o próximo nó
    free(temp);
    return valor;
}

void imprimirPilha(struct Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia\n");
        return;
    }
    struct s_no *temp = pilha->topo;
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->prox;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuPilha (struct Pilha *pilha) {
    int opcao, valor;

    do {
        printf("\n-----PILHA-----\n");
        printf("1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Voltar ao menu principal\n");
        scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("\nInforme o valor para inserir: ");
            scanf("%d", &valor);
            inserirPilha(pilha, valor);
            printf("\nValor inserido.\n");
            printf("Pilha atualizada: \n");
            imprimirPilha(pilha);
            break;
        case 2:
            valor = removerPilha(pilha);
                if (valor != -1) {
                    printf("Valor %d removido.\n", valor);
                    printf("Pilha atualizada: \n");
                    imprimirPilha(pilha);
                }

            break;
        case 3:
            break;

        default:
            printf("Informe uma opcao valida\n");
    }
    } while (opcao != 3);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
//int main 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main () {

    int opcao;

    struct s_no *ptlista = NULL; //inicializa a lista vazia
    struct s_no *ptlistaCircular = NULL;
    struct s_no *listaDupla = criarListaDupla();

    struct Fila fila;

    fila.inicio = NULL;
    fila.final = NULL;

    struct Pilha pilha;
    pilha.topo = NULL;

    do {
        printf("\n-----MENU PRINCIPAL-----\n");
        printf("1- Lista Simplesmente Encadeada\n");
        printf("2- Lista Circular\n");
        printf("3- Lista Duplamente Encadeada\n");
        printf("4- Fila\n");
        printf("5- Pilha\n");
        printf("6- SAIR\n");
        printf("\n");
        printf("Qual deseja escolher? \n");
        scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            menuListaSimples(&ptlista); 
            break;

        case 2:
            menuListaCircular(&ptlistaCircular);
            break;

        case 3:
            menuListaDupla(listaDupla);  //estou passando apenas listaDupla, pois ela ja é a cabeca da lista
            break;

        case 4:
            menuFila(&fila);
            break;

        case 5:
            menuPilha(&pilha);
            break;

        case 6:
            printf("Saindo...");
            break;

        default:
            printf("Informe uma opcao valida.\n");

    } 
} while (opcao != 6);
    return 0;
} 