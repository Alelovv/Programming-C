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
    printf("������� ��� �����: ");
    scanf("%255s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("������ �������� �����");
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

    printf("���������� ������� ����� '%s':\n", filename);
    printf("����� ���������� ��������: %d\n", total_chars);
    printf("���������� �����: %d\n", lines + 1); 
    printf("���������� ����: %d\n", digits);
    printf("���������� ������ ����������: %d\n", punct);
    printf("���������� ���������� ��������: %d\n", spaces);
    printf("���������� ����: %d\n", letters);
    printf("  �� ��� ��������: %d\n", lower);
    printf("  �� ��� ���������: %d\n", upper);
    printf("  �� ��� �������: %d\n", vowels);
    printf("  �� ��� ���������: %d\n", consonants);

    return 0;
}
