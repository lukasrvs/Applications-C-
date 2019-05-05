#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo{
	int info; //dado
	struct sNodo *next; //Elo
} Nodo;

typedef struct sLista{
	Nodo *head; //cabeça da lista
	Nodo *tail; //cauda da lista
	int size; //tamanho
} Lista;

Lista* criaLista(){
	Lista *lista;
	lista = (Lista*) malloc (sizeof(Lista));
	lista->head = NULL;
	lista->tail = NULL;
	lista->size = 0;
	
	return lista;
}

Nodo* criaNodo(int info){
	Nodo *nodo;
	nodo = (Nodo*) malloc (sizeof(Nodo));
	nodo->info = info;
	nodo->next = NULL;
	
	return nodo;
}

void insercao(Lista *lista, Nodo *pivo, int info);
int remocao(Lista *lista, Nodo *pivo);
void percorreListaCabecaCauda(Lista *lista);

int main(){
	Lista *a;
	a = criaLista(); //cria lista
	
	insercao(a, NULL, 10);
	insercao(a, a->head, 20);
	insercao(a, a->tail, 30);
	insercao(a, a->head, 50);

	//percorre lista
	percorreListaCabecaCauda(a);
	
	printf("\nhead: %d\n", a->head->info);
	printf("tail: %d\n", a->tail->info);
	
	remocao(a, NULL);
	remocao(a, a->tail);
	remocao(a, a->head);

	//percorre lista
	percorreListaCabecaCauda(a);
	
	printf("\nhead: %d\n", a->head->info);
	printf("tail: %d\n", a->tail->info);
	
	return 0;
}

void insercao(Lista *lista, Nodo *pivo, int info){
	Nodo *novo_nodo;
	novo_nodo = criaNodo(info);

	if (pivo == NULL){
		if (lista->size == 0)
			lista->tail = novo_nodo;
	
		novo_nodo->next = lista->head;
		lista->head = novo_nodo;
	} else {
		if (pivo->next == NULL)
			lista->tail = novo_nodo;
	
		novo_nodo->next = pivo->next;
		pivo->next = novo_nodo;
	}
	
	lista->size++;	
}

int remocao(Lista *lista, Nodo *pivo){
	Nodo *antigo;

	if (lista->size == 0) {
		printf("Impossivel excluir. Lista vazia!\n");
		return 0;
	}
	
	if (pivo == NULL){
		antigo = lista->head;
		lista->head = lista->head->next;
		
		if (lista->head == NULL)
			lista->tail = NULL;
	}else{
		if (pivo->next == NULL){
			printf("Impossivel excluir. O elemento pivo eh o ultimo na Lista!\n");
			return 0;
		}

		antigo = pivo->next;
		pivo->next = pivo->next->next;
		if (pivo->next == NULL)
			lista->tail = pivo;
	}

	free(antigo);
	lista->size--;
	
	return 0;
}

void percorreListaCabecaCauda(Lista *lista){
	Nodo *aux;
	//Procedimento para percorrer a lista
	aux = lista->head;
	while(aux != NULL){
		printf("%d, ", aux->info);
		aux = aux->next;
	}
}
