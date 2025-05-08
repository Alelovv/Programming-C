#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
    int distance;
} Element;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool checkMove(int from, int to, int direction, char** maze, int rows, int cols) {
    int wall_from = 0;
    int wall_to = 0;

    char ch_from = maze[from / cols][from % cols];
    char ch_to = maze[to / cols][to % cols];

    if (ch_from >= '0' && ch_from <= '9') {
        wall_from = ch_from - '0';
    } else if (ch_from >= 'A' && ch_from <= 'F') {
        wall_from = ch_from - 'A' + 10;
    }

    if (ch_to >= '0' && ch_to <= '9') {
        wall_to = ch_to - '0';
    } else if (ch_to >= 'A' && ch_to <= 'F') {
        wall_to = ch_to - 'A' + 10;
    }

    if (direction == 0) {
        if ((wall_from & 1) || (wall_to & 4)) return false;
    } else if (direction == 1) {
        if ((wall_from & 2) || (wall_to & 8)) return false;
    } else if (direction == 2) {
        if ((wall_from & 4) || (wall_to & 1)) return false;
    } else if (direction == 3) {
        if ((wall_from & 8) || (wall_to & 2)) return false;
    }

    return true;
}

void solveMaze(char** maze, int rows, int cols) {
    bool** visited;
    int** parent;
    int i, j;

    visited = (bool**)malloc(rows * sizeof(bool*));
    parent = (int**)malloc(rows * sizeof(int*));

    for (i = 0; i < rows; i++) {
        visited[i] = (bool*)calloc(cols, sizeof(bool));
        parent[i] = (int*)malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            parent[i][j] = -1;
        }
    }

    Element* queue;
    queue = (Element*)malloc(rows * cols * sizeof(Element));
    int front = 0;
    int rear = 0;

    queue[rear].pos.x = 0;
    queue[rear].pos.y = 0;
    queue[rear].distance = 0;
    rear++;
    visited[0][0] = true;

    bool found = false;
    Position goal;
    goal.x = rows - 1;
    goal.y = cols - 1;

    int path_len = 0;

    while (front < rear) {
        Element now = queue[front];
        front++;

        if (now.pos.x == goal.x && now.pos.y == goal.y) {
            found = true;
            path_len = now.distance;
            break;
        }

        for (i = 0; i < 4; i++) {
            int nx = now.pos.x + dx[i];
            int ny = now.pos.y + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (!visited[nx][ny]) {
                    int from = now.pos.x * cols + now.pos.y;
                    int to = nx * cols + ny;

                    if (checkMove(from, to, i, maze, rows, cols)) {
                        visited[nx][ny] = true;
                        parent[nx][ny] = from;
                        queue[rear].pos.x = nx;
                        queue[rear].pos.y = ny;
                        queue[rear].distance = now.distance + 1;
                        rear++;
                    }
                }
            }
        }
    }

    if (found) {
        printf("%d\n", path_len);

        Position current = goal;
        while (!(current.x == 0 && current.y == 0)) {
            int p = parent[current.x][current.y];
            if (p == -1) {
                break;
            }
            current.x = p / cols;
            current.y = p % cols;

            if (maze[current.x][current.y] != '0') {
                maze[current.x][current.y] = '*';
            }
        }
        maze[goal.x][goal.y] = '*';

        FILE* output = fopen("output.txt", "w");
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                fputc(maze[i][j], output);
            }
            fputc('\n', output);
        }
        fclose(output);
    } else {
        printf("No path found\n");
    }

    for (i = 0; i < rows; i++) {
        free(visited[i]);
        free(parent[i]);
    }
    free(visited);
    free(parent);
    free(queue);
}

int main() {
    char file_name[100];
    char line[256];
    FILE* file;
    int rows = 0;
    int cols = 0;
    int i;

    printf("Enter maze filename: ");
    scanf("%s", file_name);

    file = fopen(file_name, "r");
    if (!file) {
        printf("Cannot open file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len > 0) {
            rows++;
            if (cols == 0) {
                cols = len;
            } else if (cols != len) {
                printf("Inconsistent line length\n");
                fclose(file);
                return 1;
            }
        }
    }

    if (rows == 0 || cols == 0) {
        printf("Empty maze\n");
        fclose(file);
        return 1;
    }

    rewind(file);

    char** maze = (char**)malloc(rows * sizeof(char*));
    for (i = 0; i < rows; i++) {
        maze[i] = (char*)malloc((cols + 1) * sizeof(char));
        if (fgets(line, sizeof(line), file)) {
            int len = strlen(line);
            if (line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            strncpy(maze[i], line, cols);
            maze[i][cols] = '\0';
        }
    }

    fclose(file);

    solveMaze(maze, rows, cols);

    for (i = 0; i < rows; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}

