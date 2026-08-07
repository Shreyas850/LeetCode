import bisect

class MaxSparseTable:
    def __init__(self, arr):
        self.n = len(arr)
        if self.n == 0:
            return
        self.log = [0] * (self.n + 1)
        for i in range(2, self.n + 1):
            self.log[i] = self.log[i // 2] + 1
        self.st = [[0] * self.n for _ in range(self.log[self.n] + 1)]
        self.st[0] = list(arr)
        for j in range(1, self.log[self.n] + 1):
            length = 1 << (j - 1)
            row_prev = self.st[j - 1]
            row_curr = self.st[j]
            for i in range(self.n - (1 << j) + 1):
                a = row_prev[i]
                b = row_prev[i + length]
                row_curr[i] = a if a > b else b

    def query(self, L, R):
        if L > R or self.n == 0:
            return None
        j = self.log[R - L + 1]
        a = self.st[j][L]
        b = self.st[j][R - (1 << j) + 1]
        return a if a > b else b

class MinSparseTable:
    def __init__(self, arr):
        self.n = len(arr)
        if self.n == 0:
            return
        self.log = [0] * (self.n + 1)
        for i in range(2, self.n + 1):
            self.log[i] = self.log[i // 2] + 1
        self.st = [[0] * self.n for _ in range(self.log[self.n] + 1)]
        self.st[0] = list(arr)
        for j in range(1, self.log[self.n] + 1):
            length = 1 << (j - 1)
            row_prev = self.st[j - 1]
            row_curr = self.st[j]
            for i in range(self.n - (1 << j) + 1):
                a = row_prev[i]
                b = row_prev[i + length]
                row_curr[i] = a if a < b else b

    def query(self, L, R):
        if L > R or self.n == 0:
            return None
        j = self.log[R - L + 1]
        a = self.st[j][L]
        b = self.st[j][R - (1 << j) + 1]
        return a if a < b else b

class Solution:
    def maxActiveSectionsAfterTrade(self, s, queries):
        n = len(s)
        total_1s = s.count('1')
        
        zeros = []
        starts = []
        ends = []
        
        i = 0
        while i < n:
            if s[i] == '0':
                start = i
                while i < n and s[i] == '0':
                    i += 1
                zeros.append((start, i - 1, i - start))
                starts.append(start)
                ends.append(i - 1)
            else:
                i += 1
                
        K = len(zeros)
        ones_between = [starts[i+1] - ends[i] - 1 for i in range(K - 1)]
        Z_full_lens = [z[2] for z in zeros]
        ZZ_full = [Z_full_lens[i] + Z_full_lens[i+1] for i in range(K - 1)]
        
        max_Z_ST = MaxSparseTable(Z_full_lens)
        min_O_ST = MinSparseTable(ones_between)
        max_ZZ_ST = MaxSparseTable(ZZ_full)
        
        ans = []
        
        for l, r in queries:
            first_z = bisect.bisect_left(ends, l)
            last_z = bisect.bisect_right(starts, r) - 1
            
            if first_z > last_z or first_z == last_z:
                ans.append(total_1s)
                continue
                
            z1_start, z1_end, _ = zeros[first_z]
            zk_start, zk_end, _ = zeros[last_z]
            
            Z_prime_1 = min(r, z1_end) - max(l, z1_start) + 1
            Z_prime_k = min(r, zk_end) - max(l, zk_start) + 1
            
            M_Z = max(Z_prime_1, Z_prime_k)
            if first_z + 1 <= last_z - 1:
                val = max_Z_ST.query(first_z + 1, last_z - 1)
                M_Z = max(M_Z, val)
                
            m_O = min_O_ST.query(first_z, last_z - 1)
            
            if first_z + 1 == last_z:
                M_ZZ = Z_prime_1 + Z_prime_k
            else:
                val1 = Z_prime_1 + Z_full_lens[first_z + 1]
                val2 = Z_full_lens[last_z - 1] + Z_prime_k
                M_ZZ = max(val1, val2)
                if first_z + 1 <= last_z - 2:
                    val3 = max_ZZ_ST.query(first_z + 1, last_z - 2)
                    M_ZZ = max(M_ZZ, val3)
                    
            gain = max(M_ZZ, M_Z - m_O)
            ans.append(total_1s + gain)
            
        return ans