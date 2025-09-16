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

// --- Particionamentos ---
// Pior caso (pivô = último elemento)
int particionarPior(int arr[], int baixo, int alto) {
    int pivo = arr[alto];
    int i = baixo - 1;
    for (int j = baixo; j < alto; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

// Melhor caso (pivô = elemento do meio)
int particionarMelhor(int arr[], int baixo, int alto) {
    int meio = (baixo + alto) / 2;
    trocar(&arr[meio], &arr[alto]);
    int pivo = arr[alto];
    int i = baixo - 1;
    for (int j = baixo; j < alto; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

// Caso médio (pivô aleatório)
int particionarMedio(int arr[], int baixo, int alto) {
    int indicePivo = baixo + rand() % (alto - baixo + 1);
    trocar(&arr[indicePivo], &arr[alto]);
    int pivo = arr[alto];
    int i = baixo - 1;
    for (int j = baixo; j < alto; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    return i + 1;
}

// --- Funções QuickSort ---
void quickSort(int arr[], int baixo, int alto, int (*particionar)(int[], int, int)) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1, particionar);
        quickSort(arr, pi + 1, alto, particionar);
    }
}

// Função potência
int potencia(int base, int exp) {
    int resultado = 1;
    for (int i = 0; i < exp; i++) resultado *= base;
    return resultado;
}

// Média
double media(double valores[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n; i++) soma += valores[i];
    return soma / n;
}

// Mediana
double mediana(double valores[], int n) {
    double *copia = malloc(n * sizeof(double));
    if (!copia) return -1;
    for (int i = 0; i < n; i++) copia[i] = valores[i];

    // insertion sort simples
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
    if (n % 2 == 0) med = (copia[n/2 - 1] + copia[n/2]) / 2.0;
    else med = copia[n/2];

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

    // Testa para potências de 10 (10^0 até 10^6)
    for (int exp = 0; exp <= 6; exp++) {
        int tam = potencia(10, exp);
        printf("\n===== Testando com n = 10^%d (%d elementos) =====\n", exp, tam);

        int *array = malloc(tam * sizeof(int));
        if (!array) {
            printf("Erro ao alocar array de tamanho %d\n", tam);
            continue;
        }

        // --- Melhor caso ---
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++) array[i] = i + 1;

            clock_t inicio = clock();
            quickSort(array, 0, tam - 1, particionarMelhor);
            clock_t fim = clock();

            tempos[r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
        printf("\nMelhor caso:\n");
        printf("Media = %.6f s | Mediana = %.6f s | Desvio Padrao = %.6f s\n",
               media(tempos, repeticoes), mediana(tempos, repeticoes), desvioPadrao(tempos, repeticoes));

        // --- Pior caso ---
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++) array[i] = i + 1; // vetor crescente (ruim p/ pivô = último)

            clock_t inicio = clock();
            quickSort(array, 0, tam - 1, particionarPior);
            clock_t fim = clock();

            tempos[r] = (double)(fim - inicio) / CLOCKS_PER_SEC;
        }
        printf("\nPior caso:\n");
        printf("Media = %.6f s | Mediana = %.6f s | Desvio Padrao = %.6f s\n",
               media(tempos, repeticoes), mediana(tempos, repeticoes), desvioPadrao(tempos, repeticoes));

        // --- Caso médio ---
        for (int r = 0; r < repeticoes; r++) {
            for (int i = 0; i < tam; i++) array[i] = rand() % tam;

            clock_t inicio = clock();
            quickSort(array, 0, tam - 1, particionarMedio);
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
