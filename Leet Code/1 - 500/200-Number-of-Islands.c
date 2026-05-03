#include <stdio.h>

void dfs(char** grid, int m, int n, int r, int c) {
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') {
        return;
    }

    grid[r][c] = '0';

    dfs(grid, m, n, r - 1, c);
    dfs(grid, m, n, r + 1, c);
    dfs(grid, m, n, r, c - 1);
    dfs(grid, m, n, r, c + 1);
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0) return 0;

    int m = gridSize;
    int n = gridColSize[0];
    int islands = 0;

    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == '1') {
                islands++;
                dfs(grid, m, n, r, c);
            }
        }
    }

    return islands;
}

int main() {
    char row1[] = {'1','1','0','0','0'};
    char row2[] = {'1','1','0','0','0'};
    char row3[] = {'0','0','1','0','0'};
    char row4[] = {'0','0','0','1','1'};

    char* grid[] = {row1, row2, row3, row4};
    int gridColSize[] = {5,5,5,5};

    int result = numIslands(grid, 4, gridColSize);

    printf("Number of islands: %d\n", result);

    return 0;
}