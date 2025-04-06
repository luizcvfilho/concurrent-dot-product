# Lab2 - Programação Concorrente

Este repositório contém dois arquivos `.c` desenvolvidos para o laboratório 2 da disciplina de Programação Concorrente.

## Arquivos

1. **gerador-vetores.c**: 
Gera dois vetores de tamanho N definidos na execução do programa e faz o produto interno entre eles, escrevendo o resultado em um arquivo binário.

2. **produto-interno-concorrente.c**:
Faz o produto interno de dois vetorews presentes em um arquivo binário utilizando threads, após isso compara o valor adquirido com o valor presente no arquivo e calcula o erro relativo.

## Como Compilar

Para compilar os arquivos, utilize o `gcc` no terminal. Execute os seguintes comandos:

```bash
gcc -o gerador-vetores gerador-vetores.c -Wall
gcc -o produto-interno-concorrente produto-interno-concorrente.c -Wall
```

## Como Executar

Após a compilação, execute os programas com os comandos abaixo:

### Executar `gerador-vetores.c`:
N = quantidade de números gerados em cada vetor
```bash
./gerador-vetores N
```

### Executar `arquivo2.c`:
T = número de threads a serem usadas
nome-arquivo = nome do arquivo binário que vai importar os valores
```bash
./arquivo2 T nome-arquivo
```

## Observações
- Verifique se todos os arquivos necessários estão no mesmo diretório.

