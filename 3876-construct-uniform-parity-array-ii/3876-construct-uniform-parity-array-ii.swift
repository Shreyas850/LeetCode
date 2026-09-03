class Solution {
    func hasValidArray(_ nums1: [Int]) -> Bool {
        var minVal = Int.max
        var hasEven = false
        var hasOdd = false
        
        for num in nums1 {
            if num < minVal {
                minVal = num
            }
            if num % 2 == 0 {
                hasEven = true
            } else {
                hasOdd = true
            }
        }
        
        // If all elements already have the same parity, it's possible.
        if !hasEven || !hasOdd {
            return true
        }
        
        // If there is a mix of even and odd, we can only achieve uniformity (all odds) 
        // if the absolute minimum element in the array is odd.
        return minVal % 2 != 0
    }
    
    // Providing this alias to match the test runner from your previous error
    func uniformArray(_ nums1: [Int]) -> Bool {
        return hasValidArray(nums1)
    }
}