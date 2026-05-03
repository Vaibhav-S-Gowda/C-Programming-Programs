#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHA 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    char            *word;
    int              childCnt;
} TrieNode;

// ── Pool allocator (no malloc overhead in hot path) ────────
#define POOL_SIZE 300000
static TrieNode pool[POOL_SIZE];
static int      poolIdx;

static TrieNode *newNode(void) {
    TrieNode *n = &pool[poolIdx++];
    memset(n, 0, sizeof *n);
    return n;
}

static void insertWord(TrieNode *root, char *word) {
    TrieNode *cur = root;
    for (char *p = word; *p; ++p) {
        int c = *p - 'a';
        if (!cur->children[c]) {
            cur->children[c] = newNode();
            cur->childCnt++;
        }
        cur = cur->children[c];
    }
    cur->word = word;
}

// ── Globals to avoid passing through every DFS frame ───────
static char  **g_board;
static int     g_rows, g_cols;
static char  **g_results;
static int     g_resCount;

static const int DR[] = {-1, 1,  0, 0};
static const int DC[] = { 0, 0, -1, 1};

// ── DFS + Trie traversal with live pruning ─────────────────
static void dfs(int r, int c, TrieNode *node) {
    char ch = g_board[r][c];
    int  ci  = ch - 'a';

    TrieNode *next = node->children[ci];
    if (!next) return;

    // Collect word (clear to prevent duplicates)
    if (next->word) {
        g_results[g_resCount++] = next->word;
        next->word = NULL;
    }

    // Prune dead node immediately before going deeper
    if (next->childCnt == 0) {
        node->children[ci] = NULL;
        node->childCnt--;
        return;
    }

    // Mark visited in-place (no extra memory)
    g_board[r][c] = '#';

    for (int d = 0; d < 4; d++) {
        int nr = r + DR[d];
        int nc = c + DC[d];
        if ((unsigned)nr < (unsigned)g_rows &&   // branchless bounds check
            (unsigned)nc < (unsigned)g_cols &&
            g_board[nr][nc] != '#')
            dfs(nr, nc, next);
    }

    g_board[r][c] = ch;  // restore

    // Post-visit pruning: detach if now a dead leaf
    if (next->childCnt == 0 && !next->word) {
        node->children[ci] = NULL;
        node->childCnt--;
    }
}

// ── CORRECT LeetCode signature ─────────────────────────────
char **findWords(char **board, int boardSize, int *boardColSize,
                 char **words, int wordsSize, int *returnSize) {

    // Reset pool
    poolIdx    = 0;
    g_resCount = 0;
    g_board    = board;
    g_rows     = boardSize;
    g_cols     = boardColSize[0];   // all rows same width on LeetCode

    g_results  = (char **)malloc(wordsSize * sizeof(char *));

    // Build Trie
    TrieNode *root = newNode();
    for (int i = 0; i < wordsSize; i++)
        insertWord(root, words[i]);

    // Search every cell
    for (int i = 0; i < g_rows; i++)
        for (int j = 0; j < g_cols; j++)
            if (root->children[g_board[i][j] - 'a'])  // skip if no word starts here
                dfs(i, j, root);

    *returnSize = g_resCount;
    return g_results;
}


int main() {
    // 1. Setup the board: [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]
    int rows = 4;
    int cols = 4;
    char *rawBoard[] = {
        "oaan",
        "etae",
        "ihkr",
        "iflv"
    };

    // Convert raw strings to the char** format LeetCode uses
    char **board = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        board[i] = (char *)malloc((cols + 1) * sizeof(char));
        strcpy(board[i], rawBoard[i]);
    }

    // 2. Setup the words to search for
    char *words[] = {"oath", "pea", "eat", "rain"};
    int wordsSize = 4;

    // 3. Setup return parameters
    int returnSize;
    int boardColSize[] = {cols, cols, cols, cols};

    // 4. Call your function
    printf("Searching for words...\n");
    char **results = findWords(board, rows, boardColSize, words, wordsSize, &returnSize);

    // 5. Print results
    printf("Words found (%d): ", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s ", results[i]);
    }
    printf("\n");

    // 6. Cleanup
    for (int i = 0; i < rows; i++) free(board[i]);
    free(board);
    free(results);

    return 0;
}