#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Estrutura do elemento
typedef struct sElemento{
	struct sElemento *next;
	struct sElemento *prev;
	int dado;
} Elemento;

// Estrutura da fila
typedef struct sLista{
	struct sElemento *head;
	struct sElemento *tail;
	int size;
} Lista;

// Função responsável pela inicialização da fila
Lista * iniciaFila(){
	Lista* fila = (Lista*) malloc(sizeof(Lista));
	fila->head=NULL;
	fila->tail=NULL;
	fila->size=0;
	return fila;
}

//Funções declaradas no escopo do programa
void pqinsert(Lista* valores, int valor);
void remover(Lista *valores, Elemento *antigo);
void imprimir(Lista *valores);
void pqmindelete(Lista *valores);

// Função principal
int main(void){
	setlocale(LC_ALL,"Portuguese");
	Lista *a;
	a = iniciaFila();
	
	int opt,numero;
	for(;;){
		printf("Fila de prioridade ascendente:\n1 - Inserir\n2 - Remove o menor\n3 - Imprime fila\n4 - Sair\n");
		scanf("%i",&opt);
		if(opt == 4){
			free(a);
			exit(0);
		}
		if(opt == 3){
			if(a->size == 0){
				printf("Fila está vazia.\n");
			}else{
				imprimir(a);
			}
		}
		if(opt == 2){
			if(a->size == 0){
				printf("Fila está vazia.\n");
			}else{
				pqmindelete(a);
			}
		}
		if(opt ==1){
			system("cls");
			printf("Insira um número para colocar na fila:");
			scanf("%i",&numero);
			pqinsert(a, numero);
			system("cls");
		}
	}
	return 0;
}

// pqinsert, essa função realiza a inserção dos elementos dentro da fila
void pqinsert(Lista* valores, int valor){
	Elemento* novo = (Elemento*) malloc (sizeof(Elemento));
	
	novo->dado=valor;
	novo->next = NULL;
	novo->prev=NULL;

	if(valores->size==0){
		valores->head = novo;
		valores->tail=novo;
	}else{
		novo->next=valores->tail->next;
		novo->prev=valores->tail;
		valores->tail->next = novo;
		valores->tail=novo;				
	}
	valores->size++;
}

// remover o elemento da fila
void remover(Lista *valores, Elemento *antigo){
	if(valores->size!=0 && antigo!=NULL){
		if(antigo == valores->head){
			valores->head = antigo->next;
			if(valores->head == NULL){
				valores->tail=NULL;
			}else{
				antigo->next->prev = NULL;
			}
		}else{
			antigo->prev->next = antigo->next;
			if(antigo->next == NULL){
				valores->tail = antigo->prev;
			}else{
				antigo->next->prev = antigo->prev;
			}
		}
		
		free(antigo);
		valores->size--;
	}
}

// realiza a impressão da fila em ordem de chegada dos dados
void imprimir(Lista *valores){
	Elemento* aux;
	aux = valores->head;
	int i = 0;
	for(i=0; i<valores->size; i++){
		printf("%i  ", aux->dado);
		aux = aux->next;
	}
	printf("\n");
}

// uma função de remover, porém vai pegar sempre o valor mínimo para retirar
void pqmindelete(Lista *valores){
	Elemento* aux;
	aux = valores->head;
	int i = 0;
	int menor_dado = aux->dado;
	Elemento *menor = aux;
	for(i=0;i<valores->size;i++){
		if(aux->dado<menor_dado){
			menor_dado = aux->dado;
			menor = aux;
		}
		aux = aux->next;
	}
	
	remover(valores, menor);
	
	printf("Excluindo o menor valor da fila: %d\n", menor_dado);

}
