#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct Node{
		struct Node *next;
		struct Node *prev;
		int num; //Depende do tipo de dados que se deseja trabalhar
	} Node;
	
	typedef struct Lista{
		struct Node *head;
		struct Node *tail;
		int size;
	} LISTA;

void insertNode(LISTA *lista, Node *Node, int num);
void printNode(LISTA *lista);

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	
	LISTA* lista;
	lista = (LISTA*) malloc(sizeof(LISTA));
	lista->head = lista->tail = NULL;
	lista->size = 0;

	int number, i=0;
	
	for(i=0;i<3;i++){
		printf("Insira o número para lista encadeada dupla: \n");
		scanf("%i",&number);
		insertNode(lista, lista->head, number);
	}
	
	printNode();
return 0;
}

void insertNode(LISTA *lista, Node* nodePivot, int num) {
	Node* newNode;
	newNode = (Node*) malloc(sizeof(Node));
	newNode -> num = num;
	
	if((nodePivot == NULL) && (lista->size == 0)) {
		if(lista -> size == 0) {
		lista -> head = newNode;
		lista -> tail = newNode;
		}else {
		newNode -> next = nodePivot -> next;
		newNode -> prev = nodePivot;
		}
		if(nodePivot -> next == NULL) {
			lista -> tail = newNode;		
		}else {
			nodePivot -> next -> prev = newNode;
		}
		nodePivot -> next = newNode;	
	}
	lista -> size++;
}

void removeNode(LISTA *lista ,Node* node){
	if((node != NULL) && (size > 0) ){
		if(node == lista->head){
			lista->head = node->next;
			if(lista->head == NULL){
				lista->tail = NULL;
			}else{
				node->next->prev = NULL;
			}
		}else{
			node->prev->next = node->next;
			if(node->next == NULL){
				lista->tail = node->prev;
			}else{
				node->next->prev = node->prev;
			}
		}
	}
	free();
	lista->size--;
}

void printNode(LISTA *lista){
	
	Node* node;
	node = lista->head;
	while(node != NULL){
		printf("\n %d",node->num);
		node = node->next;
	}
	
}


//remocao (elemento, lista)
//inicio
// se ((elemento != NULL) e (lista não vazia))
//se (elemento == lista->head
//lista->head = elemento->next
//se (lista->head == NULL)
//lista->tail = NULL
//senao
//elemento->next->prev = NULL
//fimse
//senao
//elemento->prev->next = elemento->next
//se (elemento->next == NULL)
//lista->tail = elemento-prev
//senao
//elemento->next->prev = elemento->prev
//fimse
//fimse
//destroi(elemento)
//atualiza_tamanho_lista
// fimse
//fim

//Insercao (lista, pivo, dado)
//inicio
// Cria (novo_elemento)
// Aloca_memória (novo_elemento)
// novo_elemento->dado = dado
// se ((pivo==NULL) E (lista não vazia))
// retorna erro indicando que só
// aceita pivo NULL na inserção do
// primeiro elemento
// se (lista vazia)
//lista->head = novo_elemento
//lista->tail = novo_elemento
//senao
//novo_elemento->next = pivo->next
//novo_elemento->prev = pivo
//se (pivo->next == NULL)
//lista->tail = novo_elemento
//senao
//pivo->next->prev = novo_elemento
//fimse
//pivo->next = novo_elemento
// fimse
// atualiza_tamanho_lista
//fim





