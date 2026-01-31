/*
    We are looking for the "insertion point" of the target. 
    Even if the target exists in the array, we need the character strictly greater than it.

    1. Initialize low at 0 and high at lettersSize - 1.
    2. While low <= high:
        > Calculate mid.
        > If letters[mid] is less than or equal to the target, the answer must be to the right, so low = mid + 1.
        > Otherwise, the answer could be mid or something further to the left, so high = mid - 1.
    3. After the loop, low will point to the smallest character greater than the target.
    4. Use the modulo operator % to handle the wrap-around case.
*/


#include <stdio.h>

/*
 * Function to find the smallest letter greater than the target.
 * * @param letters: A sorted array of characters.
 * @param lettersSize: The size of the letters array.
 * @param target: The character to compare against.
 * @return: The smallest character greater than target, or letters[0] if none exist.
 */
char nextGreatestLetter(char* letters, int lettersSize, char target) {
    int low = 0;
    int high = lettersSize - 1;

    // Standard Binary Search to find the first element > target
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (letters[mid] <= target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // If 'low' reaches 'lettersSize', it means no element was greater than target.
    // The modulo operator (%) wraps the index back to 0.
    return letters[low % lettersSize];
}

int main() {
    // Example 1
    char letters1[] = {'c', 'f', 'j'};
    printf("Example 1: %c\n", nextGreatestLetter(letters1, 3, 'a')); // Expected: 'c'

    // Example 2
    char letters2[] = {'c', 'f', 'j'};
    printf("Example 2: %c\n", nextGreatestLetter(letters2, 3, 'c')); // Expected: 'f'

    // Example 3
    char letters3[] = {'x', 'x', 'y', 'y'};
    printf("Example 3: %c\n", nextGreatestLetter(letters3, 4, 'z')); // Expected: 'x'

    return 0;
}



/*
    How the code handles the "Wrap Around"
        The most elegant part of this solution is the final line: return letters[low % lettersSize];

        Case A (Target found in middle): 
            If the target is 'c' and the array is ['c', 'f', 'j'], 
            low will end up at index 1 (letter 'f'). 1 % 3 is still 1, so it returns 'f'.

        Case B (Target is larger than everything): 
            If the target is 'z' and the array is ['a', 'b'], 
            the low pointer will eventually increment past the end of the array to index 2. 
            Since 2 % 2 is 0, it automatically returns the first element (letters[0]), 
            satisfying the problem's wrap-around requirement.
*/

/*
    Metric  | Complexity
    --------|-----------
    Time    | O(log n)
    Space   | O(1)
*/