class Solution {
    func stoneGameV(_ stoneValue: [Int]) -> Int {
        let n = stoneValue.count
        if n <= 1 { return 0 }
        
        var prefix = [Int](repeating: 0, count: n + 1)
        for i in 0..<n {
            prefix[i + 1] = prefix[i] + stoneValue[i]
        }
        
        var dp = [[Int]](repeating: [Int](repeating: 0, count: n), count: n)
        
        for length in 2...n {
            for i in 0...(n - length) {
                let j = i + length - 1
                var maxScore = 0
                
                for k in i..<j {
                    let leftSum = prefix[k + 1] - prefix[i]
                    let rightSum = prefix[j + 1] - prefix[k + 1]
                    
                    if leftSum < rightSum {
                        let currentScore = leftSum + dp[i][k]
                        if currentScore > maxScore {
                            maxScore = currentScore
                        }
                    } else if leftSum > rightSum {
                        let currentScore = rightSum + dp[k + 1][j]
                        if currentScore > maxScore {
                            maxScore = currentScore
                        }
                    } else {
                        let bestSub = max(dp[i][k], dp[k + 1][j])
                        let currentScore = leftSum + bestSub
                        if currentScore > maxScore {
                            maxScore = currentScore
                        }
                    }
                }
                dp[i][j] = maxScore
            }
        }
        
        return dp[0][n - 1]
    }
}