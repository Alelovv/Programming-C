#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

bool is_consonant(char c) {
    c = tolower(c);
    return isalpha(c) && !is_vowel(c);
}

int main() {
    char filename[256];
    printf("Введите имя файла: ");
    scanf("%255s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int total_chars = 0;
    int lines = 0;
    int digits = 0;
    int punct = 0;
    int spaces = 0;
    int letters = 0;
    int lower = 0;
    int upper = 0;
    int vowels = 0;
    int consonants = 0;

    int c;
    while ((c = fgetc(file)) != EOF) {

        if (c == EOF) break;
        
        total_chars++;
        
        if (c == '\n') lines++;
        if (isdigit(c)) digits++;
        if (ispunct(c)) punct++;
        if (isspace(c)) spaces++;
        if (isalpha(c)) {
            letters++;
            if (islower(c)) lower++;
            if (isupper(c)) upper++;
            if (is_vowel(c)) vowels++;
            if (is_consonant(c)) consonants++;
        }
    }

    fclose(file);

    printf("Результаты анализа файла '%s':\n", filename);
    printf("Общее количество символов: %d\n", total_chars);
    printf("Количество строк: %d\n", lines + 1); 
    printf("Количество цифр: %d\n", digits);
    printf("Количество знаков препинания: %d\n", punct);
    printf("Количество пробельных символов: %d\n", spaces);
    printf("Количество букв: %d\n", letters);
    printf("  из них строчных: %d\n", lower);
    printf("  из них прописных: %d\n", upper);
    printf("  из них гласных: %d\n", vowels);
    printf("  из них согласных: %d\n", consonants);

    return 0;
}
