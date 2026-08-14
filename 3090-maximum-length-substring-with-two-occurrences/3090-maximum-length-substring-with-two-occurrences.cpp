class Solution {
public:
    int maximumLengthSubstring(string s) {
        int max_len = 0;
        int left = 0;
        int count[26] = {0};
        
        for (int right = 0; right < s.length(); ++right) {
            count[s[right] - 'a']++;
            
            while (count[s[right] - 'a'] > 2) {
                count[s[left] - 'a']--;
                left++;
            }
            
            if (right - left + 1 > max_len) {
                max_len = right - left + 1;
            }
        }
        
        return max_len;
    }
};