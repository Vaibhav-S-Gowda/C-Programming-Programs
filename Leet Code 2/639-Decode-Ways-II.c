#include <stdio.h>
#include <string.h>

// Helper to handle single character decodings
long long ways_1_char(char c) {
    if (c == '*') return 9;
    if (c == '0') return 0;
    return 1;
}

// Helper to handle two character decodings
long long ways_2_chars(char c1, char c2) {
    if (c1 == '*' && c2 == '*') {
        return 15; // 11-19 and 21-26
    }
    if (c1 == '*') {
        return (c2 <= '6') ? 2 : 1; // 1x or 2x
    }
    if (c2 == '*') {
        if (c1 == '1') return 9;
        if (c1 == '2') return 6;
        return 0;
    }
    int val = (c1 - '0') * 10 + (c2 - '0');
    return (val >= 10 && val <= 26) ? 1 : 0;
}

int numDecodings(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;
    
    long long MOD = 1000000007;
    long long first = 1; 
    long long second = ways_1_char(s[0]);
    
    for (int i = 1; i < n; i++) {
        long long current = (ways_1_char(s[i]) * second) % MOD;
        current = (current + ways_2_chars(s[i-1], s[i]) * first) % MOD;
        
        first = second;
        second = current;
    }
    
    return (int)second;
}

int main() {
    // Array of test cases
    char *tests[] = {"*", "1*", "2*", "10", "*1", "28"};
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    printf("Decode Ways II Results:\n");
    printf("---------------------------\n");
    for (int i = 0; i < num_tests; i++) {
        printf("Input: %-5s | Ways: %d\n", tests[i], numDecodings(tests[i]));
    }

    return 0;
}