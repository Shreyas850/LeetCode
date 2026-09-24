class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size();
        int mask = 0;
        int ans = 0;
        
        for (int b = 29; b >= 0; --b) {
            int test_mask = mask | (1 << b);
            int segments = 0;
            int current_and = -1; 
            
            for (int x : nums) {
                current_and &= x;
                
                if ((current_and & test_mask) == 0) {
                    segments++;
                    current_and = -1; 
                }
            }
            
            
            if (n - segments <= k) {
                mask = test_mask; 
            } else {
                ans |= (1 << b);  
            }
        }
        
        return ans;
    }
};