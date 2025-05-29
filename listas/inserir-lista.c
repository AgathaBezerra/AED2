#include <stdio.h>
#include <stdlib.h>

struct s_no {
    int info;
    struct s_no *prox;
};


int main () {
    struct s_no *ptlista, *p1, *p2, *p3, *p4, *p5, *ponteiro;
    int valor1, valor2, valor3, valor4, valor5;
    ptlista = NULL;

    p1 = (malloc(sizeof(struct s_no)));
    p2 = (malloc(sizeof(struct s_no)));
    p3 = (malloc(sizeof(struct s_no)));
    p4 = (malloc(sizeof(struct s_no)));
    p5 = (malloc(sizeof(struct s_no)));

    printf("Digite o valor do primeiro no: ");
    scanf("%d", &valor1);

    printf("Digite o valor do segundo no: ");
    scanf("%d", &valor2);

    printf("Digite o valor do terceiro no: ");
    scanf("%d", &valor3);

    printf("Digite o valor do quarto no: ");
    scanf("%d", &valor4);

    printf("Digite o valor do quinto no: ");    
    scanf("%d", &valor5);

    p1->info = valor1;
    p1->prox = p2;

    p2->info = valor2;
    p2->prox = p3;

    p3->info = valor3;
    p3->prox = p4;

    p4->info = valor4;
    p4->prox = p5;

    p5->info = valor5;
    p5->prox = NULL;

    ptlista = p1; // primeiro no da lista

    printf("Lista");
    printf("\n");
    printf("%d -> ", p1->info);
    printf("%d -> ", p2->info);
    printf("%d -> ", p3->info);
    printf("%d -> ", p4->info); 
    printf("%d -> ", p5->info);
    printf("NULL");

    return 0;

}