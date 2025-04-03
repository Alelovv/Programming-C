#include <stdio.h>
#include <ctype.h>
int isvowel(int c);
int main(int argc, char **argv)
{
   FILE *F; int c, letter, cons, vowel, total=0;
   int lines = 0,
    digits = 0,
    punct = 0,
    spaces = 0,
    lowercase = 0,
    uppercase = 0;
    
   char filename[256];

   printf("Enter filename: ");
   scanf(" %255s", filename);

   F = fopen(filename, "r");
   if (F == NULL) {
       printf("Error: Could not open file %s\n", filename);
       return 1;
   }


   total = letter = cons = vowel = lines = digits = punct = spaces = lowercase = uppercase = 0;
   rewind(F);
   while ((c = fgetc(F)) != EOF)
   {
       total++;
       if (c == '\n') lines++;
       if (isdigit(c)) digits++;
       if (ispunct(c)) punct++;
       if (isspace(c)) spaces++;
       if (isalpha(c)) {
           letter++;
           if (islower(c)) lowercase++;
           if (isupper(c)) uppercase++;
           if (isvowel(c)) vowel++;
           else cons++;
       }
   }

   printf("FILE %s:\n", filename);
   printf("Total characters: %d\n", total);
   printf("Lines: %d\n", lines);
   printf("Digits: %d\n", digits);
   printf("Punctuation marks: %d\n", punct);
   printf("Whitespace characters: %d\n", spaces);
   printf("Letters: %d\n", letter);
   printf("Lowercase: %d\n", lowercase);
   printf("Uppercase: %d\n", uppercase);
   printf("Vowels: %d\n", vowel);
   printf("Consonants: %d\n", cons);

   fclose(F);
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