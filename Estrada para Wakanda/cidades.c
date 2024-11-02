#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CIDADES_H
#define CIDADES_H

typedef struct {
    char Nome[256];
    int Posicao;
} Cidade;

typedef struct {
    int N;
    int T;
    Cidade *C;
} Estrada;

Estrada *getEstrada(const char *nomeArquivo);
double calcularMenorVizinhanca(const char *nomeArquivo);
char *cidadeMenorVizinhanca(const char *nomeArquivo);
void escreverArquivoMenorVizinhanca(const char *nomeArquivoEntrada, const char *nomeArquivoSaida);

#endif

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        printf("Erro na alocação de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &(estrada->T)) != 1 || fscanf(arquivo, "%d", &(estrada->N)) != 1) {
        printf("Erro na leitura dos valores T e N.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (estrada->T <= 3 || estrada->T > 1000000 || estrada->N <= 2 || estrada->N >= 10000) {
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        printf("Erro na alocação de memória para cidades.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(arquivo, "%d %s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2) {
            printf("Erro na leitura da cidade %d.\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            printf("Posição inválida para a cidade %d.\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return estrada;
}

int compararCidades(const void *a, const void *b) {
    Cidade *cidadeA = (Cidade *)a;
    Cidade *cidadeB = (Cidade *)b;
    return cidadeA->Posicao - cidadeB->Posicao;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) return -1;

    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menorVizinhanca = estrada->T;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhancaAtual = estrada->C[i].Posicao - estrada->C[i - 1].Posicao;
        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) return NULL;

    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menorVizinhanca = estrada->T;
    int cidadeIndex = 0;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhancaAtual = estrada->C[i].Posicao - estrada->C[i - 1].Posicao;
        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
            cidadeIndex = i;
        }
    }

    char *cidadeComMenorVizinhanca = strdup(estrada->C[cidadeIndex].Nome);

    free(estrada->C);
    free(estrada);
    return cidadeComMenorVizinhanca;
}

void escreverArquivoMenorVizinhanca(const char *nomeArquivoEntrada, const char *nomeArquivoSaida) {
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivoEntrada);
    char *cidade = cidadeMenorVizinhanca(nomeArquivoEntrada);

    if (cidade == NULL || menorVizinhanca == -1) {
        printf("Erro ao calcular a menor vizinhança ou ao obter a cidade.\n");
        return;
    }

    FILE *arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo de saída: %s\n", nomeArquivoSaida);
        free(cidade);
        return;
    }

    fprintf(arquivoSaida, "Cidade com menor vizinhança: %s\n", cidade);
    fprintf(arquivoSaida, "Menor vizinhança: %.2f\n", menorVizinhanca);

    fclose(arquivoSaida);
    free(cidade);
}

int main () {

    int Soma = 0;
    int NumTeste = 0;

    FILE *Resposta = fopen("Resultado.txt", "w");
    if (Resposta == NULL) {
        printf("Erro ao abrir o arquivo de saída: Resultado.txt\n");
        return 1;
    }

    // Caminho completo para o arquivo
    Estrada *T1 = getEstrada("C:\\Users\\SAMSUNG\\Desktop\\Estudo\\Faculdade\\Segundo Semestre\\Estrutura de Dados\\Estrada para Wakanda\\Arquivos\\entrada.txt");
    double D1 = calcularMenorVizinhanca("C:\\Users\\SAMSUNG\\Desktop\\Estudo\\Faculdade\\Segundo Semestre\\Estrutura de Dados\\Estrada para Wakanda\\Arquivos\\entrada.txt");
    char *C1 = cidadeMenorVizinhanca("C:\\Users\\SAMSUNG\\Desktop\\Estudo\\Faculdade\\Segundo Semestre\\Estrutura de Dados\\Estrada para Wakanda\\Arquivos\\entrada.txt");

    if (T1 == NULL) {
        fprintf(Resposta, "Erro ao carregar a estrada.\n");
        fclose(Resposta);
        return 1;
    }

    if (T1->T == 10) Soma++;
    NumTeste++;

    if (T1->N == 2) Soma++;
    NumTeste++;

    if (D1 == 3.5) Soma++;
    NumTeste++;

    if (strcmp(C1, "Birnin Zana") == 0) Soma++;
    NumTeste++;

printf("Valor de T: %d\n", T1->T);
printf("Valor de N: %d\n", T1->N);
printf("Menor vizinhança calculada (D1): %.2f\n", D1);
printf("Cidade com menor vizinhança (C1): %s\n", C1);

    fprintf(Resposta, "\n\nATENÇÃO: Você acertou %d de %d itens. Logo, em 2.00 pontos, sua nota foi %.2f.\n", Soma, NumTeste, 2.0 * (float)Soma / (float)NumTeste);

    free(C1);
    free(T1->C);
    free(T1);
    fclose(Resposta);
    
    return 0;
}
