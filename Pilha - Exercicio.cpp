#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define MAX 30

/*
+ INSTITUTO FEDERAL CATARINENSE - CAMPUS VIDEIRA
+ Lucas Antônio Ribeiro Vitor de Souza
+ Estrutura de Dados I
+ Exercicios - Pilha
+ Professor: Manassés Ribeiro
*/

// Estrutura do nodo
typedef struct sNode {
	char dado;
	struct sNode *next;
	struct sNode *prev;
}Node;

// Estrutura da pilha
typedef struct stack {
	struct sNode *head;
	struct sNode *tail;
	int size;
	char top;
}Stack;

//Funções declaradas no escopo
void removeNode(Stack *stack, Node *node);
int verificaAcerto(Stack *stack, int tam, int pare, int colc, int chav);
void alternativa();
void insertNode(Stack *stack, Node *pivot, char dado);
void printStack(Stack *stack);
char verificaStack(Stack *stack);

//Função principal
int main(void) {
	setlocale(LC_ALL,"Portuguese");
	Stack *stack;
	stack = (Stack*)malloc(sizeof(Stack));
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	
	char cha, equation[MAX];
	int i=0, tam=0, pare=0, colc=0, chav=0,result;
	
	printf("Digite a equação: ");
	scanf("%[^\n]s", &equation);
	tam = strlen(equation);
	
	for(i=0;i<tam;i++){
		cha = equation[i];
		if(equation[i] == '('){
			insertNode(stack, stack->tail, cha);
			pare++;
		}
		if(equation[i] == '['){
			insertNode(stack, stack->tail, cha);
			colc++;
		}
		if(equation[i] == '{'){
			insertNode(stack, stack->tail, cha);
			chav++;
		}
		if(equation[i] == ')'){
			if(stack->size == 0){
				printf("Expressão %s errada",equation);
			}
			cha = verificaStack(stack);
			if(cha == '('){
				removeNode(stack,stack->tail);
				pare--;
			}
		}
		if(equation[i] == ']'){
			if(stack->size == 0){
				printf("Expressão %s errada",equation);
			}
			cha = verificaStack(stack);
			if(cha == '['){
				removeNode(stack,stack->tail);
				colc--;
			}
		}
		if(equation[i] == '}'){
			if(stack->size == 0){
				printf("Expressão %s errada",equation);
			}
			cha = verificaStack(stack);
			if(cha == '{'){
				removeNode(stack,stack->tail);
				chav--;
			}
		}
	}
	result = pare + colc + chav;
	
	if(result == 0){
		printf("Expressão %s correta",equation);
	}
	if(result != 0){
		printf("Expressão %s errada",equation);
	}
	
	getch();
	return 0;
}

// Inserção do nodo, funciona como uma lista duplamente encadeada e nesse caso aplicando no conceito da pilha, ou seja adicionando sempre ao final da pilha
void insertNode(Stack *stack, Node *pivot, char dado) {
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->dado = dado;
	
	if(pivot == NULL && stack->size != 0){
		printf("só aceita pivo NULL");
		return ;
	}
	if(stack->size == 0){
		stack->head = newNode;
		stack->tail = newNode;
	} else {
		newNode->next = pivot->next;
		newNode->prev = pivot;
		if(pivot->next == NULL){
			stack->tail = newNode;
		}else {
			pivot->next->prev = newNode;
		}
		pivot->next = newNode;
	}
	stack->size++;
}

// Função de remoção da pilha
void removeNode(Stack *stack, Node *node) {
	if((node != NULL) && (stack->size > 0) ){
		if(node == stack->head){
			stack->head = node->next;
			if(stack->head == NULL){
				stack->tail = NULL;
			}else{
				node->next->prev = NULL;
			}
		}else{
			node->prev->next = node->next;
			if(node->next == NULL){
				stack->tail = node->prev;
			}else{
				node->next->prev = node->prev;
			}
		}
		free(node);
		stack->size--;
	}
}

// Imprimi dados da pilha
void printStack(Stack *stack) {
	Node* node;
	node = stack->head;
	while(node != NULL){
		printf("%c",node->dado);
		node = node->next;
	}
}

// Verifica o topo da pilha
char verificaStack(Stack *stack) {
	//Node *removido;
	//removido = stack->tail;
	//char rem = removido->dado;
	//return rem;
	
	return stack->tail->dado;
}
