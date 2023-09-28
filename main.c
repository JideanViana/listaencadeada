#include <stdio.h>
#include <stdlib.h>

typedef struct no{
        int x;
        struct no *proximo;
    }No;
typedef struct{
    No *inicio;
    No *fim;
    int tamanho;
}Lista;

    void criar_lista(Lista *lista){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }

    //  INSERIR NO ÍNICIO:
    void inserir_inicio(Lista *lista, int numero){
        No *novo = malloc(sizeof(No));
            if (novo == NULL)   {
                printf("Erro ao alocar memoria");
                return;
            }
        novo->x = numero;
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        if(lista->fim == NULL)
            lista->fim = novo;
        lista->fim->proximo = lista->inicio;
        lista->tamanho++;
        return;
    }
    //INSERIR NO FIM:
    void inserir_fim(Lista *lista, int numero){
        No *novo = malloc(sizeof(No));
        if(novo == NULL){
            printf("Erro ao alocar memoria");
            return;
        }
        novo->x = numero;

        if(lista->inicio == NULL) {//CASO SEJA O PRIMEIRO ELEMENTO:
            lista->inicio = novo;
            lista->fim = novo;
            lista->fim->proximo = lista->inicio;
        }else{   //CASO NÃO SEJA O PRIMEIRO:
            lista->fim->proximo = novo;
            lista->fim = novo;
            novo->proximo = lista->inicio;
        }
        lista->tamanho++;
        return;
    }
    //INSERIR ORDENADAMENTE:
    void inserir_ordenado(Lista *lista, int numero){
        No *auxiliar, *novo = malloc(sizeof(No));
        if(novo == NULL){
            printf("Erro ao alocar memoria.\n");
            return;
        }
        novo->x = numero;

        if(lista->inicio == NULL){
            inserir_inicio(lista, numero);
        }
        else if(novo->x < lista->inicio->x){
            inserir_inicio(lista, numero);
        }else{
            auxiliar = lista->inicio;
            while(auxiliar->proximo != lista->inicio && novo->x > auxiliar->proximo->x)
                auxiliar = auxiliar->proximo;
            if(auxiliar->proximo == lista->inicio)
                inserir_fim(lista, numero);
            else{
            novo->proximo = auxiliar->proximo;
            auxiliar->proximo = novo;
            lista->tamanho++;
            }
        }
        return;
    }

    //IMPRIMIR:
    void imprimir(Lista lista) {
        No *no = lista.inicio;
        printf("\n\tLista com tamanho %d: ", lista.tamanho);
        if(no){
            do{
                printf("%d ", no->x);
                no = no->proximo;
            }while(no != lista.inicio);
            printf("\nInicio da lista: %d\n", no->x);
        }
        printf("\n\n");
        return;
    }
    //REMOVER:
    No* remover(Lista *lista,int numero){
        No *auxiliar, *remover = NULL;

        if(lista->inicio == NULL){
            printf("Lista vazia.\n");
            return remover;
        }

        if(lista->inicio == lista->fim && lista->inicio->x == numero){
            remover = lista->inicio;
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->tamanho--;
        }else if(lista->inicio->x == numero){
            remover  = lista->inicio;
            lista->inicio = remover->proximo;
            lista->fim->proximo = lista->inicio;
            lista->tamanho--;
        }else{
            auxiliar = lista->inicio;
            while(auxiliar->proximo != lista->inicio && auxiliar->proximo->x != numero)
                auxiliar = auxiliar->proximo;
            if(auxiliar->proximo->x == numero){
                if(lista->fim == auxiliar->proximo){
                    remover = auxiliar->proximo;
                    auxiliar->proximo = remover->proximo;
                    lista->fim = auxiliar;
                } else {
                    remover = auxiliar->proximo;
                    auxiliar->proximo = remover->proximo;
                }
                lista->tamanho--;
            }
        }
        return remover;
    }
    //BUSCAR
    No* buscar(Lista *lista, int numero){
        No *auxiliar = lista->inicio;

        if(auxiliar){
            do{
                if(auxiliar->x == numero)
                    return auxiliar;
                auxiliar = auxiliar->proximo;
            }while(auxiliar != lista->inicio);
        }
        return NULL;
    }

int main(){

    int opcao, valor;
    Lista lista;
    No *remove = NULL;
    criar_lista(&lista);

    do{
        printf("\n0-SAIR \n1-INSERIR NO INICIO \n2-INSERIR NO FIM \n3-INSERIR ORDENADO \n4-IMPRIMIR \n5-REMOVER \n6-BUSCAR\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_inicio(&lista, valor);
            break;
        case 2:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_fim(&lista, valor);
            break;
        case 3:
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            inserir_ordenado(&lista, valor);
            break;
        case 4:
            imprimir(lista);
            break;
        case 5:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remove = remover(&lista, valor);
            if(remove){
                printf("Elemento removido: %d\n", remove->x);
                free(remove);
            }else
                printf("Elemento inesistente.\n");

            break;
        case 6:
            printf("Digite o valor que deseja encontrar: ");
            scanf("%d", &valor);
            remove = buscar(&lista, valor);
            if(remove)
                printf("Valor encontrado: %d\n", remove->x);
            else
                printf("Valor não encontrado!\n");
            break;
        default:
            if(opcao != 0)
                printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}
