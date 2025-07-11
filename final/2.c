#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addMatrices(int **a, int **b, int **res, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int **a, int **b, int **res, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            res[i][j] = 0;
            for (int k = 0; k < cols; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
}

int main() {
    int rows, cols;
    printf("Введите количество строк и столбцов: ");
    scanf("%d %d", &rows, &cols);

    int **matrix1 = malloc(rows * sizeof(int*));
    int **matrix2 = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = malloc(cols * sizeof(int));
        matrix2[i] = malloc(cols * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = rand() % 100;
            matrix2[i][j] = rand() % 100;
        }

    FILE *file = fopen("input.txt", "w");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(file, "%d ", matrix1[i][j]);
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(file, "%d ", matrix2[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);

    // Освобождаем и пересоздаём для чистоты
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);

    matrix1 = malloc(rows * sizeof(int*));
    matrix2 = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = malloc(cols * sizeof(int));
        matrix2[i] = malloc(cols * sizeof(int));
    }

    file = fopen("input.txt", "r");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(file, "%d", &matrix1[i][j]);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(file, "%d", &matrix2[i][j]);
    fclose(file);

    int **sum = malloc(rows * sizeof(int*));
    int **product = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        sum[i] = malloc(cols * sizeof(int));
        product[i] = malloc(cols * sizeof(int));
    }

    addMatrices(matrix1, matrix2, sum, rows, cols);
    multiplyMatrices(matrix1, matrix2, product, rows, cols);

    // Поиск минимального элемента и количества нечётных
    int minVal = matrix1[0][0];
    int minIndex = 0;
    int oddCount = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            int val = matrix1[i][j];
            if (val < minVal) {
                minVal = val;
                minIndex = i * cols + j;
            }
            if (val % 2 != 0)
                oddCount++;
        }

    file = fopen("output.txt", "w");

    fprintf(file, "Сумма матриц:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(file, "%d ", sum[i][j]);
        fprintf(file, "\n");
    }

    fprintf(file, "\nПроизведение матриц:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(file, "%d ", product[i][j]);
        fprintf(file, "\n");
    }

    fprintf(file, "\nМинимальный элемент матрицы 1: %d (номер %d)\n", minVal, minIndex);
    fprintf(file, "Количество нечетных чисел в матрице 1: %d\n", oddCount);

    fclose(file);

    // Очистка
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(sum[i]);
        free(product[i]);
    }
    free(matrix1);
    free(matrix2);
    free(sum);
    free(product);

    return 0;
}
