#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
	int num; //dado
	struct NODE *next; //Elo
} Node;

typedef struct Lista{
	NODE *head; //cabeça da lista
	NODE *tail; //cauda da lista
	int size; //tamanho
} LISTA;

Lista* criaLista(){
	LISTA *lista;
	lista = (LISTA*) malloc (sizeof(LISTA));
	lista->head = NULL;
	lista->tail = NULL;
	lista->size = 0;
	
	return lista;
}

Node* criaNode(int num){
	Node *nodo;
	nodo = (Node*) malloc (sizeof(Node));
	nodo->num = num;
	nodo->next = NULL;
	
	return nodo;
}

void insercao(LISTA *lista, Node *pivo, int num){
	Node *novo_nodo;
	novo_nodo = criaNode(num);

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

int remocao(LISTA *lista, Node *pivot){
	Node *antigo;

	if (lista->size == 0) {
		printf("Impossivel excluir. Lista vazia!\n");
		return 0;
	}
	
	if (pivot == NULL){
		antigo = lista->head;
		lista->head = lista->head->next;
		
		if (lista->head == NULL)
			lista->tail = NULL;
	}else{
		if (pivot->next == NULL){
			printf("Impossivel excluir. O elemento pivo eh o ultimo na Lista!\n");
			return 0;
		}

		antigo = pivot->next;
		pivot->next = pivot->next->next;
		if (pivot->next == NULL)
			lista->tail = pivot;
	}

	free(antigo);
	lista->size--;
	
	return 0;
}

void percorreListaCabecaCauda(LISTA *lista){
	Node *aux;
	//Procedimento para percorrer a lista
	aux = lista->head;
	while(aux != NULL){
		printf("%d, ", aux->num);
		aux = aux->next;
	}
}

int main(){
	system("color 0A");
	LISTA *a;
	a = criaLista(); //cria lista
	
	insercao(a, NULL, 10);
	insercao(a, a->head, 20);
	insercao(a, a->tail, 30);
	insercao(a, a->head, 50);

	//percorre lista
	percorreListaCabecaCauda(a);
	
	printf("\nhead: %d\n", a->head->num);
	printf("tail: %d\n", a->tail->num);
	
	remocao(a, NULL);
	remocao(a, a->tail);
	remocao(a, a->head);

	//percorre lista
	percorreListaCabecaCauda(a);
	
	printf("\nhead: %d\n", a->head->num);
	printf("tail: %d\n", a->tail->num);
	
	return 0;
}
