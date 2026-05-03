#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * FUNCTION: isAnagram
 * -------------------
 * Checks whether two strings are anagrams of each other.
 *
 * Parameters:
 *   a - first string
 *   b - second string
 *
 * Returns:
 *   1 if strings are anagrams
 *   0 otherwise
 */
int isAnagram(char *a, char *b)
{
    int freq[256] = {0};   // Frequency table for ASCII characters

    /* Count characters in first string */
    while (*a) {
        freq[(unsigned char)*a]++;
        a++;
    }

    /* Subtract characters from second string */
    while (*b) {
        freq[(unsigned char)*b]--;
        b++;
    }

    /* Check if all frequencies are zero */
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0)
            return 0;      // Not an anagram
    }

    return 1;              // Anagram
}

/*
 * FUNCTION: removeAnagrams
 * -----------------------
 * Removes consecutive anagrams from the array of words.
 *
 * Parameters:
 *   words       - array of strings
 *   wordsSize   - number of words in the array
 *   returnSize  - output parameter for size of returned array
 *
 * Returns:
 *   A malloc'ed array of strings with consecutive anagrams removed
 */
char** removeAnagrams(char** words, int wordsSize, int* returnSize)
{
    /* Allocate maximum possible space */
    char **result = (char **)malloc(wordsSize * sizeof(char *));
    int k = 0;

    /* Always keep the first word */
    result[k++] = words[0];

    /* Compare each word with the last kept word */
    for (int i = 1; i < wordsSize; i++) {
        if (!isAnagram(words[i], result[k - 1])) {
            result[k++] = words[i];
        }
    }

    *returnSize = k;
    return result;
}

/*
 * FUNCTION: main
 * --------------
 * Driver code to test removeAnagrams function
 */
int main()
{
    char *words[] = {"abba", "baba", "bbaa", "cd", "cd"};
    int wordsSize = sizeof(words) / sizeof(words[0]);
    int returnSize = 0;

    char **result = removeAnagrams(words, wordsSize, &returnSize);

    printf("Result after removing consecutive anagrams:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s ", result[i]);
    }

    printf("\n");

    /* Free dynamically allocated memory */
    free(result);

    return 0;
}
