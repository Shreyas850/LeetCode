class Solution {
    func validSequence(_ word1: String, _ word2: String) -> [Int] {
        let w1 = Array(word1.utf8)
        let w2 = Array(word2.utf8)
        let n = w1.count
        let m = w2.count
        
        var R = [Int](repeating: -1, count: m)
        var p1 = n - 1
        
        for j in stride(from: m - 1, through: 0, by: -1) {
            while p1 >= 0 && w1[p1] != w2[j] {
                p1 -= 1
            }
            if p1 >= 0 {
                R[j] = p1
                p1 -= 1
            } else {
                R[j] = -1 
            }
        }
        
        var ans = [Int]()
        var changed = false
        var i = 0
        
        for j in 0..<m {
            var found = false
            while i < n {
                if w1[i] == w2[j] {
                    ans.append(i)
                    i += 1
                    found = true
                    break
                } else if !changed {
                    if j == m - 1 || R[j + 1] >= i + 1 {
                        changed = true
                        ans.append(i)
                        i += 1
                        found = true
                        break
                    }
                }
                i += 1
            }
            
            if !found {
                return []
            }
        }
        
        return ans
    }
}