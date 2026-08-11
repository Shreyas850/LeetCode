class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        bool exists = true;
        while (exists) {
            exists = false;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] == sum) {
                    exists = true;
                    sum++;
                    break;
                }
            }
        }
        
        return sum;
    }
};