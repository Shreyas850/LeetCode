class Solution {
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        int count = 0;
        int next_avail = 0;
        
        for (int end = k - 1; end < n; ++end) {
            // Check for a valid palindrome of length k
            int start_k = end - k + 1;
            if (start_k >= next_avail && isPalindrome(s, start_k, end)) {
                count++;
                next_avail = end + 1;
                continue;
            }
            
            // Check for a valid palindrome of length k + 1
            int start_k_plus_1 = end - k;
            if (start_k_plus_1 >= next_avail && isPalindrome(s, start_k_plus_1, end)) {
                count++;
                next_avail = end + 1;
                continue;
            }
        }
        
        return count;
    }
};