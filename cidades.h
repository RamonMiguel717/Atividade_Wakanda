#ifndef CIDADES_H
#define CIDADES_H

typedef struct {
    char Nome[256];  // Nome da cidade
    int Posicao;     // Posição da cidade
} Cidade;

typedef struct {
    int N;           // Número de cidades
    int T;           // Comprimento da estrada
    Cidade *C;       // Vetor de cidades
} Estrada;

Estrada *getEstrada(const char *nomeArquivo); // Inicializa cidades no TAD indicado acima.
double calcularMenorVizinhanca(const char *nomeArquivo); // Retorna a menor vizinhança.
char *cidadeMenorVizinhanca(const char *nomeArquivo); // Retorna a cidade que tem menor vizinhança.

#endif
// Estrutura de restrições 
Estrada getEstrada(const char *arquivoTeste01.txt){
    FILE *arquivo = fopen(arquivoTeste01,"r");
    if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo\n");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL){
        printf ("Erro na alocacao de memoria. \n");
        fclose (arquivo);
        return 0;
    }

    fscan(arquivo, "%d", &(estrada->T));
    fscan(arquivo, "%d", &(estrada->N));

    if (estrada->T <= 3 || estrada->T > 1000000 || estrada->N  <= 2 || estrada->N >= 10000){
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i=0; i < estrada->N; i++){
        fscanf(arquivo,"%d" "%s", &(estrada->C[i].Posicao),&(estrada->C[i].Nome));

    if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T){
        free(estrada);
        fclose(arquvio);
        return NULL;
    }
    for (int i = 0; i <estrada->N;i++){
        while (estrada.T)
        {
            /* code */
        }
        
    }


    }
    return estrada;
}

void calcularMenorVizinhanca(const char *nomeArquvio){
    for (int i = 0; i<=)
}