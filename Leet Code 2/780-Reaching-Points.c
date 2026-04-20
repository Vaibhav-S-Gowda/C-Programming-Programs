#include <stdio.h>
#include <stdbool.h>

/**
 * Logic: 
 * Instead of (x, y) -> (x+y, y) or (x, x+y), 
 * we go (tx, ty) -> (tx-ty, ty) if tx > ty, else (tx, ty-tx).
 * We use % to speed up multiple subtractions.
 */
bool reachingPoints(int sx, int sy, int tx, int ty) {
    while (tx >= sx && ty >= sy) {
        if (tx == sx && ty == sy) {
            return true;
        }
        
        if (tx > ty) {
            if (ty == sy) {
                // If ty matches sy, tx must be reachable by subtracting multiples of sy
                return (tx - sx) % sy == 0;
            }
            tx %= ty;
        } else if (ty > tx) {
            if (tx == sx) {
                // If tx matches sx, ty must be reachable by subtracting multiples of sx
                return (ty - sy) % sx == 0;
            }
            ty %= tx;
        } else {
            // tx == ty, and they aren't sx, sy. No further moves possible.
            break;
        }
    }
    return false;
}

int main() {
    // Test Case 1
    int sx1 = 1, sy1 = 1, tx1 = 3, ty1 = 5;
    printf("Test 1: %s\n", reachingPoints(sx1, sy1, tx1, ty1) ? "true" : "false");

    // Test Case 2
    int sx2 = 1, sy2 = 1, tx2 = 2, ty2 = 2;
    printf("Test 2: %s\n", reachingPoints(sx2, sy2, tx2, ty2) ? "true" : "false");

    // Test Case 3
    int sx3 = 1, sy3 = 1, tx3 = 1, ty3 = 1;
    printf("Test 3: %s\n", reachingPoints(sx3, sy3, tx3, ty3) ? "true" : "false");

    return 0;
}