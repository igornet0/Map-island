#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 8
#define MAX_BLOCKS 100
#define INPUT_FILE "C:\\Users\\User\\Desktop\\Map-island\\input.in"
#define OUTPUT_FILE "C:\\Users\\User\\Desktop\\Map-island\\output.c"

typedef struct {
    int n;
    int horizontal[MAX_N][MAX_N];
    int vertical[MAX_N][MAX_N];
    int h_size[MAX_N];
    int v_size[MAX_N];
} ProblemBlock;

// Функция для считывания данных
int readInput(ProblemBlock *blocks, int *block_count) {
    FILE *input = fopen(INPUT_FILE, "r");
    if (!input) {
        printf("Error opening input file.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(input, "%d", &blocks[count].n) == 1) {
        int n = blocks[count].n;

        // Считываем горизонтальные данные
        for (int i = 0; i < n; i++) {
            blocks[count].h_size[i] = 0;
            int value;
            while (fscanf(input, "%d", &value) && value != 0) {
                blocks[count].horizontal[i][blocks[count].h_size[i]++] = value;
            }
        }

        // Считываем вертикальные данные
        for (int i = 0; i < n; i++) {
            blocks[count].v_size[i] = 0;
            int value;
            while (fscanf(input, "%d", &value) && value != 0) {
                blocks[count].vertical[i][blocks[count].v_size[i]++] = value;
            }
        }

        count++;
    }

    fclose(input);
    *block_count = count;
    return 1;
}

// Проверка соответствия строки
int checkRow(int *row, int *pattern, int size, int n) {
    int i = 0, count = 0, index = 0;
    while (i < n) {
        if (row[i] == 1) {
            count++;
        } else if (count > 0) {
            if (index >= size || pattern[index++] != count) return 0;
            count = 0;
        }
        i++;
    }
    if (count > 0) {
        if (index >= size || pattern[index++] != count) return 0;
    }
    return index == size;
}

// Рекурсивное восстановление карты
void solve(int n, int grid[MAX_N][MAX_N], int row, int col, ProblemBlock *block, int *found) {
    if (row == n) {
        for (int i = 0; i < n; i++) {
            int temp[MAX_N];
            for (int j = 0; j < n; j++) temp[j] = grid[j][i];
            if (!checkRow(temp, block->vertical[i], block->v_size[i], n)) return;
        }
        *found = 1;
        return;
    }

    if (col == n) {
        int temp[MAX_N];
        for (int i = 0; i < n; i++) temp[i] = grid[row][i];
        if (!checkRow(temp, block->horizontal[row], block->h_size[row], n)) return;
        solve(n, grid, row + 1, 0, block, found);
        return;
    }

    grid[row][col] = 0;
    solve(n, grid, row, col + 1, block, found);
    if (*found) return;

    grid[row][col] = 1;
    solve(n, grid, row, col + 1, block, found);
}

// Восстановление карты
int restoreMap(ProblemBlock *block, FILE *output) {
    int grid[MAX_N][MAX_N] = {0};
    int found = 0;

    solve(block->n, grid, 0, 0, block, &found);

    if (!found) {
        fprintf(output, "no map\n");
        return 0;
    }

    for (int i = 0; i < block->n; i++) {
        for (int j = 0; j < block->n; j++) {
            fprintf(output, "%s", grid[i][j] ? "* " : "  ");
        }
        fprintf(output, "\n");
    }
    return 1;
}

// Главная функция
int main() {
    ProblemBlock blocks[MAX_BLOCKS];
    int block_count;

    if (!readInput(blocks, &block_count)) {
        return 1;
    }

    FILE *output = fopen(OUTPUT_FILE, "w");
    if (!output) {
        printf("Error opening output file.\n");
        return 1;
    }

    for (int i = 0; i < block_count; i++) {
        if (i > 0) fprintf(output, "next problem\n");
        if (!restoreMap(&blocks[i], output)) {
            fprintf(output, "\n");
        }
    }

    fclose(output);
    printf("Saved to %s\n", OUTPUT_FILE);
    return 0;
}