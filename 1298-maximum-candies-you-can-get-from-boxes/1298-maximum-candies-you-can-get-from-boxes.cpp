class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        vector<bool> hasBox(n, false);
        vector<bool> hasKey(n, false);
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; ++i) {
            if (status[i] == 1) {
                hasKey[i] = true;
            }
        }
        
        queue<int> q;
        for (int box : initialBoxes) {
            hasBox[box] = true;
            if (hasKey[box]) {
                visited[box] = true;
                q.push(box);
            }
        }
        
        int totalCandies = 0;
        
        while (!q.empty()) {
            int currentBox = q.front();
            q.pop();
            
            totalCandies += candies[currentBox];
            
            for (int key : keys[currentBox]) {
                hasKey[key] = true;
                if (hasBox[key] && !visited[key]) {
                    visited[key] = true;
                    q.push(key);
                }
            }
            
            for (int box : containedBoxes[currentBox]) {
                hasBox[box] = true;
                if (hasKey[box] && !visited[box]) {
                    visited[box] = true;
                    q.push(box);
                }
            }
        }
        
        return totalCandies;
    }
};