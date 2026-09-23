class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total_sum = 0;
        for (int num : nums) {
            total_sum += num;
        }
        
        int target = total_sum - x;
        
        // If the total sum is less than x, it's impossible.
        if (target < 0) return -1;
        // If the total sum is exactly x, we need all elements.
        if (target == 0) return nums.size();
        
        int max_len = -1;
        int current_sum = 0;
        int left = 0;
        int n = nums.size();
        
        for (int right = 0; right < n; ++right) {
            current_sum += nums[right];
            
            // Shrink the window if the sum exceeds the target
            while (current_sum > target && left <= right) {
                current_sum -= nums[left];
                left++;
            }
            
            // If we found a valid subarray, update the max length
            if (current_sum == target) {
                if (right - left + 1 > max_len) {
                    max_len = right - left + 1;
                }
            }
        }
        
        return max_len != -1 ? n - max_len : -1;
    }
};