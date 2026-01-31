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