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

int isvowel(int c);
int main(int argc, char **argv)
{
   FILE *F; int c, letter, cons, vowel, total=0;
  while ( --argc )
 {
   F=fopen(argv[argc],"r");
    total=letter=cons=vowel=0;
    while ( (c=fgetc(F))!=EOF)
     {
          total++;
          if (isalpha(c))
          { 
           letter++;
           if (isvowel(c)) vowel++;
           else cons++;
          }
     }
      printf("FILE %s: total=%d letters=%d vowels=%d, cons=%d\n",argv[argc],total,letter,vowel,cons);
  }
    return 0;
}

int isvowel(int c)
{
    switch(tolower(c))
    {
        case 'a': 
        case 'e':
        case 'i': 
        case 'o': 
        case 'u':
        case 'y': return 1;
    }
    return 0;
}

void analyze_file() {
    char filename[256] = "exemple.txt";
    char result_filename[256] = "result.txt";
    
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("ERROR!\n");
        return;
    }

    FILE *output_file = fopen(result_filename, "w");
    if (output_file == NULL) {
        printf("ERROR!\n");
        fclose(input_file);
        return;
    }

    int total_chars = 0, lines = 0, digits = 0, punct = 0;
    int spaces = 0, letters = 0, lower = 0, upper = 0;
    int vowels = 0, consonants = 0;

    int c;
    while ((c = fgetc(input_file)) != EOF) {
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

	fprintf(output_file, "Результаты анализа файла:\n");
	fprintf(output_file, "Общее количество символов: %d\n", total_chars);
	fprintf(output_file, "Количество строк: %d\n", lines + 1);
	fprintf(output_file, "Количество цифр: %d\n", digits);
	fprintf(output_file, "Количество знаков препинания: %d\n", punct);
	fprintf(output_file, "Количество пробельных символов: %d\n", spaces);
	fprintf(output_file, "Количество букв: %d\n", letters);
	fprintf(output_file, "  Строчные буквы: %d\n", lower);
	fprintf(output_file, "  Прописные буквы: %d\n", upper);
	fprintf(output_file, "  Гласные буквы: %d\n", vowels);
	fprintf(output_file, "  Согласные буквы: %d\n", consonants)

    fclose(input_file);
    fclose(output_file);

}
