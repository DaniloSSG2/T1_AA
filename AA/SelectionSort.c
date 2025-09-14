#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// Função para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função principal do Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indice_min = i; // assume que o menor está na posição i

        // procura o menor elemento no restante do vetor
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indice_min]) {
                indice_min = j;
            }
        }

        // troca o menor encontrado com o primeiro elemento da parte não ordenada
        if (indice_min != i) {
            trocar(&arr[i], &arr[indice_min]);
        }
    }
}

int potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }
    return resultado;
}
// Função para calcular a média
double media(double valores[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += valores[i];
    return soma / n;
}

// Função para calcular a mediana
double mediana(double valores[], int n) {
    // cria uma cópia para não bagunçar o array original
    double *copia = malloc(n * sizeof(double));
    if (!copia) return -1;

    for (int i = 0; i < n; i++) copia[i] = valores[i];

    // ordena a cópia (insertion sort simples para n=100)
    for (int i = 1; i < n; i++) {
        double chave = copia[i];
        int j = i - 1;
        while (j >= 0 && copia[j] > chave) {
            copia[j + 1] = copia[j];
            j--;
        }
        copia[j + 1] = chave;
    }

    double med;
    if (n % 2 == 0)
        med = (copia[n/2 - 1] + copia[n/2]) / 2.0;
    else
        med = copia[n/2];

    free(copia);
    return med;
}

// Função para calcular desvio padrão
double desvioPadrao(double valores[], int n) {
    double m = media(valores, n);
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += (valores[i] - m) * (valores[i] - m);
    return sqrt(soma / n);
}
// Exemplo de uso
int main() {
    int count = 0;
    int exp = 5;
    double arrayT[100];
    //double resultado = pow(base, exp);
    int tam = potencia(10, exp);
    printf("tamanho do array = %d\n", tam);
    int *array = malloc(tam * sizeof(int));
    if (!array) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    int n = tam;
    clock_t inicio, fim;

    int opt;
    printf("1-Melhor Caso\n2-Pior Caso\n3-Caso Medio\n");
    scanf("%d", &opt);
    srand(time(NULL)); // inicializa gerador de números aleatórios

    switch(opt){
        case 1:
            printf("Selecionado: Melhor Caso\n");
            count = 0;
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = i + 1; // vetor crescente
                }
                inicio = clock();
                selectionSort(array, n);
                fim = clock();

                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        case 2:
            printf("Selecionado: Pior Caso\n");
            count = 0;
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = tam - i; // vetor decrescente
                }
                inicio = clock();
                selectionSort(array, n);
                fim = clock();

                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        case 3:
            printf("Selecionado: Caso Medio\n");
            count = 0;
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = rand() % tam; // aleatórios
                }
                inicio = clock();
                selectionSort(array, n);
                fim = clock();

                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        default:
            printf("ERRO: NUMERO INVALIDO!!!!!!!!!\n");
            break;
    }

    printf("Tempos de execucao (100 repeticoes):\n");
    for (int i = 0; i < 100; i++) {
        printf("%f segundos\n", arrayT[i]);
    }
    printf("\nMedia = %.6f segundos\n", media(arrayT, 100));
    printf("Mediana = %.6f segundos\n", mediana(arrayT, 100));
    printf("Desvio padrao = %.6f segundos\n", desvioPadrao(arrayT, 100));

    free(array);
return 0;
}