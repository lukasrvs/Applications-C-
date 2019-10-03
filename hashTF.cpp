#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 100

typedef struct sNode{
	struct sNode *next;
	struct sNode *prev;
	char info[MAX];
}Node;

typedef struct sBucket{
	struct sNode *head;
	struct sNode *tail;
	struct sBucket *next;
	struct sBucket *prev;
	int key;
	int size;
}Bucket;

typedef struct sHash{
	struct sBucket *head;
	struct sBucket *tail;
	int size;
}Hash;

Hash * createHash();
Bucket * createBucket(int key);
Node * createNode(char* info);
Node * findPivot(Bucket *bucket, char* info);
void autoInsert();
char castString(char* info);
void bucketDestroy(Hash *hash, char* info);
void bucketNew(Hash *hash, char* info);
void findNode(Hash *hash, char* info);
void menu();
void initHash(Hash *hash);
void insertHash(Hash *hash, Bucket *newBucket);
void insertNode(Bucket *bucket, Node *pivot, char* info);
void removeNode(Bucket *bucket, Node *node);
void removeBucket(Hash *hash, Bucket *bucket);
void printBucket(Bucket *hash);
void printHash(Hash *hash);
void verifierBucket(Bucket *bucket, char* info);
void song();

int main(void) {
	setlocale(LC_ALL,"Portuguese");
	menu();
	song();
	
	return 0;
} 

Hash * createHash(){
	Hash *hash;
	hash = (Hash*)malloc(sizeof(Hash));
	hash->head = NULL;
	hash->tail = NULL;
	hash->size = 0;
	return hash;
}

Bucket * createBucket(int key){
	Bucket *bucket;
	bucket = (Bucket*)malloc(sizeof(Bucket));
	bucket->head = NULL;
	bucket->tail = NULL;
	bucket->size = 0;
	bucket->next = NULL;
	bucket->prev = NULL;
	bucket->key = key;
	return bucket;
}

Node * createNode(char* info){
	Node *node;
	node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->prev = NULL;
	strcpy(node->info, info);
	return node;
}

void insertNode(Bucket *bucket, Node *pivot, char* info){
	Node *newNode;
	newNode = createNode(info);
	
	if((pivot == NULL) && (bucket->size != 0)){
		newNode->next = bucket->head;
		bucket->head = newNode;
		newNode->next->prev = newNode;
	}else if(bucket->size == 0){
		bucket->head = newNode;
		bucket->tail = newNode;
	}else {
		newNode->next = pivot->next;
		newNode->prev = pivot;
		if(pivot->next == NULL){
			bucket->tail = newNode;
		}else {
			pivot->next->prev = newNode;
		}
		pivot->next = newNode;
	}
	bucket->size++;	
}

void insertHash(Hash *hash, Bucket *newBucket){
	Bucket * pivot;
	pivot = hash->tail;
	
	if((pivot == NULL) && (hash->size != 0)){
		printf("Só é aceito pivo NULL na inserção do primeiro elemento");
		return ;
	}
	if(hash->size == 0){
		hash->head = newBucket;
		hash->tail = newBucket;
	}else {
		newBucket->next = pivot->next;
		newBucket->prev = pivot;
		if(pivot->next == NULL){
			hash->tail = newBucket;
		}else {
			pivot->next->prev = newBucket;
		}
		pivot->next = newBucket;
	}
	hash->size++;
}

void initHash(Hash *hash){
	int i;
	for(i=0;i<10;i++){
		Bucket *b;
		b = createBucket(i);
		insertHash(hash, b);
	}
}

char castString(char* info){
	int key;
	key = (int)info[0];
	
	return key % 10;
}

Node * findPivot(Bucket *bucket, char* info){
	Node *aux;
	aux = bucket->head;
	while(aux != NULL){
		if(strcmp(aux->info,info) == 1){
			return aux->prev;
		}
		aux = aux->next;
	}
	return bucket->tail;
}

void bucketNew(Hash *hash, char* info){
	Bucket *aux;
	aux = hash->head;
	int i = castString(info);
	Node *pivot;
	
	while(aux != NULL){
		if(i == aux->key){
			pivot = findPivot(aux, info);
			insertNode(aux,pivot,info);
			return ;
		}
		aux = aux->next;
	}
}

void removeNode(Bucket *bucket, Node *node){
	if((node != NULL) && (bucket->size != 0)){
		if(node == bucket->head) {
			bucket->head = node->next;
			if(bucket->head == NULL){
				bucket->tail = NULL;
			}else {
				bucket->next->prev = NULL;
			}
		}else{
			node->prev->next = node->next;
			if(node->next == NULL){
				bucket->tail = node->prev;
			}else {
				node->next->prev = node->prev;
			}
		}
		free(node);
		bucket->size--;
	}
}

void verifierBucket(Bucket *bucket, char* info){
	Node *aux;
	aux = bucket->head;
	int flag = 0;
	while(aux != NULL){
		if(strcmp(info, aux->info) == 0){
			printf("Dado: %s existe\n", info);
			flag = 1;
			removeNode(bucket, aux);
			getch();
			return ;
		}
		aux = aux->next;
	}
	if(flag == 0){
		printf("Dado não existe");
		getch();
	}
}

void bucketDestroy(Hash *hash, char* info){
	Bucket *aux;
	aux = hash->head;
	int i = castString(info);
	Node *node;
	
	while(aux != NULL){
		if(i == aux->key){
			verifierBucket(aux, info);
			return ;
		}
		aux = aux->next;
	}
	
}

void removeBucket(Hash *hash, Bucket *bucket){
	if((bucket != NULL) && (hash->size != 0)){
		if(bucket == hash->head) {
			hash->head = bucket->next;
			if(hash->head == NULL){
				hash->tail = NULL;
			}else {
				bucket->next->prev = NULL;
			}
		}else{
			bucket->prev->next = bucket->next;
			if(bucket->next == NULL){
				hash->tail = bucket->prev;
			}else {
				bucket->next->prev = bucket->prev;
			}
		}
		free(bucket);
		hash->size--;
	}
}

void findNode(Hash *hash, char* info){
	Bucket *aux;
	aux = hash->head;
	Node *node;
	int i = 0, flag = 0;
	
	while(aux != NULL){
		if(aux->key == ((int)info[0] % 10)){
			node = aux->head;
			printf("%i -> ",aux->key);
			while(node != NULL){
				i++;
				if(strcmp(node->info, info) == 0){
					printf("%iº",i);
					flag = 1;
				}
				node = node->next;
			}
			break;
		}
		aux = aux->next;
	}
	if(flag == 0){
		printf("Não existe!!!");
	}
	
}

void printBucket(Bucket *hash){
	Node *aux;
	aux = hash->head;
	printf(" -> ");
	while(aux != NULL){
		printf(" %s ,",aux->info);
		aux = aux->next;
	}
}

void printHash(Hash *hash){
	Bucket *aux;
	aux = hash->head;
	while(aux != NULL){
		printf("\n %i",aux->key);
		printBucket(aux);
		aux = aux->next;
	}
}

void autoInsert(Hash *hash){
	char name[MAX];
	FILE *file;
	file = fopen("database1.txt", "r");
	if(file == NULL){
		printf("Arquivo nao encontrado.\n");
		system("PAUSE");
	}
	
	while(fgets(name, 100, file) != NULL){
		name[strcspn(name, "\n")] = 0;
		bucketNew(hash,name);
		
	}
	printf("Inserção concluída!!!");
	
	fclose(file);	
}

void menu(){
	Hash *h;
	h = createHash();
	int op;
	char dado[MAX];
	initHash(h);
	
	for(;;){
		system("cls");
		printf("\n\tTABELA HASH\n__________________________\n|[ 1 - Inserir no bucket]|\n|[ 2 - Remover do bucket]|\n|[ 3 - Imprimir         ]|\n|[ 4 - Auto Insercao    ]|\n|[ 5 - Consulta         ]|\n|[ 6 - Sair             ]|\n__________________________\n>");
		scanf("%i", &op);
		if(op == 1){
			printf("coloque o dado:");
			scanf(" %[^\n]", &dado);
			bucketNew(h,dado);
		}
		if(op == 2){
			printf("coloque o dado:");
			scanf(" %[^\n]", &dado);
			bucketDestroy(h, dado);
		}
		if(op == 3){
			printHash(h);
			getch();
		}
		if(op == 4){
			printf("Inserindo do arquivo...\n");
			Sleep(500);
			autoInsert(h);
			getch();
		}
		if(op == 5){
			system("cls");
			printf("coloque o dado:");
			scanf(" %[^\n]", &dado);
			findNode(h,dado);
			getch();
		}
		if(op == 6){
			break;
		}
	}
}

void song(){

	int i = 0;
	for(i=0;i<2;i++){
		Beep(880,500);
		system("color EC");printf("THANKS \n");
		Beep(587.33,1000);
		Beep(698.46,500);
		system("color CE");printf("THANKS \n");
		Beep(880,500);
		system("color EC");printf("THANKS \n");
		Beep(587.33,1000);
		Beep(698.46,500);
		Beep(880,250);
		Beep(1046.50,250);
		Beep(987.77,500);
		system("color CE");printf("THANKS \n");
		Beep(783.99,500);
		Beep(698.46,250);
		Beep(783.99,250);
		system("color EC");printf("THANKS \n");
		Beep(880,500);
		Beep(587.33,500);
		Beep(523.25,250);
		system("color CE");printf("THANKS \n");
		Beep(659.26,250);
		Beep(587.33,750);
	}
}
