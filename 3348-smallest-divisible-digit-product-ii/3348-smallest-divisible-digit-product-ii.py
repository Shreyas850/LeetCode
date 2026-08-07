class Solution:
    def smallestNumber(self, num, t):
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a
            
        temp = t
        for p in [2, 3, 5, 7]:
            while temp % p == 0:
                temp //= p
        if temp > 1:
            return "-1"
            
        memo = {}
        def get_min_digits(R):
            if R == 1:
                return 0
            if R in memo:
                return memo[R]
            res = float('inf')
            for d in range(2, 10):
                nxt_R = R // gcd(R, d)
                if nxt_R < R:
                    res = min(res, 1 + get_min_digits(nxt_R))
            memo[R] = res
            return res
            
        n = len(num)
        
        if "0" not in num:
            R = t
            for char in num:
                R //= gcd(R, int(char))
            if R == 1:
                return num
                
        pref_R = [t]
        for char in num:
            if char == '0':
                break
            pref_R.append(pref_R[-1] // gcd(pref_R[-1], int(char)))
            
        z = min(n - 1, len(pref_R) - 1)
        
        for i in range(z, -1, -1):
            R = pref_R[i]
            start_d = int(num[i]) + 1
            for d in range(start_d, 10):
                nxt_R = R // gcd(R, d)
                if get_min_digits(nxt_R) <= n - 1 - i:
                    ans = [num[:i], str(d)]
                    rem_L = n - 1 - i
                    curr_R = nxt_R
                    while rem_L > 0:
                        for nxt_d in range(1, 10):
                            cand_R = curr_R // gcd(curr_R, nxt_d)
                            if get_min_digits(cand_R) <= rem_L - 1:
                                ans.append(str(nxt_d))
                                curr_R = cand_R
                                rem_L -= 1
                                break
                    return "".join(ans)
                    
        L = max(n + 1, get_min_digits(t))
        ans = []
        rem_L = L
        curr_R = t
        while rem_L > 0:
            for nxt_d in range(1, 10):
                cand_R = curr_R // gcd(curr_R, nxt_d)
                if get_min_digits(cand_R) <= rem_L - 1:
                    ans.append(str(nxt_d))
                    curr_R = cand_R
                    rem_L -= 1
                    break
        return "".join(ans)