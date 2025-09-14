#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Função para trocar os elementos do vetor
void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MaxHeapify(int array[], int n, int i){
    int maior = i; // raiz
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if (esq < n && array[esq] > array[maior])
        maior = esq;

    if (dir < n && array[dir] > array[maior])
        maior = dir;

    if (maior != i){
        Swap(&array[i], &array[maior]);
        MaxHeapify(array, n, maior);
    }
}

void HeapSort(int array[], int n) {
    // Monta max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(array, n, i);

    // Extrai elementos
    for (int i = n - 1; i > 0; i--){
        Swap(&array[0], &array[i]);
        MaxHeapify(array, i, 0);
    }
}

int potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++)
        resultado *= base;
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
    int exp = 10;
    double arrayT[100];
    int tam = potencia(4, exp);

    printf("Tamanho do array = %d\n", tam);

    int *array = malloc(tam * sizeof(int));
    if (!array) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    clock_t inicio, fim;
    int opt;

    printf("1-Melhor Caso\n2-Pior Caso\n3-Caso Medio\n");
    scanf("%d", &opt);

    srand(time(NULL)); // inicializa gerador aleatório

    int count = 0;
    switch(opt){
        case 1:
            printf("Selecionado: Melhor Caso\n");
            count = 0;
            while(count < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = i + 1; // vetor crescente
                }
                inicio = clock();
                HeapSort(array, tam);
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
                HeapSort(array, tam);
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
                    array[i] = rand() % tam; // valores aleatórios
                }
                inicio = clock();
                HeapSort(array, tam);
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
