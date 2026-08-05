#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Step 1: Build the adjacency list for the directed graph
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }
        
        // Step 2: Find all suspicious methods using BFS
        vector<bool> suspicious(n, false);
        queue<int> q;
        
        q.push(k);
        suspicious[k] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = true;
                    q.push(v);
                }
            }
        }
        
        // Step 3: Check if any non-suspicious method invokes a suspicious method
        bool can_remove = true;
        for (const auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];
            
            if (!suspicious[u] && suspicious[v]) {
                can_remove = false;
                break;
            }
        }
        
        // Step 4: Construct the result based on the check
        vector<int> result;
        if (can_remove) {
            for (int i = 0; i < n; ++i) {
                if (!suspicious[i]) {
                    result.push_back(i);
                }
            }
        } else {
            // If we can't remove them, return all methods
            for (int i = 0; i < n; ++i) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};