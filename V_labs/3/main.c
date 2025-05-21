/*
Сборка:
    gcc -o main main.c -liconv

Запуск:
    ./main output.txt путь_к_директории
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iconv.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_FIELD 256
#define MAX_LINE 1024
#define MAX_PATH 1024
#define COMPARE_LEN 5

typedef struct Book {
    int year;
    char title[MAX_FIELD];
    char author[MAX_FIELD];
    char publisher[MAX_FIELD];
    struct Book *left;
    struct Book *right;
} Book;

int isBibFile(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".bib") == 0);
}

Book* makeBook(const char *author, const char *title, const char *publisher, int year) {
    Book *b = (Book*)malloc(sizeof(Book));
    if (!b) exit(1);

    strncpy(b->author, author, MAX_FIELD - 1);
    b->author[MAX_FIELD - 1] = '\0';

    strncpy(b->title, title, MAX_FIELD - 1);
    b->title[MAX_FIELD - 1] = '\0';

    strncpy(b->publisher, publisher, MAX_FIELD - 1);
    b->publisher[MAX_FIELD - 1] = '\0';

    b->year = year;
    b->left = NULL;
    b->right = NULL;

    return b;
}

int cmpPrefix(const char *s1, const char *s2) {
    return strncmp(s1, s2, COMPARE_LEN);
}

Book* addToTree(Book *root, Book *node) {
    if (!root) return node;

    int cmp = cmpPrefix(node->author, root->author);
    if (cmp < 0) {
        root->left = addToTree(root->left, node);
    } else if (cmp > 0) {
        root->right = addToTree(root->right, node);
    } else {
        int cmpTitle = cmpPrefix(node->title, root->title);
        if (cmpTitle < 0) {
            root->left = addToTree(root->left, node);
        } else {
            root->right = addToTree(root->right, node);
        }
    }

    return root;
}

void destroyTree(Book *root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

void outputTree(FILE *fp, Book *node) {
    if (!node) return;
    outputTree(fp, node->left);
    fprintf(fp, "Author: %s\n", node->author);
    fprintf(fp, "Title: %s\n", node->title);
    fprintf(fp, "Publisher: %s\n", node->publisher);
    fprintf(fp, "Year: %d\n\n", node->year);
    outputTree(fp, node->right);
}

void searchTree(Book *root, const char *key) {
    if (!root) return;

    if (strncmp(key, root->author, COMPARE_LEN) == 0 || strncmp(key, root->title, COMPARE_LEN) == 0) {
        printf("Found: %s - %s\n", root->author, root->title);
    }

    if (strncmp(key, root->author, COMPARE_LEN) <= 0 || strncmp(key, root->title, COMPARE_LEN) <= 0)
        searchTree(root->left, key);

    if (strncmp(key, root->author, COMPARE_LEN) >= 0 || strncmp(key, root->title, COMPARE_LEN) >= 0)
        searchTree(root->right, key);
}

void parseBibFile(const char *filepath, Book **tree) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file: %s\n", filepath);
        return;
    }

    char line[MAX_LINE];
    char author[MAX_FIELD] = "";
    char title[MAX_FIELD] = "";
    char publisher[MAX_FIELD] = "";
    int year = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *trim = line;
        while (isspace(*trim)) trim++;
        char *end = trim + strlen(trim) - 1;
        while (end > trim && isspace(*end)) *end-- = '\0';

        if (!*trim || *trim == '%') continue;

        if (strncmp(trim, "author", 6) == 0) {
            char *start = strchr(trim, '{');
            char *finish = strrchr(trim, '}');
            if (start && finish) {
                *finish = '\0';
                strncpy(author, start + 1, MAX_FIELD - 1);
                author[MAX_FIELD - 1] = '\0';
            }
        } else if (strncmp(trim, "title", 5) == 0) {
            char *start = strchr(trim, '{');
            char *finish = strrchr(trim, '}');
            if (start && finish) {
                *finish = '\0';
                strncpy(title, start + 1, MAX_FIELD - 1);
                title[MAX_FIELD - 1] = '\0';
            }
        } else if (strncmp(trim, "publisher", 9) == 0) {
            char *start = strchr(trim, '{');
            char *finish = strrchr(trim, '}');
            if (start && finish) {
                *finish = '\0';
                strncpy(publisher, start + 1, MAX_FIELD - 1);
                publisher[MAX_FIELD - 1] = '\0';
            }
        } else if (strncmp(trim, "year", 4) == 0) {
            char *start = strchr(trim, '{');
            char *finish = strrchr(trim, '}');
            if (start && finish) {
                *finish = '\0';
                year = atoi(start + 1);
            }
        } else if (strcmp(trim, "}") == 0) {
            if (*author && *title) {
                Book *b = makeBook(author, title, publisher, year);
                *tree = addToTree(*tree, b);
                author[0] = title[0] = publisher[0] = '\0';
                year = 0;
            }
        }
    }

    fclose(fp);
}

void handleDirectory(const char *dirname, Book **tree) {
    DIR *dir = opendir(dirname);
    if (!dir) {
        fprintf(stderr, "Directory open error: %s\n", dirname);
        return;
    }

    struct dirent *entry;
    struct stat fileStat;
    char fullPath[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dirname, entry->d_name);
        if (stat(fullPath, &fileStat) != 0) continue;

        if (S_ISREG(fileStat.st_mode) && isBibFile(entry->d_name)) {
            printf("Processing: %s\n", fullPath);
            parseBibFile(fullPath, tree);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s output_file input_dir\n", argv[0]);
        return 1;
    }

    const char *outputPath = argv[1];
    const char *inputDir = argv[2];
    Book *library = NULL;

    handleDirectory(inputDir, &library);

    FILE *outFile = fopen(outputPath, "w");
    if (!outFile) {
        perror("Output file error");
        destroyTree(library);
        return 1;
    }

    outputTree(outFile, library);
    fclose(outFile);

    char key[MAX_FIELD];
    printf("Enter search key (first %d letters): ", COMPARE_LEN);
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Search results:\n");
    searchTree(library, key);

    destroyTree(library);
    return 0;
}
