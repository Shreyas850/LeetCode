class Solution {
public:
    int score(vector<string>& cards, char x) {
        int L_counts[26] = {0};
        int R_counts[26] = {0};
        int c_x = 0;
        
        for (const string& card : cards) {
            if (card[0] == x && card[1] == x) {
                c_x++;
            } else if (card[0] == x) {
                L_counts[card[1] - 'a']++;
            } else if (card[1] == x) {
                R_counts[card[0] - 'a']++;
            }
        }
        
        int S_L = 0, M_L = 0;
        for (int i = 0; i < 26; ++i) {
            S_L += L_counts[i];
            if (L_counts[i] > M_L) {
                M_L = L_counts[i];
            }
        }
        
        int S_R = 0, M_R = 0;
        for (int i = 0; i < 26; ++i) {
            S_R += R_counts[i];
            if (R_counts[i] > M_R) {
                M_R = R_counts[i];
            }
        }
        
        int max_total = 0;
        
        for (int c_L = 0; c_L <= c_x; ++c_L) {
            int c_R = c_x - c_L;
            
            int pairs_L = min((S_L + c_L) / 2, c_L > M_L ? S_L : S_L + c_L - M_L);
            int pairs_R = min((S_R + c_R) / 2, c_R > M_R ? S_R : S_R + c_R - M_R);
            
            if (pairs_L + pairs_R > max_total) {
                max_total = pairs_L + pairs_R;
            }
        }
        
        return max_total;
    }
};