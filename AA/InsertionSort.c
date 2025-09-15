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
//insertionSort(array, tam);

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
            insertionSort(array, tam);
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
            insertionSort(array, tam);
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
            insertionSort(array, tam);
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
