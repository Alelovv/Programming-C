#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_DAISIES 100
#define MAX_TRIES 100

// Структура для ромашки
typedef struct {
    int x, y;          // Координаты центра
    int diameter;      // Диаметр цветка
    int petals;        // Количество лепестков
    unsigned long color; // Цвет лепестков
} Daisy;

// Глобальные переменные X11
Display *dis;
int screen;
Window win;
GC gc;

// Цвета
unsigned long green, yellow, white, blue, pink, violet, orange;

// Массив ромашек
Daisy daisies[MAX_DAISIES];
int num_daisies = 0;

// Загрузка цветов
void get_colors() {
    XColor tmp;
    Colormap cmap = DefaultColormap(dis, screen);

    XParseColor(dis, cmap, "green", &tmp);
    XAllocColor(dis, cmap, &tmp);
    green = tmp.pixel;

    XParseColor(dis, cmap, "yellow", &tmp);
    XAllocColor(dis, cmap, &tmp);
    yellow = tmp.pixel;

    XParseColor(dis, cmap, "white", &tmp);
    XAllocColor(dis, cmap, &tmp);
    white = tmp.pixel;

    XParseColor(dis, cmap, "blue", &tmp);
    XAllocColor(dis, cmap, &tmp);
    blue = tmp.pixel;

    XParseColor(dis, cmap, "pink", &tmp);
    XAllocColor(dis, cmap, &tmp);
    pink = tmp.pixel;

    XParseColor(dis, cmap, "violet", &tmp);
    XAllocColor(dis, cmap, &tmp);
    violet = tmp.pixel;

    XParseColor(dis, cmap, "orange", &tmp);
    XAllocColor(dis, cmap, &tmp);
    orange = tmp.pixel;
}

// Инициализация окна
void init_x() {
    unsigned long black = BlackPixel(dis, screen);
    dis = XOpenDisplay(NULL);
    screen = DefaultScreen(dis);
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, WIDTH, HEIGHT, 5, black, green);
    XSetStandardProperties(dis, win, "Ромашки", "Daisies", None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | KeyPressMask);
    gc = XCreateGC(dis, win, 0, 0);
    XMapRaised(dis, win);
    get_colors();
}

// Закрытие окна
void close_x() {
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

// Функция построчной закраски окружности
void fill_circle(int xc, int yc, int r) {
    for (int y = yc - r; y <= yc + r; y++) {
        int dy = y - yc;
        int delta = r * r - dy * dy;
        if (delta >= 0) {
            int dx = (int)sqrt(delta);
            int x1 = xc - dx;
            int x2 = xc + dx;
            if (y >= 0 && y < HEIGHT) {
                x1 = x1 < 0 ? 0 : x1;
                x2 = x2 >= WIDTH ? WIDTH - 1 : x2;
                XDrawLine(dis, win, gc, x1, y, x2, y);
            }
        }
    }
}

// Рисование ромашки
void draw_daisy(Daisy d) {
    double R = d.diameter / 2.0;
    int center_r = (int)(0.125 * d.diameter + 0.5); // Радиус центра = 0.25 * диаметр / 2

    // Рисуем желтый центр
    XSetForeground(dis, gc, yellow);
    fill_circle(d.x, d.y, center_r);

    // Рисуем лепестки
    XSetForeground(dis, gc, d.color);
    double r_petal = 0.3 * d.diameter / 2.0; // Расстояние до центра лепестка
    double rp = 0.2 * d.diameter / 2.0;      // Радиус лепестка
    for (int i = 0; i < d.petals; i++) {
        double theta = i * 2 * M_PI / d.petals;
        int xp = d.x + (int)(r_petal * cos(theta) + 0.5);
        int yp = d.y + (int)(r_petal * sin(theta) + 0.5);
        fill_circle(xp, yp, (int)(rp + 0.5));
    }
}

// Функция растрового круга (перенесена из circle.c)
void rasterCircle(int x0, int y0, int radius) {
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    XDrawPoint(dis, win, gc, x0, y0 + radius);
    XDrawPoint(dis, win, gc, x0, y0 - radius);
    XDrawPoint(dis, win, gc, x0 + radius, y0);
    XDrawPoint(dis, win, gc, x0 - radius, y0);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        XDrawPoint(dis, win, gc, x0 + x, y0 + y);
        XDrawPoint(dis, win, gc, x0 - x, y0 + y);
        XDrawPoint(dis, win, gc, x0 + x, y0 - y);
        XDrawPoint(dis, win, gc, x0 - x, y0 - y);
        XDrawPoint(dis, win, gc, x0 + y, y0 + x);
        XDrawPoint(dis, win, gc, x0 - y, y0 + x);
        XDrawPoint(dis, win, gc, x0 + y, y0 - x);
        XDrawPoint(dis, win, gc, x0 - y, y0 - x);
    }
}

// Генерация ромашек
void generate_daisies() {
    unsigned long petal_colors[] = {white, blue, pink, violet, orange};
    int num_colors = sizeof(petal_colors) / sizeof(unsigned long);
    srand(time(NULL));

    while (1) {
        int tries = 0;
        while (tries < MAX_TRIES) {
            int diameter = 20 + rand() % 41; // 20-60 пикселей
            int R = diameter / 2;
            int x = R + rand() % (WIDTH - 2 * R);
            int y = R + rand() % (HEIGHT - 2 * R);
            int petals = 4 + rand() % 12; // 4-15 лепестков
            unsigned long color = petal_colors[rand() % num_colors];

            // Проверка пересечения
            int intersects = 0;
            for (int i = 0; i < num_daisies; i++) {
                int dx = x - daisies[i].x;
                int dy = y - daisies[i].y;
                int dist_sq = dx * dx + dy * dy;
                int sum_R = R + daisies[i].diameter / 2;
                if (dist_sq < sum_R * sum_R) {
                    intersects = 1;
                    break;
                }
            }

            if (!intersects) {
                daisies[num_daisies].x = x;
                daisies[num_daisies].y = y;
                daisies[num_daisies].diameter = diameter;
                daisies[num_daisies].petals = petals;
                daisies[num_daisies].color = color;
                num_daisies++;
                break;
            }
            tries++;
        }

        if (tries == MAX_TRIES) {
            if (num_daisies >= 2) {
                // Удаляем два первых цветка
                for (int i = 0; i < num_daisies - 2; i++) {
                    daisies[i] = daisies[i + 2];
                }
                num_daisies -= 2;
            } else {
                // Больше не можем удалять, прекращаем
                break;
            }
        }
        if (num_daisies >= MAX_DAISIES) break;
    }
}

// Перерисовка окна
void redraw() {
    XClearWindow(dis, win);
    for (int i = 0; i < num_daisies; i++) {
        draw_daisy(daisies[i]);
    }
}

// Главная функция
int main() {
    XEvent event;
    char text[255];

    init_x();
    generate_daisies();

    while (1) {
        XNextEvent(dis, &event);
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw();
        }
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, NULL, 0) == 1) {
            if (text[0] == 'q') {
                close_x();
            }
        }
    }
    return 0;
}