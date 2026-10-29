class Solution {
    vector<int> bit;
    int timer;
    
    void add(int idx, int val, int n) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }
    
    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res ^= bit[idx];
        }
        return res;
    }
    
    void dfs(int u, int p, int d, const vector<vector<int>>& adj, vector<int>& in, vector<int>& out, vector<int>& depth, vector<array<int, 16>>& up) {
        in[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < 16; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj, in, out, depth, up);
            }
        }
        out[u] = timer;
    }
    
    int get_lca(int u, int v, const vector<int>& depth, const vector<array<int, 16>>& up) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = 15; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = 15; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        
        timer = 0;
        vector<int> in(n), out(n), depth(n);
        vector<array<int, 16>> up(n);
        bit.assign(n + 2, 0);
        
        dfs(0, 0, 0, adj, in, out, depth, up);
        
        for (int i = 0; i < n; ++i) {
            int val = 1 << (s[i] - 'a');
            add(in[i], val, n);
            add(out[i] + 1, val, n);
        }
        
        vector<bool> ans;
        ans.reserve(queries.size());
        
        for (const string& q : queries) {
            if (q[0] == 'u') {
                int u = 0;
                int idx = 7;
                while (q[idx] != ' ') {
                    u = u * 10 + (q[idx] - '0');
                    idx++;
                }
                idx++;
                char c = q[idx];
                
                if (s[u] != c) {
                    int diff = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                    add(in[u], diff, n);
                    add(out[u] + 1, diff, n);
                    s[u] = c;
                }
            } else {
                int u = 0, v = 0;
                int idx = 6;
                while (q[idx] != ' ') {
                    u = u * 10 + (q[idx] - '0');
                    idx++;
                }
                idx++;
                while (idx < q.size()) {
                    v = v * 10 + (q[idx] - '0');
                    idx++;
                }
                
                int lca = get_lca(u, v, depth, up);
                int mask_u = query(in[u]);
                int mask_v = query(in[v]);
                int char_lca = 1 << (s[lca] - 'a');
                
                int path_mask = mask_u ^ mask_v ^ char_lca;
                
                if ((path_mask & (path_mask - 1)) == 0) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        }
        
        return ans;
    }
};