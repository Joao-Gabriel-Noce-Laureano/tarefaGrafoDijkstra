#include <stdio.h>
#include <stdlib.h>

typedef struct grafo {
    int numVertices;
    int **matGraph;
} GRAFO;

//Função para criar grafo
GRAFO* criaGrafo(int numVertices)
{
	int i, j;
	GRAFO* graph = (GRAFO *) malloc(sizeof(GRAFO));
	graph->numVertices = numVertices;
	
	graph->matGraph = (int **)malloc(graph->numVertices * sizeof(int*)); 
	for(i = 0; i < graph->numVertices; i++) graph->matGraph[i] = (int*) malloc(graph->numVertices * sizeof(int));
	
	for (i = 0; i < graph->numVertices; i++) {
        for (j = 0; j < graph->numVertices; j++) {
            graph->matGraph[i][j] = 0;
        }
    }
	
	return graph;
}

void insereGrafo(GRAFO* graph, int ini, int fim,int peso)
{
	if(ini >= 0 && ini < graph->numVertices && fim >= 0 && fim < graph->numVertices)  graph->matGraph[ini][fim] = peso;
}



// Função para imprimir a matriz do grafo
void imprimeMatriz(GRAFO* graph) {
    int i, j;
    printf("Matriz do Grafo:\n");
	
    for (i = 0; i < graph->numVertices; i++) {
    	printf("[ ");
        for (j = 0; j < graph->numVertices; j++) {
            printf("%d ",graph->matGraph[i][j]);
        }
        printf("]\n");
    }
}

//Função para achar o menor caminho entre dois vértices
int menorCaminho(GRAFO* graph,int ini, int fim)
{
	if(ini < 0 || ini > graph->numVertices -1)
	{
		printf("Vertice inicial nao existente!\n");
		return -1;
	} 
	
	int i, j, k; //variáveis auxiliares
	
	int **menorCaminhoAtual = (int **)malloc(graph->numVertices * sizeof(int*)); //Matriz que guarda o percurso do menor caminho para cada vértice
	for(i = 0; i < graph->numVertices; i++) menorCaminhoAtual[i] = (int*) malloc(graph->numVertices * sizeof(int));
	for (i = 0; i < graph->numVertices; i++) {
        for (j = 0; j < graph->numVertices; j++) {
            menorCaminhoAtual[i][j] = -1; 
        }
    }
	
	int *verticesConcluidos = (int*) malloc(graph->numVertices*sizeof(int)); //Vertices que todos os vizinhos já foram observados
	int *menorVal = (int*) malloc(graph->numVertices*sizeof(int)); //Valor do menor caminho para cada vértice
	for (i = 0; i < graph->numVertices; i++) {
		verticesConcluidos[i] = 0; //0 = false ; 1 = true
		menorVal[i] = 3000000; //valor alto (infinito)
	}
	
	
	int atual = ini; //começa no inicio
	menorVal[ini] = 0;
	menorCaminhoAtual[ini][0] = ini;
	
	while(atual != -1 && atual != fim)
	{
		
		for (i = 0; i < graph->numVertices; i++) { //percorre os vizinhos do vertice atual atualizando o menor caminho dos vizinhos se necessário
    		if(graph->matGraph[atual][i] != 0 && menorVal[i] > menorVal[atual] + graph->matGraph[atual][i])
			{
				
				menorVal[i] = menorVal[atual] + graph->matGraph[atual][i];
				
				for (j = 0; j < graph->numVertices; j++) menorCaminhoAtual[i][j] = menorCaminhoAtual[atual][j];
				
				for (j = 0; j < graph->numVertices; j++)
				{
					if(menorCaminhoAtual[i][j] == -1)
					{
						menorCaminhoAtual[i][j] = i;
						break;
					}
				}

				
			} 
    	} 
    	
    	verticesConcluidos[atual] = 1; //define o vertice atual como concluido
    	
    	int menor = -1;
    	for (i = 0; i < graph->numVertices; i++) { //procura o próximo vértice (aquele com menor valor para chegar até ele)
    		if(graph->matGraph[atual][i] != 0 && verticesConcluidos[i] == 0 && menorVal[menor] > menorVal[i])
			{
				menor = i;
				
			} 
    	}
    	atual = menor;
    	
	}
    if(atual != -1)
	{
		printf("Menor caminho entre %d e %d: %d\n",ini, fim,menorVal[fim]);
		printf("Percurso do menor caminho: ");
		for (i = 0; menorCaminhoAtual[fim][i] != -1; i++) printf("%d ",menorCaminhoAtual[fim][i]);
		printf("\n");
		return menorVal[fim];
	} 
    else printf("Vertice final nao encontrado!\n");
}


int main() {
	int i,j;
	
	
	int matr [6][6] = {
	{0, 1, 4, 0, 0, 0},
	{1, 0, 4, 2, 7, 0},
	{4, 4, 0, 3, 5, 0},
	{0, 2, 3, 0, 4, 6},
	{0, 7, 5, 4, 0, 7},
	{0, 0, 0, 6, 7, 0}
	};
	
	GRAFO* graph = criaGrafo(6);
	
	for (i = 0; i < graph->numVertices; i++) {
        for (j = 0; j < graph->numVertices; j++) {
            insereGrafo(graph, i, j,matr [i][j]);
        }
    }
	
	

	
	imprimeMatriz(graph);
	printf("\n");
	menorCaminho(graph,0, 4);
    return 0;
}
