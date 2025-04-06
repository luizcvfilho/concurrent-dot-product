
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int main(int argc, char*argv[]){
    float *vetor1;
    float *vetor2;
    float *vetorfinal;
    long int n;
    float elem;
    size_t ret;
    FILE *arquivo;

    if (argc < 2) {
        fprintf(stderr, "Digite: %s <dimensao>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);

    vetor1 = (float *)malloc(sizeof(float) * n);
    vetor2 = (float *)malloc(sizeof(float) * n);
    vetorfinal = (float *)malloc(sizeof(float) * n);
    if (!vetor1 || !vetor2 || !vetorfinal) {
        fprintf(stderr, "Erro de alocao da memoria dos vetores\n");
        return 2;
    }

    srand(time(NULL));
    for (long int i = 0; i < n; i++) {
        elem = (rand() % MAX) / 3.0;
        vetor1[i] = elem;
        elem = (rand() % MAX) / 3.0;
        vetor2[i] = elem;
        vetorfinal[i] = vetor1[i] * vetor2[i];
    }

    arquivo = fopen("arquivo-vetores", "wb");
    if (!arquivo) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 3;
    }
    // escreve a dimensao
    ret = fwrite(&n, sizeof(long int), 1, arquivo);
    // escreve os elementos do vetor
    ret = fwrite(vetor1, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de escrita do vetor 1 no  arquivo\n");
        return 4;
    }
    ret = fwrite(vetor2, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de escrita do vetor 2 no  arquivo\n");
        return 4;
    }
    ret = fwrite(vetorfinal, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de escrita do vetor final no  arquivo\n");
        return 4;
    }

    fclose(arquivo);

    arquivo = fopen("arquivo-vetores", "rb");
    if (!arquivo) {
        fprintf(stderr, "Erro de abertura do arquivo para leitura\n");
        return 5;
    }

    ret = fread(&n, sizeof(long int), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de leitura da dimensão do arquivo\n");
        return 6;
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
    ret = fread(vetorfinal, sizeof(float), n, arquivo);
    if (ret < n) {
        fprintf(stderr, "Erro de leitura do vetor final do arquivo\n");
        return 7;
    }

    fclose(arquivo);

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

    printf("Vetor Final:\n");
    for (long int i = 0; i < n; i++) {
        printf("%.2f ", vetorfinal[i]);
    }
    printf("\n");

    free(vetor1);
    free(vetor2);
    free(vetorfinal);
    return 0;

}