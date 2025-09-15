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
// mergeSort(array, 0, tam - 1);
int main() {
    srand(time(NULL));

    int repeticoes = 15; // repetições por caso/tamanho
    double *tempos = malloc(repeticoes * sizeof(double));

    if (!tempos) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Testa para potências de 10 (10^2 até 10^6)
    for (int exp = 0; exp <= 6; exp++) {
        int tam = potencia(10, exp);
        printf("\n===== Testando com n = 10^%d (%d elementos) =====\n", exp, tam);

        int *array = malloc(tam * sizeof(int));
        if (!array) {
            printf("Erro ao alocar array de tamanho %d\n", tam);
            continue;
        }

        // --- Melhor caso (vetor crescente)
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++)
                array[i] = i + 1;

            clock_t inicio = clock();
            mergeSort(array, 0, tam - 1);
            clock_t fim = clock();

            tempos[r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
        printf("\nMelhor caso:\n");
        printf("Media = %.6f s | Mediana = %.6f s | Desvio Padrao = %.6f s\n",
               media(tempos, repeticoes), mediana(tempos, repeticoes), desvioPadrao(tempos, repeticoes));

        // --- Pior caso (vetor decrescente)
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++)
                array[i] = tam - i;

            clock_t inicio = clock();
            mergeSort(array, 0, tam - 1);
            clock_t fim = clock();

            tempos[r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
        printf("\nPior caso:\n");
        printf("Media = %.6f s | Mediana = %.6f s | Desvio Padrao = %.6f s\n",
               media(tempos, repeticoes), mediana(tempos, repeticoes), desvioPadrao(tempos, repeticoes));

        // --- Caso médio (aleatório)
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++)
                array[i] = rand() % tam;

            clock_t inicio = clock();
            mergeSort(array, 0, tam - 1);
            clock_t fim = clock();

            tempos[r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
        printf("\nCaso medio:\n");
        printf("Media = %.6f s | Mediana = %.6f s | Desvio Padrao = %.6f s\n",
               media(tempos, repeticoes), mediana(tempos, repeticoes), desvioPadrao(tempos, repeticoes));

        free(array);
    }

    free(tempos);
    return 0;
}
