#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Função para mesclar duas metades de um vetor
void merge(int arr[], int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;  
    int n2 = direita - meio;       

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função principal do MergeSort
void mergeSort(int arr[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(arr, esquerda, meio);
        mergeSort(arr, meio + 1, direita);

        merge(arr, esquerda, meio, direita);
    }
}

int potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }
    return resultado;
}

double media(double valores[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += valores[i];
    return soma / n;
}

double mediana(double valores[], int n) {
    double *copia = malloc(n * sizeof(double));
    if (!copia) return -1;

    for (int i = 0; i < n; i++) copia[i] = valores[i];

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

double desvioPadrao(double valores[], int n) {
    double m = media(valores, n);
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += (valores[i] - m) * (valores[i] - m);
    return sqrt(soma / n);
}

int main() {
    srand(time(NULL)); // garante aleatoriedade

    int cont = 0;
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

    switch(opt){
        case 1:
            printf("Selecionado: Melhor Caso\n");
            while(cont < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = i+1; // crescente
                }
                inicio = clock();
                mergeSort(array, 0, tam - 1);
                fim = clock();
                arrayT[cont++] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            }
            break;

        case 2:
            printf("Selecionado: Pior Caso\n");
            while(cont < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = tam - i; // decrescente
                }
                inicio = clock();
                mergeSort(array, 0, tam - 1);
                fim = clock();
                arrayT[cont++] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            }
            break;

        case 3:
            printf("Selecionado: Caso Medio\n");
            while(cont < 100){
                for(int i = 0; i < tam; i++){
                    array[i] = rand() % tam; // aleatório proporcional ao tamanho
                }
                inicio = clock();
                mergeSort(array, 0, tam - 1);
                fim = clock();
                arrayT[cont++] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            }
            break;

        default:
            printf("ERRO: NUMERO INVALIDO!!!!!!!!!\n");
            free(array);
            return 1;
    }

    printf("Tempos de execucao (100 repeticoes):\n");
    for(int i = 0; i < 100; i++){
        printf("%f segundos\n", arrayT[i]);
    }
    printf("\nMedia = %.6f segundos\n", media(arrayT, 100));
    printf("Mediana = %.6f segundos\n", mediana(arrayT, 100));
    printf("Desvio padrao = %.6f segundos\n", desvioPadrao(arrayT, 100));

    free(array);
    return 0;
}
