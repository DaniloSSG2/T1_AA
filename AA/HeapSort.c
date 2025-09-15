#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Função para trocar dois elementos
void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Ajusta a heap
void MaxHeapify(int array[], int n, int i) {
    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if (esq < n && array[esq] > array[maior])
        maior = esq;

    if (dir < n && array[dir] > array[maior])
        maior = dir;

    if (maior != i) {
        Swap(&array[i], &array[maior]);
        MaxHeapify(array, n, maior);
    }
}

// Função principal do HeapSort
void HeapSort(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(array, n, i);

    for (int i = n - 1; i > 0; i--) {
        Swap(&array[0], &array[i]);
        MaxHeapify(array, i, 0);
    }
}

// Função potência
int potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++)
        resultado *= base;
    return resultado;
}

// Média
double media(double valores[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += valores[i];
    return soma / n;
}

// Mediana
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

// Desvio padrão
double desvioPadrao(double valores[], int n) {
    double m = media(valores, n);
    double soma = 0.0;
    for (int i = 0; i < n; i++)
        soma += (valores[i] - m) * (valores[i] - m);
    return sqrt(soma / n);
}

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
            HeapSort(array, tam);
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
            HeapSort(array, tam);
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
            HeapSort(array, tam);
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
