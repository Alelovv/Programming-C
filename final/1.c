#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int rows, cols;
    printf("Введите количество строк и столбцов: ");
    scanf("%d %d", &rows, &cols);

    // Выделяем память под матрицы
    int **matrix1 = malloc(rows * sizeof(int*));
    int **matrix2 = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = malloc(cols * sizeof(int));
        matrix2[i] = malloc(cols * sizeof(int));
    }

    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Заполняем матрицы случайными числами
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = rand() % 100;
            matrix2[i][j] = rand() % 100;
        }
    }

    // Запись в файл
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    fprintf(file, "Матрица 1:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix1[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nМатрица 2:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix2[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file); // Закрываем файл

    // Очищаем память
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);

    return 0;
}
