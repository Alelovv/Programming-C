// Найти все области, статистику глифов:
// размеры глифа, количество пикселей, плотность, связность, диаметр, периметр
// найти похожие глифы путем сравнения глифов одинакового размера.
// Похожие глифы должны содержать не более 10% раличающихся пикселей.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

#define ISBIT(n,x) (((01<<(n))&(x))?1:0)
#define MAX_GLYPHS 50000
#define SIMILARITY_THRESHOLD 0.9 // 90% similarity (10% difference)

typedef struct img { // Структура глифа - картинки
   int w; int h;     // ширина и высота в пикселях
   int dx;           // расстояние до следующего глифа (если буква)
   int count;        // черных пикселей всего
   int id;           // идентификатор - "номер" глифа
   int bytes;        // количество байтов в битовой карте (неупакованная)
   double density;   // плотность черных пикселей
   int diam;         // диаметр в манхэттенской метрике
   int perim;        // периметр глифа
   int conn;         // связность
   unsigned char *data;  // битовая карта (неупакованная)
} IMG;

IMG *G[MAX_GLYPHS];
int N = 0;


void calculate_stats(IMG *img);
void find_similar_glyphs();
void print_glyph_stats(IMG *img);
int compare_glyphs(IMG *a, IMG *b);
void flood_fill(IMG *img, int x, int y, int *area, int *perimeter, int visited[][img->h]);
int get_pixel(IMG *img, int x, int y);

void outbyte(char byte) { // Вывод байта в двоичном виде
    for (int i = 7; i >= 0; i--)
        putchar(ISBIT(i, byte) ? '*' : ' ');
    fflush(stdout);
}

void outbytes(int n, char *byte) { // Вывод массива байтов в двоичном виде
    for (int i = 0; i < n; i++)
        outbyte(byte[i]);
    putchar('\n');
}

int popcnt8(unsigned char i) {
    int count = 0;
    while (i) {
        count++;
        i &= (i - 1);
    }
    return count;
}

int popcnt64(unsigned long long w) {
    //  return __builtin_popcountll(w);
    w -= (w >> 1) & 0x5555555555555555ULL;
    w = (w & 0x3333333333333333ULL) + ((w >> 2) & 0x3333333333333333ULL);
    w = (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    return (int)((w * 0x0101010101010101ULL) >> 56);
}

IMG *init_img(int id, int w, int h) { 
    // создание пустого (чистого) глифа с заданными размерами
    IMG *t = (IMG *)malloc(sizeof(IMG));
    t->w = w;
    t->h = h;
    t->dx = 0;
    t->count = 0;
    t->id = id;
    t->bytes = w * h; 
    t->data = (unsigned char *)calloc(t->bytes, 1);
    return t;
}

IMG *load_img(int id, char *File) {             // TODO -  считывание из каталога
    
    FILE *F = fopen(File, "rb");        // считывание из файла глифа с номером id
    if (!F) {
        perror("Error opening file");
        return NULL;
    }

    IMG *I = (IMG *)malloc(sizeof(IMG));
    fread(&I->w, sizeof(int), 1, F);
    fread(&I->h, sizeof(int), 1, F);
    fread(&I->dx, sizeof(int), 1, F);
    fread(&I->count, sizeof(int), 1, F);
    fread(&I->id, sizeof(int), 1, F);
    fread(&I->bytes, sizeof(int), 1, F);


    int packed_bytes = I->bytes;
    unsigned char *packed_data = (unsigned char *)malloc(packed_bytes);
    fread(packed_data, 1, packed_bytes, F);
    fclose(F);


    I->data = (unsigned char *)calloc(I->w * I->h, 1);
    I->bytes = I->w * I->h;

    int row_bytes = (I->h + 7) / 8;
    for (int x = 0; x < I->w; x++) {
        for (int b = 0; b < row_bytes; b++) {
            unsigned char byte = packed_data[x * row_bytes + b];
            for (int k = 0; k < 8 && (b * 8 + k) < I->h; k++) {
                int y = b * 8 + k;
                I->data[x + y * I->w] = (byte >> (7 - k)) & 1;
            }
        }
    }
    free(packed_data);

    calculate_stats(I);
    return I;
}

int get_pixel(IMG *img, int x, int y) { // Получение значения пикселя
    if (x < 0 || x >= img->w || y < 0 || y >= img->h) return 0;
    return img->data[x + y * img->w];
}

void calculate_stats(IMG *img) { // Расчет статистик глифа
    if (img->count == 0) {
        img->count = 0;
        for (int i = 0; i < img->w * img->h; i++)
            img->count += img->data[i];
    }

    img->density = (double)img->count / (img->w * img->h);

    int min_x = img->w, max_x = -1;
    int min_y = img->h, max_y = -1;
    int has_pixels = 0;

    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w; x++) {
            if (get_pixel(img, x, y)) {
                has_pixels = 1;
                if (x < min_x) min_x = x;
                if (x > max_x) max_x = x;
                if (y < min_y) min_y = y;
                if (y > max_y) max_y = y;
            }
        }
    }

    img->diam = has_pixels ? (max_x - min_x + max_y - min_y) : 0;

    int visited[img->w][img->h];
    memset(visited, 0, sizeof(visited));
    int total_perimeter = 0, regions = 0;

    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w; x++) {
            if (get_pixel(img, x, y) && !visited[x][y]) {
                int area = 0, perimeter = 0;
                flood_fill(img, x, y, &area, &perimeter, visited);
                total_perimeter += perimeter;
                regions++;
            }
        }
    }

    img->perim = total_perimeter;
    img->conn = regions;
}

void flood_fill(IMG *img, int x, int y, int *area, int *perimeter, int visited[][img->h]) {
    if (x < 0 || x >= img->w || y < 0 || y >= img->h || visited[x][y] || !get_pixel(img, x, y)) {
        return;
    }

    visited[x][y] = 1;
    (*area)++;

    int neighbors = get_pixel(img, x-1, y) + get_pixel(img, x+1, y) +
                    get_pixel(img, x, y-1) + get_pixel(img, x, y+1);
    *perimeter += (4 - neighbors);

    flood_fill(img, x+1, y, area, perimeter, visited);
    flood_fill(img, x-1, y, area, perimeter, visited);
    flood_fill(img, x, y+1, area, perimeter, visited);
    flood_fill(img, x, y-1, area, perimeter, visited);
}

void print_glyph_stats(IMG *img) {
    printf("ID: %d\n", img->id);
    printf("Dimensions: %d x %d pixels\n", img->w, img->h);
    printf("Black pixels: %d\n", img->count);
    printf("Density: %.2f%%\n", img->density * 100);
    printf("Diameter (Manhattan): %d\n", img->diam);
    printf("Perimeter: %d\n", img->perim);
    printf("Connectivity (regions): %d\n", img->conn);
    printf("\n");
}

int compare_glyphs(IMG *a, IMG *b) { // Сравнение глифов
    if (a->w != b->w || a->h != b->h) return 0;

    int total_pixels = a->w * a->h;
    int different_pixels = 0;

    for (int y = 0; y < a->h; y++) {
        for (int x = 0; x < a->w; x++) {
            if (get_pixel(a, x, y) != get_pixel(b, x, y)) {
                different_pixels++;
            }
        }
    }

    double similarity = 1.0 - (double)different_pixels / total_pixels;
    return (similarity >= SIMILARITY_THRESHOLD);
}

void find_similar_glyphs() { // Поиск похожих глифов
    printf("\nFinding similar glyphs...\n");
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (compare_glyphs(G[i], G[j])) {
                printf("Glyph %d and %d are similar (size: %dx%d)\n", 
                       G[i]->id, G[j]->id, G[i]->w, G[i]->h);
            }
        }
    }
}

void process_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    char filename[256];
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "glif_") == entry->d_name) {
            snprintf(filename, sizeof(filename), "%s/%s", path, entry->d_name);
            G[N] = load_img(N, filename);
            if (G[N]) {
                printf("Loaded %s\n", filename);
                print_glyph_stats(G[N]);
                N++;
                if (N >= MAX_GLYPHS) break;
            }
        }
    }
    closedir(dir);
}

int main() {
    char path[256];
    printf("Enter the directory path for glyph files: ");
    scanf("%255s", path);

    process_directory(path);
    if (N == 0) {
        printf("No glyphs were loaded.\n");
        return 1;
    }

    find_similar_glyphs();

    for (int i = 0; i < N; i++) {
        free(G[i]->data);
        free(G[i]);
    }
    return 0;
}