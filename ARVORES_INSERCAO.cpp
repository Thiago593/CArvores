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

int tamanho(No *raiz){
	if (raiz == NULL)
		return 0;
	else
		return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita); // Tamanho à esquerda e à direita
}

int pesquisar (No *raiz, int elemento){
	if(raiz == NULL){ //raiz nula --> árvore vazia
		return -1;
	}
	else{
		if(raiz->conteudo == elemento) 
			return raiz->conteudo;
		else{
			if(elemento<raiz->conteudo) //verificação da árvore à esquerda
				return pesquisar(raiz->esquerda, elemento) ;
			else
				return pesquisar(raiz->direita, elemento); //verificação da árvore à direita
			
		}
	}
}

/* Remoção de nós folhas */
No* remover(No *raiz, int elemento){
	if(raiz == NULL){ //Verifica se a raiz está vazia
	printf("Valor não encontrado\n");
		return NULL;
	}
	else{
		/* Remoção de nós folhas */
		if(raiz->conteudo == elemento){
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				return NULL;
			}
			/* Remoção de nós com direita ou esquerda */
			else{
				if(raiz->esquerda == NULL || raiz->direita == NULL){
					No *aux;
					if(raiz->esquerda != NULL) // Esquerda é nula?
						aux = raiz->esquerda; //Salva o nó a esquerda
					else
						aux = raiz->direita; //Salva o nó a direita
						
					free(raiz); //Remove a raiz
					return aux; //Retorna o endereço salvo 
				}
			/* Remoção de nós com direita e esquerda */
			else{
				No *aux = raiz->esquerda; //Procurar o nó mais a direita da arvore esquerda
				while(aux->direita != NULL){
					aux = aux->direita; //Percorrendo a arvore até a folha
				}
				raiz->conteudo = aux->conteudo;
				aux->conteudo = elemento;
				raiz->esquerda = remover(raiz->esquerda, elemento);
				return raiz;
			}
		}
	}
		else{
			if(elemento < raiz->conteudo)
				raiz->esquerda = remover(raiz->esquerda, elemento);
			else
				raiz->direita = remover(raiz->direita, elemento);
				
			return raiz;
		}
	}
}

No* pesquisarNo (No *raiz, int elemento){
	if(raiz == NULL){ //raiz nula --> árvore vazia
		return NULL;
	}
	else{
		if(raiz->conteudo == elemento) 
			return raiz;
		else{
			if(elemento<raiz->conteudo) //verificação da árvore à esquerda
				return pesquisarNo(raiz->esquerda, elemento) ;
			else
				return pesquisarNo(raiz->direita, elemento); //verificação da árvore à direita
			
		}
	}
}

void exibirarv(No *raiz){
	if(raiz != NULL){
		exibirarv(raiz->esquerda); //todos à esquerda
		printf("%d ", raiz->conteudo); // O nó
		exibirarv(raiz->direita); // Todos à direita
	}
}

print_arvore(No *no, int nivel, char lado) {
    if (no) {
         
        print_arvore(no->esquerda, nivel+1, 'e');
        
        for (int i=0; i<nivel; i++) {
            printf("  ");
        }

        switch (lado) {
            case 'e': printf("\x1b[43m%d\n\x1b[0m", no->conteudo); break;
            case 'd': printf("\x1b[44m%d\n\x1b[0m", no->conteudo); break;
            default: printf("%d\n", no->conteudo); break;
        }
        
        print_arvore(no->direita, nivel+1, 'd');
    }
}

int alturaRaiz(No *raiz){
	if(raiz == NULL || raiz->direita == NULL && raiz->esquerda ==NULL)
			return 0;
	else{
		int esquerda = 1 + alturaRaiz(raiz->esquerda);
		int direita = 1 + alturaRaiz(raiz->direita);
		
		if(esquerda>direita)
			return esquerda;
		else
			return direita;
	}
}

int alturaNo(No *raiz, int elemento){
	No *no = pesquisarNo(raiz, elemento);
	if(no != NULL)
		return alturaRaiz(no);
	else
		return -1;
}

typedef enum{
	Sair, Inserir, Exibir, Pesquisar, Remover, AlturaRaiz, AlturaNo
}Menu; 

int main(){
	setlocale(LC_ALL,"Portuguese");
	int valor;
	Menu menu;
	
	ArvBinaria arvore;
	arvore.raiz = NULL; // sem uso de ponteiros
	
	while(1){	
		printf("\nEscolha uma opção:\n");
		printf("Sair ------------- [0]\n");
		printf("Inserir ---------- [1]\n");
		printf("Exibir ----------- [2]\n"); 
		printf("Pesquisar -------- [3]\n");
		printf("Remover ---------- [4]\n");
		printf("Altura da árvore - [5]\n");
		printf("Altura do Nó ----- [6]\n");
		scanf("%d", &menu);
	
		switch(menu){
		case Sair:
			printf("Fim.");
		return 0;
		break;
		
		case Inserir:
			printf("Digite um número inteiro positivo:");
			scanf("%d", &valor);
			
			while(valor<0){
				printf("Digite um número inteiro positivo:");
				scanf("%d", &valor);
			}
			
			inserir(&arvore, valor);
			system ("cls");
			break;
			
		case Exibir:
			printf("\n");
			exibirarv(arvore.raiz);
			printf("\n\n\n");
			print_arvore(arvore.raiz, 0, 'R');
			
			printf("\nTamanho: %d\n", tamanho(arvore.raiz));
			break;
		
		case Pesquisar:
			printf("Digite o valor a ser buscado na árvore:");
			scanf("%d", &valor);
			if (pesquisar(arvore.raiz, valor) == -1){
				printf("O elemento não existe na árvore\n");
			}
			else
				printf("O elemento existe na árvore\n");
			break;
		
		case Remover:
			printf("Digite um elemento da árvore a ser removido:");
			scanf("%d", &valor);	
			arvore.raiz = remover(arvore.raiz, valor);
			break;
			
		case AlturaRaiz:
			printf("A altura da árvore é: %d\n", alturaRaiz(arvore.raiz));
		break;
		
		case AlturaNo:
			printf("Digite o valor a ser calculada a altura:");
			scanf("%d", &valor);
			if (alturaNo(arvore.raiz, valor) == -1){
				printf("O elemento não existe na árvore\n");
			}
			else
				printf("A altura do nó é: %d\n", alturaNo(arvore.raiz, valor));
		break;
		
		default:
			printf("Escolha inválida!");
		}
	}
}
