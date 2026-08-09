class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = n - 1; i >= 0; --i) {
            for (int m = 1; m <= n; ++m) {
                if (i + 2 * m >= n) {
                    dp[i][m] = suffix_sum[i];
                } else {
                    int min_opponent = 2147483647;
                    for (int x = 1; x <= 2 * m; ++x) {
                        int next_m = (m > x) ? m : x;
                        if (dp[i + x][next_m] < min_opponent) {
                            min_opponent = dp[i + x][next_m];
                        }
                    }
                    dp[i][m] = suffix_sum[i] - min_opponent;
                }
            }
        }
        
        return dp[0][1];
    }
};