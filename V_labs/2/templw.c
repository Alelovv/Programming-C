#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ����� ��� ��� ���������� ����������
typedef struct word {
    int count;
    char* Word;
} WORD;

int cmpword_alpha(WORD*, WORD*);
int cmpword_quant(WORD*, WORD*);

WORD* words[100000];

int totalw = 0;

int main(int ac, char* av[])
{
    FILE* OUT1, * OUT2, * IN;
    char* pword;
    // ����� ������� ����� ��� ������,
    // �������� �� �����,  ������������� ���������� � �.�.
    if (ac < 2)
    {
        printf("You forgot to specify the list of files!\n"); exit(0);
    }
    OUT1 = fopen("out1.txt", "w");
    OUT2 = fopen("out2.txt", "w");
    if (!OUT1 || !OUT2) {
        printf("Failed to open output files!\n"); exit(1);
    }
    while (--ac) // ���� �� ������ ������
    {
        IN = fopen(av[ac], "r");
        printf("Processing file %s\n", av[ac]);
        // ��������� ��������� ����
        while ((pword = getword(IN)) != NULL)
        { // ......................... 
          // �������� � ����������� ������
          // ��������� � ������ � ����������� totalw
          // ��� ����������� ������� ���
          // ����������� � ������� �����
            int found = 0;
            for (int i = 0; i < totalw; i++) {
                if (strcmp(words[i]->Word, pword) == 0) {
                    words[i]->count++;
                    found = 1;
                    break;
                }
            }
            if (!found && totalw < 100000) {
                WORD* w = (WORD*)malloc(sizeof(WORD));
                w->Word = pword;
                w->count = 1;
                words[totalw++] = w;
            }
            else if (!found) {
                free(pword);
            }
            //
            //     break;  // ������ ��� ��������
        }
        fclose(IN);
    }
    qsort(words, totalw, sizeof(WORD*),
        (int (*)(const void*, const void*))cmpword_alpha);
    // ����� ����� �������
    for (int i = 0; i < totalw; i++) {
        fprintf(OUT1, "%s %d\n", words[i]->Word, words[i]->count);
    }

    qsort(words, totalw, sizeof(WORD*),
        (int (*)(const void*, const void*))cmpword_quant);
    // ����� ����� �������
    for (int i = 0; i < totalw; i++) {
        fprintf(OUT2, "%s %d\n", words[i]->Word, words[i]->count);
    }

    fclose(OUT1);
    fclose(OUT2);
    return 0;
}

char* getword(FILE* F)
{
    char* s; int c;
    // ��������� ���� ����� �� ����� F
    //................. 
    // return NULL ���� ���� ��������
    static char buf[256];
    int i = 0;

    while ((c = fgetc(F)) != EOF) {
        if (isalpha(c)) {
            buf[i++] = tolower(c);
            break;
        }
    }
    if (c == EOF) return NULL;

    while ((c = fgetc(F)) != EOF && (isalpha(c) || isdigit(c))) {
        if (i < 255) {
            buf[i++] = tolower(c);
        }
    }

    buf[i] = '\0';
    s = (char*)malloc(strlen(buf) + 1);
    strcpy(s, buf);
    return s;
}

int cmpword_alpha(WORD* w1, WORD* w2)
{
    return strcmp(w1->Word, w2->Word);
}

int cmpword_quant(WORD* w1, WORD* w2)
{
    return w2->count - w1->count;
}
