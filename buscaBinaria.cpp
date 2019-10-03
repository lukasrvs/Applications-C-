#include <stdio.h>
#include <stdlib.h>

int buscaBinaria(int tamanho, int *v, int numero){
	
	int inicio = 0;
	int final = tamanho - 1;
	int meio; // guarda a metade do vetor
	
	while(inicio <= final){  //enquanto o valor inicio for menor igual o fim 
		// possa encontrar o elemento caso contrario nao tem o número
		
		meio = (inicio + final) / 2;
		
		
		if(numero < v[meio]){ // número for menor que a metade do vetor, ta na primeira metade
		
			final = meio - 1;
			
		}else if(numero > v[meio]){

			inicio = meio + 1; // número esta na segunda metade
			
		}else return meio;
	
	}return -1; // número não encontrado
}

int main(){
	
	int vetor[] = {1,3,5,7,9,11,13,15,17,19,21,23,25};
	int chave;
	int tamanho = sizeof(vetor)/sizeof(int);
	
	printf("Defina a chave de busca:");
	scanf("%i",&chave);
	
	if(buscaBinaria(tamanho, vetor, chave) != -1){
	printf("Tamanho vetor: %i \nchave busca: %i \nposicao: %d \n", tamanho,chave,buscaBinaria(tamanho, vetor, chave));
	}else{
		printf("chave busca nao encontrado");
	}
}
