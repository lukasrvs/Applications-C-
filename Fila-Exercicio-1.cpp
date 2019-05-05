#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

typedef struct sNodo{
	struct sNodo *next;
	struct sNodo *prev;
	int dado;
} Nodo;

typedef struct sFila{
	struct sNodo *front;
	struct sNodo *rear;
	int size;
} Fila;

typedef struct sEspera{
	struct sNodo *front;
	struct sNodo *rear;
	int size;
} Espera;

Fila * criaFila(){
	Fila *fila;
	fila = (Fila*)malloc(sizeof(Fila));
	fila->front = NULL;
	fila->rear = NULL;
	fila->size = 0;
	return fila;
}

Espera * criaEspera(){
	Espera *espera;
	espera = (Espera*)malloc(sizeof(Espera));
	espera->front = NULL;
	espera->rear = NULL;
	espera->size = 0;
	return espera;
}

Nodo * criaNodo(int dado){
	Nodo *nodo;
	nodo = (Nodo*)malloc(sizeof(Nodo));
	nodo->next = NULL;
	nodo->prev = NULL;
	nodo->dado = dado;
	return nodo;
}

int filaVazia(Fila *fila);
int removerNodo(Fila *fila, Nodo *nodo);
void fremover(Fila *fila);
void imprimirEspera(Espera *espera);
void imprimirFila(Fila *fila);
void inserirEspera(Espera *espera, Nodo *nodo, int dado);
void inserirNodo(Fila *fila, Nodo *pivo, int dado);
void removerEspera(Espera *espera, Nodo *nodo);
void transfereEsperaParaEstacionamento(Fila *fila, Espera *espera);

int main(void) {
	setlocale(LC_ALL,"Portuguese");
	Fila *a;
	a = criaFila();
	Espera *e;
	e = criaEspera();
	Nodo *nodo;
	Nodo *primeiroNodo;
	primeiroNodo = a->front;
	nodo = a->front;

	int opt, placa, dado, removido;

	for(;;){
		system("cls");
		printf("Estacionamento:\n1 - Entrada de veículo\n2 - Saída de Veículo\n3 - Veículos\n4 - Sair\n>");
		scanf("%i", &opt);
	
		if(opt < 1 && opt > 4){
			printf("Opção inválida, tente novamente!");	
		}
		if(opt == 4){
			printf("Saindo...");
			Sleep(400);
			exit(0);
		}
		if(opt == 3){
			imprimirFila(a);
			imprimirEspera(e);
			printf("\n\nAPERTE ENTER PARA CONTINUAR\n\n");
			getch();
		}
		if(opt == 2){
			if(filaVazia(a) == 0){
				getch();
			}else{
			fremover(a);
				if(e->size != 0){
					transfereEsperaParaEstacionamento(a, e);
				}
			}
		}
		if(opt == 1){
			if(a->size < 10){
				printf("Qual a placa do carro para adicionar ao estacionamento:");
				scanf("%i",&placa);
				inserirNodo(a, a->rear, placa);
			}else{
				printf("Estacionamento está cheio!\nQual a placa do carro para adicionar a fila de espera:\n");
				scanf("%i",&placa);
				inserirEspera(e, e->rear, placa);
			}
		}
	}

	getch();
	return 0;
}

void inserirNodo(Fila *fila, Nodo *pivo, int dado){
	Nodo *novo;
	novo = criaNodo(dado);
	
	if((pivo == NULL) && (fila->size != 0)){
		printf("Só é aceito pivo NULL na inserção do primeiro elemento");
		return ;
	}
	if(fila->size == 0){
		fila->front = novo;
		fila->rear = novo;
	}else {
		novo->next = pivo->next;
		novo->prev = pivo;
		if(pivo->next == NULL){
			fila->rear = novo;
		}else {
			pivo->next->prev = novo;
		}
		pivo->next = novo;
	}
	fila->size++;
}

int removerNodo(Fila *fila, Nodo *nodo){
	int dado;
	if((nodo != NULL) && (fila->size != 0)){
		if(nodo == fila->front) {
			fila->front = nodo->next;
			if(fila->front == NULL){
				fila->rear = NULL;
			}else {
				nodo->next->prev = NULL;
			}
		}else{
			nodo->prev->next = nodo->next;
			if(nodo->next == NULL){
				fila->rear = nodo->prev;
			}else {
				nodo->next->prev = nodo->prev;
			}
		}
		dado = nodo->dado;
		free(nodo);
		fila->size--;
	}
	return dado;
}

void transfereEsperaParaEstacionamento(Fila *fila, Espera *espera) { 
	Nodo *dado;
	dado = espera->front;
	int placa;
	
	placa = dado->dado;
	
	removerEspera(espera, espera->front);
	
	inserirNodo(fila, fila->rear,placa);
}

void inserirEspera(Espera *espera, Nodo *pivo, int dado){
	Nodo *novo;
	novo = criaNodo(dado);
	
	if((pivo == NULL) && (espera->size != 0)){
		printf("Só é aceito pivo NULL na inserção do primeiro elemento");
		return ;
	}
	if(espera->size == 0){
		espera->front = novo;
		espera->rear = novo;
	}else {
		novo->next = pivo->next;
		novo->prev = pivo;
		if(pivo->next == NULL){
			espera->rear = novo;
		}else {
			pivo->next->prev = novo;
		}
		pivo->next = novo;
	}
	espera->size++;
}

void removerEspera(Espera *espera, Nodo *nodo){
	if((nodo != NULL) && (espera->size != 0)){
		if(nodo == espera->front) {
			espera->front = nodo->next;
			if(espera->front == NULL){
				espera->rear = NULL;
			}else {
				nodo->next->prev = NULL;
			}
		}else{
			nodo->prev->next = nodo->next;
			if(nodo->next == NULL){
				espera->rear = nodo->prev;
			}else {
				nodo->next->prev = nodo->prev;
			}
		}
		free(nodo);
		espera->size--;
	}
}

void imprimirFila(Fila *fila){
	Nodo *tmp;
	tmp = fila->front;
	printf("Estacionamento:\n");
	if(fila->size == 0){
		printf("Estacionamento está vazio\n");
	}else{
		while(tmp != NULL){
			printf("%i  ", tmp->dado);
			tmp = tmp->next;
		}
	}
	printf("\n");
}

void imprimirEspera(Espera *espera){
	Nodo *tmp;
	tmp = espera->front;
	printf("Espera de vaga:\n");
	
	if(espera->size == 0){
		printf("Espera de vaga está vazia\n");
	}else{
		while(tmp != NULL){
			printf("%i  ", tmp->dado);
			tmp = tmp->next;
		}
	}
}

int filaVazia(Fila *fila){
	if(fila->size != 0){
		return 1;
	}else {
		printf("A fila está vazia");
		return 0;
	}
}

void fremover(Fila *fila){
	Nodo* elemento;
	int op, placa, dado, removido;
	
	int primeiroElemento;
	primeiroElemento = fila->front->dado;
	
	elemento = fila->front;
	printf("Selecione a placa do carro que deseja retirar: \n");
	scanf("%i", &placa);
	if(elemento->dado != placa){
		do{
			Nodo *aux = elemento->next;
			if(elemento->dado == placa){
				removido = removerNodo(fila, fila->front);
			}else{
				dado = removerNodo(fila, fila->front);
				inserirNodo(fila, fila->rear, dado);
			}
			elemento=aux;
		}while(elemento->dado != primeiroElemento);
	}else{
		removido = removerNodo(fila, fila->front);
	}
}
