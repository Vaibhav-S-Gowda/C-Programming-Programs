/*
    The Logic
        For an element to have both a strictly smaller and a strictly greater element in the same array, 
        it simply needs to exist somewhere in the "middle" of the range.
            - If an element is the minimum (min(nums)), 
                there is nothing strictly smaller than it.
            - If an element is the maximum (max(nums)), 
                there is nothing strictly greater than it.
        Therefore, any element $x$ satisfies the condition if:
            min(nums) < x < max(nums)
*/

/*
    Complexity Analysis
        Time Complexity: O(n). We traverse the array to find the min/max and then once more to count.
        Space Complexity: O(1). We only store a few integer variables regardless of the input size.
*/