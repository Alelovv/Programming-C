#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int matrix1[2][2], matrix2[2][2], result[2][2];
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            fscanf(input, "%d", &matrix1[i][j]);
        }
    }
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            fscanf(input, "%d", &matrix2[i][j]);
        }
    }
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            fprintf(output, "%d ", result[i][j]);
        }
        fprintf(output, "\n");
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}