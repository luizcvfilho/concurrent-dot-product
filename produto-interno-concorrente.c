#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

long int n;
float *vetor1;
float *vetor2;
long int T;

void *ProdutoThread(void *tid){
    long int id = (long int) tid;
    long int start, fim, bloco;
    double *produto;

    bloco = n/T;
    start = id*bloco;
    fim = (id == T - 1) ? n : start + bloco;

    produto = (double *)malloc(sizeof(double));
    if (!produto) {
        fprintf(stderr, "Erro de alocacao da memoria do produto\n");
        pthread_exit(NULL);
    }

    *produto = 0.0;
    for (long int i = start; i < fim; i++) {
        *produto += vetor1[i] * vetor2[i];
    }

    printf("Thread %ld encerrada: produto parcial = %lf\n", id, *produto);
    pthread_exit((void *) produto);
}

int main(int argc, char*argv[]){
    char *nome_arquivo;
    FILE *arquivo;
    double valor_calculado;
    double valor_final_arquivo;
    double erro_relativo;
    size_t ret;
    pthread_t *vetor_tid;

    if (argc < 3) {
        fprintf(stderr, "Digite: %s <numero de threads> <nome do arquivo>\n", argv[0]);
        return 1;
    }

    
    T = atoi(argv[1]);
    nome_arquivo = argv[2];
    arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        fprintf(stderr, "Erro de abertura do arquivo para leitura\n");
        return 5;
    }
    
    ret = fread(&n, sizeof(long int), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de leitura da dimensão do arquivo\n");
        return 6;
    }

    if (T > n) T = n;
    vetor1 = (float *)malloc(sizeof(float) * n);
    vetor2 = (float *)malloc(sizeof(float) * n);

    if (!vetor1 || !vetor2) {
        fprintf(stderr, "Erro de alocao da memoria dos vetores\n");
        return 2;
    }
    
    ret = fread(vetor1, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de leitura do vetor 1 do arquivo\n");
        return 7;
    }

    ret = fread(vetor2, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de leitura do vetor 2 do arquivo\n");
        return 7;
    }

    ret = fread(&valor_final_arquivo, sizeof(double), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de leitura do vetor final do arquivo\n");
        return 7;
    }

    fclose(arquivo);
    vetor_tid = (pthread_t *) malloc(T * sizeof(pthread_t));
    if (vetor_tid == NULL) {
        fprintf(stderr, "Erro de alocacao do vetor de threads\n");
        return 8;
    }

    for (long int i = 0; i < T; i++) {
        if (pthread_create(&vetor_tid[i], NULL, ProdutoThread, (void *)i)) {
            fprintf(stderr, "Erro de criacao da thread %ld\n", i);
            return 9;
        }
    }

    valor_calculado = 0.0;
    for (long int i = 0; i < T; i++) {
        void *produto;
        if (pthread_join(vetor_tid[i], (void *)&produto)) {
            fprintf(stderr, "Erro de join da thread %ld\n", i);
            return 10;
        }
        valor_calculado += *(double *)produto;
        free(produto);
    }

    printf("Vetores lidos do arquivo: \n");
    printf("Vetor 1:\n");
    for (long int i = 0; i < n; i++) {
        printf("%.2f ", vetor1[i]);
    }
    printf("\n");

    printf("Vetor 2:\n");
    for (long int i = 0; i < n; i++) {
        printf("%.2f ", vetor2[i]);
    }
    printf("\n");

    erro_relativo = (valor_final_arquivo - valor_calculado) / valor_final_arquivo;
    printf("Produto interno concorrente: %lf\n", valor_calculado);
    printf("Produto interno sequencial: %lf\n", valor_final_arquivo);
    printf("Erro relativo: %lf\n", erro_relativo);

    free(vetor1);
    free(vetor2);
    free(vetor_tid);
    return 0;
}