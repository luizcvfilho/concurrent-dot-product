
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

// Uncomment if you want to see the vector values
// #define VECTORS

int main(int argc, char*argv[]){
    float *vetor1;
    float *vetor2;
    double resultado = 0.0;
    long int n;
    float elem;
    size_t ret;
    FILE *arquivo;

    if (argc < 3) {
        fprintf(stderr, "Digite: %s <dimensao> <nome do arquivo gerado>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);

    vetor1 = (float *)malloc(sizeof(float) * n);
    vetor2 = (float *)malloc(sizeof(float) * n);
    if (!vetor1 || !vetor2) {
        fprintf(stderr, "Erro de alocao da memoria dos vetores\n");
        return 2;
    }

    srand(time(NULL));
    for (long int i = 0; i < n; i++) {
        elem = ((double)rand() / RAND_MAX) * MAX - (MAX / 2.0);
        vetor1[i] = elem;
        
        elem = ((double)rand() / RAND_MAX) * MAX - (MAX / 2.0);
        vetor2[i] = elem;

        resultado += vetor1[i] * vetor2[i];
    }

    arquivo = fopen(argv[2], "wb");

    if (!arquivo) {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 3;
    }

    ret = fwrite(&n, sizeof(long int), 1, arquivo);

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
    ret = fwrite(&resultado, sizeof(double), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de escrita do resultado final no  arquivo\n");
        return 4;
    }

    fclose(arquivo);

    arquivo = fopen(argv[2], "rb");
    if (!arquivo) {
        fprintf(stderr, "Erro de abertura do arquivo para leitura\n");
        return 5;
    }

    ret = fread(&n, sizeof(long int), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de leitura da dimensão do arquivo\n");
        return 6;
    }

    printf("Vetores de dimensão %ld\n", n);

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
    ret = fread(&resultado, sizeof(double), 1, arquivo);
    if (ret < 1) {
        fprintf(stderr, "Erro de leitura do resultado final do arquivo\n");
        return 7;
    }

    fclose(arquivo);

    #ifdef VECTORS
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
    #endif

    printf("Resultado Final:\n %f", resultado);
    printf("\n");

    free(vetor1);
    free(vetor2);
    return 0;

}