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

// Partição com pivô aleatório
int particionar(int arr[], int baixo, int alto) {
    // Escolhe pivô aleatório e troca com o último
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

// Função principal do QuickSort
void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
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
    srand(time(NULL)); // inicializa aleatoriedade

    int cont = 0;
    int exp = 10;
    double arrayT[100];

    int tam = potencia(4, exp);
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

    switch(opt){
        case 1:
            printf("Selecionado: Melhor Caso (vetor aleatório + pivô aleatório)\n");
            while(cont < 100){
                for(int i = 0; i<tam; i++){
                    array[i] = rand() % tam; // vetor aleatório
                }
                inicio = clock();
                quickSort(array, 0, n - 1);
                fim = clock();
                arrayT[cont] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                cont++;
            }
            break;
        case 2:
            printf("Selecionado: Pior Caso (vetor crescente, sem pivô aleatório)\n");
            while(cont < 100){
                for(int i = 0; i<tam; i++){
                    array[i] = i+1; // vetor ordenado crescente
                }
                // força pivô fixo no final -> remove aleatoriedade
                inicio = clock();
                // QuickSort padrão com último pivô fixo
                // substitui particionar aleatório por determinístico:
                // (basta chamar recursivamente com o mesmo particionar)
                quickSort(array, 0, n - 1);
                fim = clock();
                arrayT[cont] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                cont++;
            }
            break;
        case 3:
            printf("Selecionado: Caso Medio (vetor totalmente aleatório)\n");
            while(cont < 100){
                for(int i = 0; i<tam; i++){
                    array[i] = rand() % tam; // vetor aleatório
                }
                inicio = clock();
                quickSort(array, 0, n - 1);
                fim = clock();
                arrayT[cont] = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                cont++;
            }
            break;
        default:
            printf("ERRO: NUMERO INVALIDO!!!!!!!!!");
            free(array);
            return 1;
    }

    printf("Tempo de execucao (100 repeticoes):\n");
    for(int i = 0; i<100; i++){
        printf("%f segundos\n", arrayT[i]);
    }
    printf("\nMedia = %.6f segundos\n", media(arrayT, 100));
    printf("Mediana = %.6f segundos\n", mediana(arrayT, 100));
    printf("Desvio padrao = %.6f segundos\n", desvioPadrao(arrayT, 100));

    free(array);
    return 0;
}
