/* ARVORE BINÁRIA */

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

//Usando typedef para melhorar a leitura
typedef struct no{
	int conteudo;
	struct no *esquerda, *direita;
}No;

typedef struct{
	No *raiz;
}ArvBinaria;

void inserirDireita(No *no, int valor);
	
void inserirEsquerda(No *no, int valor){
	if(no->esquerda == NULL){
		No *Novo = (No*)malloc(sizeof(No)); //alocação dinâmica na memória heap
		Novo->conteudo = valor; //Novo nó recebe o valor
		Novo->esquerda = NULL; //direita e esquerda nulos
		Novo->direita = NULL;
		no->esquerda = Novo; //inserção à esquerda
	}
	else{ //verificação de qual sub-arvore o valor irá ser salvo
		if(valor < no->esquerda->conteudo) // Menor --> Esquerda do nó esquerdo
			inserirEsquerda(no->esquerda, valor);
		if(valor > no->esquerda->conteudo) // Impede repetição
			inserirDireita(no->esquerda, valor); // Maior --> Direita do nó esquerdo
	}
}

void inserirDireita(No *no, int valor){
	if(no->direita == NULL){
		No *Novo = (No*)malloc(sizeof(No)); //alocação dinâmica na memória heap
		Novo->conteudo = valor; //Novo nó recebe o valor
		Novo->esquerda = NULL; //direita e esquerda nulos
		Novo->direita = NULL;
		no->direita = Novo; //inserção à direita
	}
	else{
		if(valor > no->direita->conteudo) // Maior --> Direita do nó direito
			inserirDireita(no->direita, valor);
		if(valor < no->direita->conteudo)
			inserirEsquerda(no->direita, valor); // Menor --> Esquerda do nó direito
	}
}

void inserir(ArvBinaria *arvore, int valor){ 
	if(arvore->raiz == NULL){ //Raiz Nula (Primeira inserção)
		No *Novo = (No*)malloc(sizeof(No)); //alocação dinâmica na memória heap
		Novo->conteudo = valor; //Novo nó recebe o valor
		Novo->esquerda = NULL; //direita e esquerda nulos
		Novo->direita = NULL;
		arvore->raiz = Novo; // Raiz passa a ser o valor do primeiro nó
	}
	else{
		if(valor < arvore->raiz->conteudo)
			inserirEsquerda(arvore->raiz, valor); //inserção à esquerda
		if(valor > arvore->raiz->conteudo)
			inserirDireita(arvore->raiz, valor); // inserção à direita
	}
}

void exibirarv(No *raiz){
	if(raiz != NULL){
		exibirarv(raiz->esquerda); //todos à esquerda
		printf(" %d ", raiz->conteudo); // O nó
		exibirarv(raiz->direita); // Todos à direita
	}
}

typedef enum{
	Sair, Inserir, Exibir
}Menu; 

int main(){
	setlocale(LC_ALL,"Portuguese");
	int valor;
	Menu menu;
	
	ArvBinaria arvore;
	arvore.raiz = NULL; // sem uso de ponteiros
	
	while(1){	
		printf("Escolha uma opção:\n");
		printf("Sair    [0]\n");
		printf("Inserir [1]\n");
		printf("Exibir  [2]\n");
		scanf("%d", &menu);
	
		switch(menu){
		case Sair:
			printf("Fim.");
		return 0;
		break;
		
		case Inserir:
			printf("Digite um número inteiro:");
			scanf("%d", &valor);
			inserir(&arvore, valor);
			system ("cls");
			break;
			
		case Exibir:
			printf("\n");
			exibirarv(arvore.raiz);
			break;
			
		default:
			printf("Escolha inválida!");
		}
	}
}
