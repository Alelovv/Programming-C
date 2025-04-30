#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct word {
    int count;
    char *word;
} WORD;

WORD *words[100000];
size_t total_words = 0;

int cmpword_alpha(const void *w1, const void *w2);
int cmpword_freq(const void *w1, const void *w2);

char *get_word(FILE *file);
void add_word(char *word);
void write_output(FILE *out);
int is_text_file(const char *filename);

int main(int argc, char *argv[]) {
    FILE *out_alpha, *out_freq, *input_file;
    char *pword;
    DIR *dir;
    struct dirent *ent;
    char path[1024];

    if (argc < 2) {
        printf("Directory not found\n");
        exit(1);
    }

    for (int i = 0; i < 100000; i++) {
        words[i] = NULL;
    }

    if ((dir = opendir(argv[1])) == NULL) {
        printf("Couldn't open directory %s\n", argv[1]);
        exit(1);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", argv[1], ent->d_name);

        if (!is_text_file(path)) {
            continue;
        }

        input_file = fopen(path, "r");
        if (input_file == NULL) {
            printf("Couldn't open file %s\n", path);
            continue;
        }

        printf("Processing file %s\n", path);

        while ((pword = get_word(input_file)) != NULL) {
            add_word(pword);
            free(pword);
        }

        fclose(input_file);
    }
    closedir(dir);

    out_alpha = fopen("dict_alpha.txt", "w");
    out_freq = fopen("dict_freq.txt", "w");
    if (out_alpha == NULL || out_freq == NULL) {
        printf("Unable to create output files\n");
        return 0;
    }

    qsort(words, total_words, sizeof(WORD *), cmpword_alpha);
    write_output(out_alpha);

    qsort(words, total_words, sizeof(WORD *), cmpword_freq);
    write_output(out_freq);

    fclose(out_alpha);
    fclose(out_freq);

    for (int i = 0; i < total_words; i++) {
        free(words[i]->word);
        free(words[i]);
    }

    return 0;
}

void add_word(char *word) {
    for (int i = 0; i < total_words; i++) {
        if (strcmp(words[i]->word, word) == 0) {
            words[i]->count++;
            return;
        }
    }

    WORD *new_word = (WORD *)malloc(sizeof(WORD));

    new_word->word = strdup(word);

    new_word->count = 1;
    words[total_words++] = new_word;
}

char *get_word(FILE *file) {
    static char buffer[256];
    int c;
    int i = 0;

    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            buffer[i++] = (char)tolower(c);
            break;
        }
    }

    if (c == EOF) {
        return NULL;
    }

    while (i < 255 && (c = fgetc(file)) != EOF && isalnum(c)) {
        buffer[i++] = (char)tolower(c);
    }

    buffer[i] = '\0';
    return strdup(buffer);
}

int cmpword_alpha(const void *w1, const void *w2) {
    const WORD *word1 = *(const WORD **)w1;
    const WORD *word2 = *(const WORD **)w2;
    return strcmp(word1->word, word2->word);
}

int cmpword_freq(const void *w1, const void *w2) {
    const WORD *word1 = *(const WORD **)w1;
    const WORD *word2 = *(const WORD **)w2;

    if (word1->count > word2->count) return -1;
    if (word1->count < word2->count) return 1;
    return strcmp(word1->word, word2->word);
}

void write_output(FILE *out) {
    for (int i = 0; i < total_words; i++) {
        fprintf(out, "%s: %d\n", words[i]->word, words[i]->count);
    }
}

int is_text_file(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        return 0;
    }

    if (!S_ISREG(st.st_mode)) {
        return 0;
    }

    const char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".txt") == 0) {
        return 1;
    }
    return 0;
}
