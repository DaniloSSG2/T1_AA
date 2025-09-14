#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Função principal do Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

// Função para calcular potência (base^exp)
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
    double *copia = malloc(n * sizeof(double));
    if (!copia) return -1;

    for (int i = 0; i < n; i++) copia[i] = valores[i];

    // insertion sort na cópia
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

int main() {
    srand(time(NULL)); // garante números aleatórios diferentes a cada execução

    int count = 0;
    int exp = 6; // cuidado com valores grandes
    double arrayT[100];

    int tam = potencia(10, exp);
    printf("Tamanho do array = %d\n", tam);

    int *array = malloc(tam * sizeof(int));
    if (!array) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    clock_t inicio, fim;
    int opt;
    printf("1-Melhor Caso\n2-Pior Caso\n3-Caso Medio\n");
    scanf("%d", &opt);

    switch(opt){
        case 1:
            printf("Selecionado: Melhor Caso\n");
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = i+1; // crescente
                }
                inicio = clock();
                insertionSort(array, tam);
                fim = clock();
                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        case 2:
            printf("Selecionado: Pior Caso\n");
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = tam - i; // decrescente
                }
                inicio = clock();
                insertionSort(array, tam);
                fim = clock();
                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        case 3:
            printf("Selecionado: Caso Medio\n");
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = rand() % tam; // valores aleatórios
                }
                inicio = clock();
                insertionSort(array, tam);
                fim = clock();
                arrayT[count] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                count++;
            }
            break;

        default:
            printf("ERRO: NUMERO INVALIDO!!!!!!!!!\n");
            free(array);
            return 1;
    }

    // Exibe os resultados
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
