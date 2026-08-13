class Solution {
    struct Node {
        int prefLen;
        char prefChar;
        int suffLen;
        char suffChar;
        int maxLen;
        int size;
    };
    
    vector<Node> tree;
    
    Node merge(const Node& left, const Node& right) {
        Node res;
        res.size = left.size + right.size;
        
        res.prefChar = left.prefChar;
        res.prefLen = left.prefLen;
        if (left.prefLen == left.size && left.prefChar == right.prefChar) {
            res.prefLen += right.prefLen;
        }
        
        res.suffChar = right.suffChar;
        res.suffLen = right.suffLen;
        if (right.suffLen == right.size && right.suffChar == left.suffChar) {
            res.suffLen += left.suffLen;
        }
        
        res.maxLen = max(left.maxLen, right.maxLen);
        if (left.suffChar == right.prefChar) {
            res.maxLen = max(res.maxLen, left.suffLen + right.prefLen);
        }
        
        return res;
    }
    
    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, s[start], 1, s[start], 1, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node + 1, start, mid, s);
        build(2 * node + 2, mid + 1, end, s);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }
    
    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            tree[node] = {1, val, 1, val, 1, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node + 1, start, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }
    
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        build(0, 0, n - 1, s);
        
        int k = queryIndices.size();
        vector<int> ans;
        ans.reserve(k);
        
        for (int i = 0; i < k; ++i) {
            update(0, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[0].maxLen);
        }
        
        return ans;
    }
};