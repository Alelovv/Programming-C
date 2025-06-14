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

int hasEqualInRowOrCol(int **matrix, int rows, int cols) {
    // Проверка по строкам
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = j + 1; k < cols; k++)
                if (matrix[i][j] == matrix[i][k])
                    return 1;

    // Проверка по столбцам
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            for (int k = i + 1; k < rows; k++)
                if (matrix[i][j] == matrix[k][j])
                    return 1;

    return 0;
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
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
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

    // Очистка и повторное чтение
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

    int flag1 = hasEqualInRowOrCol(matrix1, rows, cols);
    int flag2 = hasEqualInRowOrCol(matrix2, rows, cols);

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

    if (flag1)
        fprintf(file, "\nВ матрице 1 есть строка или столбец с одинаковыми числами.\n");
    if (flag2)
        fprintf(file, "В матрице 2 есть строка или столбец с одинаковыми числами.\n");
    if (!flag1 && !flag2)
        fprintf(file, "В обеих матрицах нет одинаковых чисел по строкам или столбцам.\n");

    fclose(file);

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
