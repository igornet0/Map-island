#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 8

// Глобальные переменные
int N;
int horizontal[MAX_SIZE][MAX_SIZE]; // Коды горизонталей
int vertical[MAX_SIZE][MAX_SIZE];   // Коды вертикалей
int grid[MAX_SIZE][MAX_SIZE];       // Текущая карта
int solutions_found = 0;

// Функция для проверки строки на соответствие коду
int validate_row(int row, int *code) {
    int count = 0, index = 0, group_size = 0;
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == 1) {
            group_size++;
        } else if (group_size > 0) {
            if (index >= MAX_SIZE || code[index++] != group_size) return 0;
            group_size = 0;
        }
    }
    if (group_size > 0) {
        if (index >= MAX_SIZE || code[index++] != group_size) return 0;
    }
    return code[index] == 0;
}

// Функция для проверки столбца на соответствие коду
int validate_column(int col, int *code) {
    int count = 0, index = 0, group_size = 0;
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == 1) {
            group_size++;
        } else if (group_size > 0) {
            if (index >= MAX_SIZE || code[index++] != group_size) return 0;
            group_size = 0;
        }
    }
    if (group_size > 0) {
        if (index >= MAX_SIZE || code[index++] != group_size) return 0;
    }
    return code[index] == 0;
}

// Функция проверки текущей карты
int validate_grid() {
    for (int i = 0; i < N; i++) {
        if (!validate_row(i, horizontal[i]) || !validate_column(i, vertical[i])) {
            return 0;
        }
    }
    return 1;
}

// Рекурсивная функция для восстановления карты
void backtrack(int row, int col) {
    if (row == N) {
        if (validate_grid()) {
            solutions_found++;
            printf("Solution %d:\n", solutions_found);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%s", grid[i][j] ? "* " : "  ");
                }
                printf("\n");
            }
            printf("\n");
        }
        return;
    }

    int next_row = (col == N - 1) ? row + 1 : row;
    int next_col = (col == N - 1) ? 0 : col + 1;

    // Попробовать оставить пустым
    grid[row][col] = 0;
    backtrack(next_row, next_col);

    // Попробовать поместить остров
    grid[row][col] = 1;
    if (validate_row(row, horizontal[row]) && validate_column(col, vertical[col])) {
        backtrack(next_row, next_col);
    }

    // Вернуть состояние
    grid[row][col] = 0;
}

int main() {
    FILE *input = fopen("C:\\Users\\User\\Desktop\\Map-island\\input.in", "r");
    FILE *output = fopen("C:\\Users\\User\\Desktop\\Map-island\\output.c", "w");

    if (!input || !output) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(input, "%d", &N) == 1) {
        if (N < 1 || N > MAX_SIZE) {
            fprintf(output, "Invalid grid size.\nnext problem\n");
            continue;
        }

        // Считать горизонтальные коды
        memset(horizontal, 0, sizeof(horizontal));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                fscanf(input, "%d", &horizontal[i][j]);
                if (horizontal[i][j] == 0) break;
            }
        }

        // Считать вертикальные коды
        memset(vertical, 0, sizeof(vertical));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                fscanf(input, "%d", &vertical[i][j]);
                if (vertical[i][j] == 0) break;
            }
        }

        // Инициализация сетки и поиск решений
        memset(grid, 0, sizeof(grid));
        solutions_found = 0;
        backtrack(0, 0);

        if (solutions_found == 0) {
            fprintf(output, "no map\n");
        }

        fprintf(output, "next problem\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}