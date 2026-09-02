class Solution {
    func maxStudents(_ seats: [[Character]]) -> Int {
        let m = seats.count
        let n = seats[0].count
        var valid = Array(repeating: 0, count: m)
        
        for i in 0..<m {
            for j in 0..<n {
                if seats[i][j] == "." {
                    valid[i] |= (1 << j)
                }
            }
        }
        
        var dp = Array(repeating: Array(repeating: -1, count: 1 << n), count: m)
        var maxAns = 0
        
        for i in 0..<m {
            for mask in 0..<(1 << n) {
                if (mask & valid[i]) == mask && (mask & (mask >> 1)) == 0 {
                    let currentCount = mask.nonzeroBitCount
                    
                    if i == 0 {
                        dp[i][mask] = currentCount
                    } else {
                        for prev in 0..<(1 << n) {
                            if dp[i - 1][prev] != -1 && 
                               (mask & (prev >> 1)) == 0 && 
                               (mask & (prev << 1)) == 0 {
                                
                                if dp[i - 1][prev] + currentCount > dp[i][mask] {
                                    dp[i][mask] = dp[i - 1][prev] + currentCount
                                }
                            }
                        }
                    }
                    
                    if dp[i][mask] > maxAns {
                        maxAns = dp[i][mask]
                    }
                }
            }
        }
        
        return maxAns
    }
}