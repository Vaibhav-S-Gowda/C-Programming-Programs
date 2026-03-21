#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Helper function to check if a character is a vowel
bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

char* reverseVowels(char* s) {
    int left = 0;
    int right = strlen(s) - 1;
    
    while (left < right) {
        // 1. Move left pointer until a vowel is found
        while (left < right && !isVowel(s[left])) {
            left++;
        }
        
        // 2. Move right pointer until a vowel is found
        while (left < right && !isVowel(s[right])) {
            right--;
        }
        
        // 3. Swap the vowels
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            
            // 4. Move pointers for next iteration
            left++;
            right--;
        }
    }
    
    return s;
}

int main() {
    // Note: Use a char array (buffer) because string literals like "hello"
    // are often stored in read-only memory and will crash on modification.
    char str1[] = "hello";
    printf("Input: hello -> Output: %s\n", reverseVowels(str1));

    char str2[] = "leetcode";
    printf("Input: leetcode -> Output: %s\n", reverseVowels(str2));

    char str3[] = "IceCreAm";
    printf("Input: IceCreAm -> Output: %s\n", reverseVowels(str3));

    return 0;
}